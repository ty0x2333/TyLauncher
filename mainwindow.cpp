#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qxtglobalshortcut.h"
#include "appbuttondialog.h"
#include "dynamicdata.h"
#include "aboutdialog.h"
#include "appbutton.h"
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
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QMenu>
#include <QCloseEvent>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    _trayIcon(nullptr),
    _trayMenu(nullptr),
    _btnMenu(nullptr),
    _aboutDialog(nullptr),
    _translator(nullptr),
    _netManager(nullptr),
    _isCanHide(true),
    _btnRightMenu(nullptr),
    _needShowUpdateDialog(false)
{
    ui->setupUi(this);
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("GB2312"));
    QWidget::installEventFilter(this);// 为这个窗口安装过滤器
#if defined(Q_OS_OSX)
    setWindowFlags(Qt::WindowStaysOnTopHint);
#elif defined(Q_OS_WIN32)
    setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);
#endif
    connect(ui->actionQuit, SIGNAL(triggered()), this, SLOT(on_Quit_triggered()));// 关联退出动作

    initBtnRightMenu();
    
    initTray();
    // 更新语言
    updateLanguage();
    
    // 尝试读取存档
    if(!loadSaveFile(DynamicData::getInstance()->getUserSettingsFileNames()))
        reset();// 还原默认设置
    ui->tabWidget->setStyleSheet("QTabBar::tab { min-width:" + QString::number(this->width() / 10 - 3) + "px;min-height:50px;}text-align:left top;");

    activateWindow();
    QxtGlobalShortcut *sc = new QxtGlobalShortcut(this);
    
    if (!sc->setShortcut(QKeySequence("Ctrl+Tab"))){
        UIUtils::showCriticalMsgBox(tr("failed to register: \"Ctrl+Tab\""));
    }
    
    _netManager = new QNetworkAccessManager(this);
    
    connect(_netManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));
    
    // 检查更新
    checkUpdate();
    
    connect(sc, SIGNAL(activated()),this, SLOT(on_hotKey_triggered()));
}
// @brief 读取存档文件
bool MainWindow::loadSaveFile(const QString fileName)
{
    if (!ui->tabWidget->configFromVector(DynamicData::getInstance()->getUserSaveData())){
        _isCanHide = false;
        UIUtils::showCriticalMsgBox(tr("Load Save Failure!"), this);
        _isCanHide = true;
        return false;
    }
    return true;
}
// @brief 重置数据
void MainWindow::reset()
{
    ui->tabWidget->clearAllAppBtnData();
    // 重置存档位置
    DynamicData::getInstance()->resetSaveFileName();
}
// @brief 保存设置
// @param[in] 文件路径
void MainWindow::saveUserSettings()
{
    DynamicData::getInstance()->saveUserSaveFile(ui->tabWidget->jsonString());
}

void MainWindow::on_hotKey_triggered()
{
    if(this->isHidden())
        restoreWindow();
    else
        hideWindow();
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
    saveUserSettings();
    DynamicData::getInstance()->saveAppConfig();
    qApp->exit();
}
void MainWindow::setisCanHide(bool val){_isCanHide = val;}
MainWindow::~MainWindow()
{
    delete ui;
    if(_trayIcon!=nullptr)
        delete _trayIcon;
    if(_trayMenu!=nullptr)
        delete _trayMenu;
    if(_aboutDialog!=nullptr)
        delete _aboutDialog;
    if(_translator!=nullptr)
        delete _translator;
    if(_btnMenu!=nullptr)
        delete _btnMenu;
}

void MainWindow::on_actionShowWindow_triggered()
{
    restoreWindow();// 还原窗口
}
// @brief "关于"菜单项被点击
void MainWindow::on_actionAbout_triggered()
{
    _isCanHide = false;
    if(_aboutDialog == nullptr)
        _aboutDialog = new AboutDialog(this);
    _aboutDialog->setModal(true);
    _aboutDialog->show();
}
void MainWindow::hideWindow()
{
    if(_isCanHide)
        this->hide();
}

void MainWindow::on_actionHotKey_triggered()
{
}
// @brief 按钮右键菜单
void MainWindow::onBtnRightClicked(QPoint)
{
    _btnRightMenu = (AppButton*)sender();
    bool isNotBtnEmpty = !_btnRightMenu->isEmpty();
    bool isNotBtnShearPlateEmpty = !DynamicData::getInstance()->BtnShearPlateIsEmpty();
    ui->actionActionBtnOpenDir->setEnabled(isNotBtnEmpty);// 打开文件夹
    ui->actionDelete->setEnabled(isNotBtnEmpty);// 删除
    ui->actionCopy->setEnabled(isNotBtnEmpty);// 复制
    ui->actionShear->setEnabled(isNotBtnEmpty);// 剪切
    ui->actionPaste->setEnabled(isNotBtnShearPlateEmpty);// 粘贴
    _btnMenu->exec(this->cursor().pos());
}
// @brief 按钮右键菜单中的打开文件夹
void MainWindow::on_actionActionBtnOpenDir_triggered()
{
    if(_btnRightMenu == nullptr)
        return;
    _btnRightMenu->openFileDirectory();
    _btnRightMenu = nullptr;
}
// @brief 按钮右键菜单中的编辑菜单项被点击
void MainWindow::on_actionEdit_triggered()
{
    if(_btnRightMenu == nullptr)
        return;
    _isCanHide = false;
    AppButtonDialog *appBtnDialog = new AppButtonDialog(this, _btnRightMenu);
    appBtnDialog->exec();
    _btnRightMenu = nullptr;
    _isCanHide = true;
}
// @brief 按钮右键菜单中的复制菜单项被点击
void MainWindow::on_actionCopy_triggered()
{
    if(_btnRightMenu == nullptr)
        return;
    copyBtn(_btnRightMenu);
    _btnRightMenu = nullptr;
}
// @brief 按钮右键菜单中的粘贴菜单项被点击
void MainWindow::on_actionPaste_triggered()
{
    if(_btnRightMenu == nullptr)
        return;
    pasteBtn(_btnRightMenu);
    _btnRightMenu = nullptr;
}
// @brief 按钮右键菜单中的剪切菜单项被点击
void MainWindow::on_actionShear_triggered()
{
    if(_btnRightMenu == nullptr)
        return;
    shearBtn(_btnRightMenu);
    _btnRightMenu = nullptr;
}
// @brief 按钮右键菜单中的删除菜单项被点击
void MainWindow::on_actionDelete_triggered()
{
    if(_btnRightMenu == nullptr)
        return;
    deleteBtn(_btnRightMenu);
    _btnRightMenu = nullptr;
}
// @brief 复制按钮
// @param[out] 是否操作成功
bool MainWindow::copyBtn(AppButton *btn)
{
    if(btn->isEmpty())
        return false;
    DynamicData::getInstance()->setBtnShearPlate(btn);
    return true;
}
// @brief 剪切按钮
void MainWindow::shearBtn(AppButton *btn)
{
    if(copyBtn(btn))
        btn->clear();// 在复制成功的情况下清除按钮
}
// @brief 粘贴按钮
void MainWindow::pasteBtn(AppButton *btn)
{
    if(DynamicData::getInstance()->BtnShearPlateIsEmpty())
        return;
    if(!btn->isEmpty())
    {
        _isCanHide = false;
        if( UIUtils::showWarnMsgBox(tr("Replace the button?"), this) == QMessageBox::Yes)
            btn->copyFrom(*DynamicData::getInstance()->getBtnShearPlate());
        _isCanHide = true;
    }
    else
    {
        btn->copyFrom(*DynamicData::getInstance()->getBtnShearPlate());
    }
}
// @brief 删除按钮
void MainWindow::deleteBtn(AppButton *btn)
{
    if(!btn->isEmpty())
    {
        _isCanHide = false;
        if( UIUtils::showWarnMsgBox(tr("Delete the button?"), this) == QMessageBox::Yes)
        {
            btn->clear();
        }
        _isCanHide = true;
    }
}

bool MainWindow::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == this && event->type())
    {
        switch (event->type())
        {
        case QEvent::WindowDeactivate:
            TyLogDebug("QEvent::WindowDeactivate");
            hideWindow();
            break;
        case QEvent::WindowStateChange:
            TyLogDebug("QEvent::WindowStateChange");
            if(this->isMinimized())
            {
                event->ignore();// 截断事件
                hideWindow();
            }
            break;
        case QEvent::Close:
            TyLogDebug("QEvent::Close");
            event->ignore();// 截断事件
            hideWindow();
            return true;
            break;
        case QEvent::Resize:
            TyLogDebug("QEvent::Resize");
            ui->tabWidget->setStyleSheet("QTabBar::tab {min-width:" + QString::number(this->width() / 10 - 3) + "px;min-height:50px;}");
            break;
        }
    }
    return false;
}
void MainWindow::keyPressEvent(QKeyEvent *keyEvent)
{
    if(keyEvent->modifiers() == Qt::ControlModifier)// 判断是否按下了Ctrl(功能键)
    {
        QList<AppButton *> appButtonList = ui->tabWidget->currentWidget()->findChildren<AppButton *>();
        switch(keyEvent->key())
        {
        case Qt::Key_C:
                for(AppButton* btn : appButtonList) // 遍历所有AppButton，寻找当前鼠标指向的按钮
                {
                    if(btn->isBeMousePointing())
                    {
                        copyBtn(btn);
                    }
                }
            break;
        case Qt::Key_X:
                for(AppButton* btn : appButtonList) // 遍历所有AppButton，寻找当前鼠标指向的按钮
                {
                    if(btn->isBeMousePointing())
                    {
                        shearBtn(btn);
                    }
                }
            break;
        case Qt::Key_V:
                for(AppButton* btn : appButtonList) // 遍历所有AppButton
                {
                    if(btn->isBeMousePointing())// 找到被鼠标指向的AppButton
                    {
                        pasteBtn(btn);
                    }
                }
            break;
        default:
            break;
        }
    }
    else
    {
        switch(keyEvent->key())
        {
        case Qt::Key_Escape:
            hideWindow();
            break;
        case Qt::Key_Delete:
        {
            QList<AppButton *> appButtonList = ui->tabWidget->currentWidget()->findChildren<AppButton *>();
            for(AppButton* btn : appButtonList) // 遍历所有AppButton
            {
                if(btn->isBeMousePointing())// 找到被鼠标指向的AppButton
                {
                    deleteBtn(btn);
                }
            }
        }
            break;
        default:
            QString keyStr = QKeySequence(keyEvent->key()).toString(QKeySequence::NativeText);
            QList<AppButton *> appButtonList = ui->tabWidget->currentWidget()->findChildren<AppButton *>();
            for(auto btn : appButtonList)
            {
                if(keyStr == btn->text())
                {
                    btn->click();
                    return;
                }
            }
            QTabBar *tabBar = ui->tabWidget->tabBar();
            for(int i = 0; i < tabBar->count(); ++i)
            {
                if(keyStr == tabBar->tabText(i))
                {
                    tabBar->setCurrentIndex(i);
                }
            }
            break;
        }
    }
}

// @brief "保存"菜单项响应
void MainWindow::on_actionSave_triggered()
{
    saveUserSettings();
    DynamicData::getInstance()->saveAppConfig();
}
// @brief "另保存"菜单项响应
void MainWindow::on_actionSave_As_triggered()
{
    QFileDialog *fileDialog = new QFileDialog(this, tr("Save As"), 
                                              ".", 
                                              "User Settins File(*.tam);;All File(*.*)");
    fileDialog->setAcceptMode(QFileDialog::AcceptSave);
    fileDialog->setModal(true);
    _isCanHide = false;
    if(fileDialog->exec() == QDialog::Accepted){
        QString fileName = fileDialog->selectedFiles()[0];
        DynamicData::getInstance()->setUserSettingsFileNames(fileName);
        saveUserSettings();
        DynamicData::getInstance()->saveAppConfig();
    }
    _isCanHide = true;
    delete fileDialog;
}
// @brief 更新主题
void MainWindow::updateTheme()
{
    // 设置样式
    QString qss;
    QFile qssFile(DynamicData::getInstance()->getTheme());
    qssFile.open(QFile::ReadOnly);
    if(qssFile.isOpen())
    {
        qss = QLatin1String(qssFile.readAll());
        qApp->setStyleSheet(qss);
        qssFile.close();
    }
    else
    {
        qApp->setStyleSheet("");
    }
    
}

void MainWindow::on_actionDefaultTheme_triggered()
{
    DynamicData::getInstance()->setTheme(":/css/res/default.qss");
    updateTheme();
}

void MainWindow::on_actionSystemTheme_triggered()
{
    DynamicData::getInstance()->setTheme("");
    updateTheme();
}

void MainWindow::on_actionEnglish_triggered()
{
    DynamicData::getInstance()->setLanguage("en");
    updateLanguage();
}

void MainWindow::on_actionChinese_triggered()
{
    DynamicData::getInstance()->setLanguage("zh_CN");
    updateLanguage();
}
// @brief 更新语言
void MainWindow::updateLanguage()
{
    if(_translator == nullptr)
        _translator = new QTranslator();
    _translator->load(QString(":/language/%1_").arg(qAppName()) + DynamicData::getInstance()->getLanguage());
    qApp->installTranslator(_translator);
    ui->retranslateUi(this);
}

void MainWindow::initBtnRightMenu()
{
    _btnMenu = new QMenu();
    _btnMenu->addAction(ui->actionActionBtnOpenDir);
    _btnMenu->addSeparator();
    _btnMenu->addAction(ui->actionEdit);
    _btnMenu->addSeparator();
    _btnMenu->addAction(ui->actionCopy);
    _btnMenu->addAction(ui->actionPaste);
    _btnMenu->addAction(ui->actionShear);
    _btnMenu->addAction(ui->actionDelete);
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
    _trayIcon->setIcon(QIcon(":/img/res/logo.ico")); // 设置托盘图标
    _trayIcon->show();// 显示托盘
}
// @brief 检查更新
void MainWindow::checkUpdate()
{
    QUrl url("http://tyyappmanager.sinaapp.com/update.php");
    QByteArray param;
    param.append("version=");
    param.append(VER_FILEVERSION_DISPLAY_STR);
    param.append("&system=");
    param.append(APPLICATION_BIT);
    _netManager->post(QNetworkRequest(url), param); 
}

void MainWindow::replyFinished(QNetworkReply *reply)
{
     if (reply->error() == QNetworkReply::NoError) 
     { 
        QByteArray bytes = reply->readAll();
        try
        {
            QJsonParseError parseErr;
            QJsonDocument doc = QJsonDocument::fromJson(bytes,&parseErr);
            if(parseErr.error != QJsonParseError::NoError || !doc.isObject())
                 throw QString("Server Error!");
            QJsonObject jsonObj = doc.object();
            if( jsonObj["state"] == -1 )
                throw QString("Server Error!");
            if( jsonObj["need"] == false )
            {
                if(_needShowUpdateDialog)
                {
                    _isCanHide = false;
                    UIUtils::showInfoMsgBox(tr("%1 is up tp date!").arg(qAppName()), this);
                    _isCanHide = true;
                }
            }
            else
            {
                _isCanHide = false;
                QString infoStr = tr("There is a new version!");
                infoStr += "\n" + jsonObj["name"].toString() + "\n" + tr("Whether to download?");
                if(UIUtils::showInfoMsgBox(infoStr, this) == QMessageBox::Yes)
                    QDesktopServices::openUrl(QUrl::fromLocalFile(APP_URL));
                _isCanHide = true;
            }
        }
        catch(QString& errStr)
        {
            _isCanHide = false;
            UIUtils::showCriticalMsgBox(errStr, this);
            _isCanHide = true;
        }
     } 
     else 
     {
         if(_needShowUpdateDialog)
         {
             _isCanHide = false;
             UIUtils::showCriticalMsgBox(tr("Please check your network connection."), this);
             _isCanHide = true;
         }
     }
     reply->deleteLater(); 
}

void MainWindow::on_actionCheck_Update_triggered()
{
    _needShowUpdateDialog = true;
    checkUpdate();
}
