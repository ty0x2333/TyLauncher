#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qxtglobalshortcut.h"
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
#include "utils/shearplateutils.h"
#include "appconfigdialog.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    _trayIcon(nullptr),
    _trayMenu(nullptr),
    _translator(nullptr),
    _netManager(nullptr),
    _needShowUpdateDialog(false)
{
    ui->setupUi(this);
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("GB2312"));
    QWidget::installEventFilter(this);// 为这个窗口安装过滤器
    
    Qt::WindowFlags flags = windowFlags();
    if (DynamicData::getInstance()->getAlwaysOnTop())
        flags |= Qt::WindowStaysOnTopHint;
#if defined(Q_OS_OSX)
    setWindowFlags(flags);
#elif defined(Q_OS_WIN32)
    flags |= Qt::FramelessWindowHint;
    setWindowFlags(flags);
#endif
    connect(ui->actionQuit, SIGNAL(triggered()), this, SLOT(on_Quit_triggered()));// 关联退出动作
    
    initTray();
    
    initMenu();
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
    saveUserSettings();
    DynamicData::getInstance()->saveAppConfig();
    qApp->exit();
}
MainWindow::~MainWindow()
{
    delete ui;
    if(_trayIcon!=nullptr)
        delete _trayIcon;
    if(_trayMenu!=nullptr)
        delete _trayMenu;
    if(_translator!=nullptr)
        delete _translator;
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

void MainWindow::on_actionHotKey_triggered()
{
}

bool MainWindow::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == this && event->type())
    {
        switch (event->type())
        {
        case QEvent::WindowDeactivate:
            TyLogDebug("QEvent::WindowDeactivate");
            if (!qApp->activeWindow())
                this->hide();
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
                for(AppButton* btn : appButtonList){ // 遍历所有AppButton，寻找当前鼠标指向的按钮
                    if(btn->isBeMousePointing()){
                        ShearPlateUtils::copy(btn);
                    }
                }
            break;
        case Qt::Key_X:
                for(AppButton* btn : appButtonList){ // 遍历所有AppButton，寻找当前鼠标指向的按钮
                    if(btn->isBeMousePointing()){
                        ShearPlateUtils::shear(btn);
                    }
                }
            break;
        case Qt::Key_V:
                for(AppButton* btn : appButtonList){ // 遍历所有AppButton
                    if(btn->isBeMousePointing()){// 找到被鼠标指向的AppButton
                        ShearPlateUtils::paste(btn);
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
            TyLogDebug("Esc Press, activeWindow: %d", qApp->activeWindow());
            if (qApp->activeWindow())
                this->hide();
            break;
        case Qt::Key_Delete:
        {
            QList<AppButton *> appButtonList = ui->tabWidget->currentWidget()->findChildren<AppButton *>();
            for(AppButton* btn : appButtonList){ // 遍历所有AppButton
                if(btn->isBeMousePointing()){// 找到被鼠标指向的AppButton
                    ShearPlateUtils::remove(btn);
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
    if(fileDialog->exec() == QDialog::Accepted){
        QString fileName = fileDialog->selectedFiles()[0];
        DynamicData::getInstance()->setUserSettingsFileNames(fileName);
        saveUserSettings();
        DynamicData::getInstance()->saveAppConfig();
    }
    delete fileDialog;
}
// @brief 更新主题
void MainWindow::updateTheme()
{
    // 设置样式
    QString qss;
    QFile qssFile(DynamicData::getInstance()->getTheme());
    qssFile.open(QFile::ReadOnly);
    if(qssFile.isOpen()){
        qss = QLatin1String(qssFile.readAll());
        qApp->setStyleSheet(qss);
        qssFile.close();
    }else{
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

void MainWindow::onLanguageMenuClicked()
{
    QAction *action = dynamic_cast<QAction *>(QObject::sender());
    if (action == nullptr)
        return;
    DynamicData::getInstance()->setLanguage(action->text());
    updateLanguage();
}

// @brief 更新语言
void MainWindow::updateLanguage()
{
    if(_translator == nullptr)
        _translator = new QTranslator();
    _translator->load(QString("language/") + DynamicData::getInstance()->getLanguage());
    qApp->installTranslator(_translator);
    ui->retranslateUi(this);
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

void MainWindow::initMenu()
{
    QStringList list = DynamicData::getInstance()->getLanguageList();
    for (QString languageName : list){
        QAction *action = new QAction(languageName, this);
        connect(action, SIGNAL(triggered()), this, SLOT(onLanguageMenuClicked()));
        ui->menuLanguage->addAction(action);
    }
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
            if( jsonObj["need"] == false ){
                if(_needShowUpdateDialog){
                    UIUtils::showInfoMsgBox(tr("%1 is up tp date!").arg(qAppName()), this);
                }
            }else{
                QString infoStr = tr("There is a new version!");
                infoStr += "\n" + jsonObj["name"].toString() + "\n" + tr("Whether to download?");
                if(UIUtils::showInfoMsgBox(infoStr, this) == QMessageBox::Ok)
                    QDesktopServices::openUrl(QUrl::fromLocalFile(APP_URL));
            }
        }catch(QString& errStr){
            UIUtils::showCriticalMsgBox(errStr, this);
        }
     }else {
         if(_needShowUpdateDialog){
             UIUtils::showCriticalMsgBox(tr("Please check your network connection."), this);
         }
     }
     reply->deleteLater(); 
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
