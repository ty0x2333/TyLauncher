/**
 * Copyright (c) 2016, luckytianyiyan <luckytianyiyan@gmail.com>
 * 
 * This file is part of TyLauncher.
 * 
 * TyLauncher is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * TyLauncher is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with TyLauncher.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qxtglobalshortcut.h"
#include "dynamicdata.h"
#include "aboutdialog.h"
#include "widget/appbutton.h"
#include "StaticSetting.h"
#include "TyLog_Qt.h"
#include "utils/uiutils.h"
#include <QMessageBox>
#include <QGridLayout>
#include <QPushButton>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QFile>
#include <QTextStream>
#include <QTextCodec>
#include <QFileDialog>
#include <QDesktopServices>
#include <QTranslator>
#include <QtNetwork/QNetworkReply>
#include <QMenu>
#include <QCloseEvent>
#include "appconfigdialog.h"
#include "datasettings.h"
#include "widget/tabwidget.h"
#include "widget/updatedialog.h"
#include "utils/stringutils.h"
#include "api/tyalgorithmapi.h"
#include "shearplate.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , _trayIcon(nullptr)
    , _trayMenu(nullptr)
    , _translator(nullptr)
    , _globalShortcut(nullptr)
    , _needShowUpdateDialog(false)
{
    ui->setupUi(this);
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("GB2312"));
    QWidget::installEventFilter(this);// 为这个窗口安装过滤器
    
#if defined(Q_OS_WIN32)
    setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);
#elif defined(Q_OS_OSX)
    setWindowFlags(Qt::WindowStaysOnTopHint);
#endif
    connect(ui->actionQuit, SIGNAL(triggered()), this, SLOT(on_Quit_triggered()));// 关联退出动作
    
    initTray();
    // 更新语言
    updateLanguage();
    
    // 尝试读取存档
    if(!loadSaveFile(DYNAMIC_DATA->userSettingsFileName()))
        reset();// 还原默认设置
    
    activateWindow();
    
    initGlobalShortcut();
    
    // 检查更新
    checkUpdate();
    
    connect(DYNAMIC_DATA, SIGNAL(appConfigChanged(QString)), this, SLOT(onAppConfigChanged(QString)));
}

void MainWindow::initTray()
{
    _trayIcon = new QSystemTrayIcon(this);
    _trayMenu = new QMenu();
    connect(_trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
            this, SLOT(onSystemTrayIconClicked(QSystemTrayIcon::ActivationReason)));
    _trayMenu->addAction(ui->actionShowWindow);// 添加显示主窗口菜单项
    _trayMenu->addSeparator();// 分割线
    _trayMenu->addAction(ui->actionQuit);// 添加退出菜单项
    _trayIcon->setContextMenu(_trayMenu);// 设置托盘菜单
    _trayIcon->setIcon(this->windowIcon()); // 设置托盘图标
    _trayIcon->show();// 显示托盘
}

void MainWindow::initGlobalShortcut()
{
    _globalShortcut = new QxtGlobalShortcut(this);
    QKeySequence keySequence = DYNAMIC_DATA->getGlobalShortcut();
    if (!_globalShortcut->setShortcut(keySequence)){
        UIUtils::showCriticalMsgBox(tr("failed to register: \"%1\"").arg(keySequence.toString()));
    }
    connect(_globalShortcut, SIGNAL(activated()),this, SLOT(on_hotKey_triggered()));
}

// @brief 读取存档文件
bool MainWindow::loadSaveFile(const QString fileName)
{
    if (!ui->tabWidget->configFromVector(DYNAMIC_DATA->getUserSaveData())){
        UIUtils::showCriticalMsgBox(tr("Load Save Failure!"), this);
        return false;
    }
    return true;
}
// @brief 重置数据
void MainWindow::reset()
{
    ui->tabWidget->clearAllAppBtnData();
    // 重置存档位置
//    DYNAMIC_DATA->resetSaveFileName();
}

void MainWindow::on_hotKey_triggered()
{
    if(this->isHidden()){
        restoreWindow();
    }else{
        if (qApp->activeWindow() == this)
            this->hide();
    }
}

// @brief 还原窗口
void MainWindow::restoreWindow()
{
    this->show();// 显示窗体
    setWindowState(Qt::WindowNoState);
    activateWindow();
}

// @brief 托盘图标点击
void MainWindow::onSystemTrayIconClicked(QSystemTrayIcon::ActivationReason reason)
{
    switch(reason)
    {
    case QSystemTrayIcon::Trigger:// 单击
        restoreWindow();// 还原窗口
        break;
    }
}
// @brief 托盘菜单的退出按钮响应
void MainWindow::on_Quit_triggered()
{
    DYNAMIC_DATA->saveUserSaveFile(ui->tabWidget->jsonString());
    DYNAMIC_DATA->saveAppConfig();
    qApp->exit();
}
MainWindow::~MainWindow()
{
    delete ui;
    if (_trayIcon != nullptr)
        delete _trayIcon;
    if (_trayMenu != nullptr)
        delete _trayMenu;
    if (_translator != nullptr)
        delete _translator;
    if (_globalShortcut != nullptr)
        delete _globalShortcut;
}

void MainWindow::on_actionShowWindow_triggered()
{
    restoreWindow();// 还原窗口
}
// @brief "关于"菜单项被点击
void MainWindow::on_actionAbout_triggered()
{
    AboutDialog *aboutDialog = new AboutDialog(this);
    aboutDialog->exec();
}

bool MainWindow::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == this && event->type())
    {
        switch (event->type())
        {
        case QEvent::WindowDeactivate:
            TyLogDebug("QEvent::WindowDeactivate");
            TyLogDebug("active status{\n\thas activeWindow: %s\n\thas activeModalWidget: %s\n\thas activePopupWidget: %s\n}", 
                       qApp->activeWindow() ? "YES" : "NO",
                       qApp->activeModalWidget() ? "YES" : "NO",
                       qApp->activePopupWidget() ? "YES" : "NO");
            if (!qApp->activeModalWidget()) {
                this->hide();
            }
            break;
        case QEvent::WindowStateChange:
            TyLogDebug("QEvent::WindowStateChange");
            if(this->isMinimized()){
                event->ignore();// 截断事件
                if (!qApp->activeWindow())
                    this->hide();
            }
            break;
        case QEvent::Close:
            TyLogDebug("QEvent::Close");
            event->ignore();// 截断事件
            if (!qApp->activeWindow())
                this->hide();
            return true;
            break;
        case QEvent::Resize:
            TyLogDebug("QEvent::Resize");
//            ui->tabWidget->setStyleSheet("QTabBar::tab { min-width:" + QString::number(this->width() / DEFAULT_TAB_COUNT) + "px;}");
//            ui->tabWidget->setStyleSheet("QTabBar::tab {min-width:" + QString::number(this->width() / 10 - 3) + "px;min-height:50px;}");
            break;
        }
    }
    return false;
}
void MainWindow::keyPressEvent(QKeyEvent *keyEvent)
{
    if(keyEvent->modifiers() != Qt::NoModifier){
        return;
    }
    switch(keyEvent->key())
    {
    case Qt::Key_Escape:
        TyLogDebug("Esc Press, activeWindow: %d", qApp->activeWindow());
        if (qApp->activeWindow())
            this->hide();
        break;
    case Qt::Key_Delete:
    {
        QList<AppButton *> appButtonList = ui->tabWidget->currentWidget()->findChildren<AppButton *>();
        for(AppButton* btn : appButtonList){ // 遍历所有AppButton
            if(btn->isBeMousePointing()){// 找到被鼠标指向的AppButton
                SHEAR_PLATE->remove(btn);
            }
        }
    }
        break;
    default:
        QString keyStr = QKeySequence(keyEvent->key()).toString(QKeySequence::NativeText);
        QList<AppButton *> appButtonList = ui->tabWidget->currentWidget()->findChildren<AppButton *>();
        for(auto btn : appButtonList){
            if(keyStr == btn->text()){
                btn->click();
                return;
            }
        }
        QTabBar *tabBar = ui->tabWidget->tabBar();
        for(int i = 0; i < tabBar->count(); ++i){
            if(keyStr == tabBar->tabText(i)){
                tabBar->setCurrentIndex(i);
            }
        }
        break;
    }
}

// @brief "保存"菜单项响应
void MainWindow::on_actionSave_triggered()
{
    DYNAMIC_DATA->saveUserSaveFile(ui->tabWidget->jsonString());
    DYNAMIC_DATA->saveAppConfig();
}
// @brief "另保存"菜单项响应
void MainWindow::on_actionSave_As_triggered()
{
    QFileDialog *fileDialog = new QFileDialog(this, tr("Save As"), 
                                              ".", 
                                              "User Settins File(*.json);;All File(*.*)");
    fileDialog->setAcceptMode(QFileDialog::AcceptSave);
    if(fileDialog->exec() == QDialog::Accepted){
        QString fileName = fileDialog->selectedFiles().first();
        DYNAMIC_DATA->saveUserSaveFile(ui->tabWidget->jsonString(), fileName);
    }
    delete fileDialog;
}

// @brief 更新语言
void MainWindow::updateLanguage()
{
    if(_translator == nullptr)
        _translator = new QTranslator();
    _translator->load(QString("language/") + DYNAMIC_DATA->getLanguage());
    qApp->installTranslator(_translator);
    ui->retranslateUi(this);
}

// @brief 检查更新
void MainWindow::checkUpdate()
{
    TyAlgorithmAPI::checkUpdate(this, SLOT(checkUpdateFinished()));
}

void MainWindow::on_actionCheck_Update_triggered()
{
    _needShowUpdateDialog = true;
    checkUpdate();
}

void MainWindow::on_actionSettings_triggered()
{
    AppConfigDialog *configDialog = new AppConfigDialog(this);
    configDialog->exec();
}

void MainWindow::onAppConfigChanged(const QString &name)
{
    TyLogDebug("onAppConfigChanged : %s", name.toUtf8().data());
    
    if (name == KEY_LANGUAGE){
        updateLanguage();
    }else if (name == KEY_HOT_KEY){
        _globalShortcut->setShortcut(DYNAMIC_DATA->getGlobalShortcut());
    }
}

void MainWindow::checkUpdateFinished()
{
    QNetworkReply *reply=dynamic_cast<QNetworkReply*>(sender());
    if (reply == nullptr)
        return;
    if (reply->error() == QNetworkReply::NoError) { 
        QByteArray bytes = reply->readAll();
        TyLogDebug("reply: %s", bytes.data());
        QT_TRY {
            QJsonParseError parseErr;
            QJsonDocument doc = QJsonDocument::fromJson(bytes,&parseErr);
            if(parseErr.error != QJsonParseError::NoError || !doc.isObject()){
                qDebug("QJsonParseError: %s\n ", bytes.toStdString().data());
            }
            QJsonObject jsonObj = doc.object();

            if(jsonObj["need"] == true) {
                QJsonObject dataObj = jsonObj["data"].toObject();
                UpdateDialog *updateDialog = new UpdateDialog(this, dataObj["version"].toString(), dataObj["version_explain"].toString());
                updateDialog->setUpdateLink(dataObj["href"].toString());
                updateDialog->exec();
            } else {
                if(_needShowUpdateDialog) {
                    UIUtils::showInfoMsgBox(tr("%1 is up to date!").arg(qAppName()), this);
                }
            }
        } QT_CATCH(QString& errStr) {
            TyLogDebug("Json Parse Error: %s", errStr);
        }
    } else {
        QString errorStr = StringUtils::networkErrorString(reply->error());
        if(_needShowUpdateDialog) {
            UIUtils::showCriticalMsgBox(errorStr, this);
        }
        TyLogDebug("Network Error: %s", errorStr.toUtf8().data());
    }
    reply->deleteLater();
}
