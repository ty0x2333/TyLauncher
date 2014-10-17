#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qxtglobalshortcut.h"
#include <QMessageBox>
#include <QGridLayout>
#include <QPushButton>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QFile>
#include <QTextStream>
#include <QTextCodec>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    _aboutDialog(nullptr),
    _trayMenu(nullptr),
    _trayIcon(nullptr),
    _btnShearPlate(nullptr),
    _isCanHide(true),
    _btnMenu(nullptr),
    _btnRightMenu(nullptr)
{
    ui->setupUi(this);
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("GB2312"));
    QWidget::installEventFilter(this);// 为这个窗口安装过滤器
    setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);
    connect(ui->actionQuit, SIGNAL(triggered()), this, SLOT(on_Quit_triggered()));// 关联退出动作
    
    _btnMenu = new QMenu();
    _btnMenu->addAction(ui->actionActionBtnOpenDir);
    _btnMenu->addSeparator();
    _btnMenu->addAction(ui->actionCopy);
    _btnMenu->addAction(ui->actionPaste);
    _btnMenu->addAction(ui->actionShear);
    _btnMenu->addAction(ui->actionDelete);
    
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
    
    // 尝试读取存档
    if(!loadSaveFile(SAVE_FILE))
        reset();// 还原默认设置
    ui->tabWidget->setStyleSheet("QTabBar::tab { min-width:" + QString::number(this->width() / 10 - 3) + "px;min-height:50px;}text-align:left top;");
    // 设置样式
    QString qss;
    //QFile qssFile("C:/css.qss");
    QFile qssFile(":/css/res/css.qss");
    qssFile.open(QFile::ReadOnly);
    if(qssFile.isOpen())
    {
        qss = QLatin1String(qssFile.readAll());
        qApp->setStyleSheet(qss);
//        qDebug("-----------------Start----------------------");
//        qDebug(qss.toUtf8().data());
//        qDebug("------------------End-----------------------");
        qssFile.close();
    }
    activateWindow();
    QxtGlobalShortcut *sc = new QxtGlobalShortcut(QKeySequence("Ctrl+~"), this);
    connect(sc, SIGNAL(activated()),this, SLOT(on_hotKey_triggered()));
}
// @brief 读取存档文件
bool MainWindow::loadSaveFile(const QString fileName)
{
    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
        return false;
    QJsonParseError parseErr;
    QJsonDocument doc = QJsonDocument::fromJson(file.readAll(),&parseErr);
    if(parseErr.error != QJsonParseError::NoError)
    {
        QMessageBox errorBox(QMessageBox::Critical, 
                               tr("存档读取失败"), 
                               parseErr.errorString(), 
                               QMessageBox::Ok, 
                               this, Qt::WindowStaysOnTopHint);
        errorBox.exec();
        return false;
    }
    QJsonArray tabArr = doc.array();
    for(int i = 0; i < 10; ++i)// 每一个Tab
    {
        QWidget *tab = new QWidget();
        QGridLayout *layout = new QGridLayout();
        QJsonValue val = tabArr.at(i);
        if(!val.isArray())
            return false;
        QJsonArray arr = val.toArray();
        for(int c = 0; c < 10; ++c)// 每一列
        {
            for(int r = 0; r < 3; ++r)// 每一行
            {
                QJsonValue valObj = arr.at(i);
                if(!valObj.isObject())
                    return false;
                QJsonObject obj = arr.at(c*3 + r).toObject();
                AppButton *btn = new AppButton(obj[XML_KEY_HOT_KEY].toString(), 
                                               obj[XML_KEY_FILE_NAME].toString());
                QString appName = obj[XML_KEY_APP_NAME].toString();
                connect(btn, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(onBtnRightClicked(QPoint)));
                if(!appName.isEmpty())
                    btn->setAppName(appName);
                layout->addWidget(btn, r, c);
            }
        }
        tab->setLayout(layout);
        ui->tabWidget->addTab(tab, QString::number((i + 1) % 10));
    }
    return true;
}
// @brief 重置数据
void MainWindow::reset()
{
    QString btnStr[3][10] = {{"Q", "W", "E", "R", "T", "Y", "U", "I", "O", "P"}
                             ,{"A", "S", "D", "F", "G", "H", "J", "K", "L", ";"}
                             ,{"Z", "X", "C", "V", "B", "N", "M", ",", ".", "/"}
                            };
    for(int i = 0; i < 10; ++i)
    {
        QWidget *tab = new QWidget();
        QGridLayout *layout = new QGridLayout();
        for(int c = 0; c < 10; ++c)
        {
            for(int r = 0; r < 3; ++r)
            {
                AppButton *btn = new AppButton(btnStr[r][c]);
                connect(btn, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(onBtnRightClicked(QPoint)));
                layout->addWidget(btn, r, c);
            }
        }
        tab->setLayout(layout);
        ui->tabWidget->addTab(tab, QString::number((i + 1)%10));
    }
}
// @brief 保存设置
void MainWindow::saveSettings()
{
    // 存档 Json
    QJsonDocument doc;
    QJsonArray tabArr;
    for(int i = 0; i < ui->tabWidget->count(); ++i)// 遍历所有tab
    {
        QJsonArray arr;
        QList<AppButton *> appButtonList = ui->tabWidget->widget(i)->findChildren<AppButton *>();
        for(AppButton* btn : appButtonList) // 遍历所有AppButton
        {
            QJsonObject obj;
            obj.insert(XML_KEY_HOT_KEY, btn->text());// 按钮的快捷键
            obj.insert(XML_KEY_APP_NAME, btn->getAppName());// 按钮的应用名
            obj.insert(XML_KEY_FILE_NAME, btn->getFileName());// 按钮的应用文件路径
            arr.append(obj);
        }
        tabArr.append(arr);
    }
    doc.setArray(tabArr);
    QFile file(SAVE_FILE);
    if(!file.open(QFile::WriteOnly))
    {
        qDebug("无法保存文件 %s:\n %s.", SAVE_FILE, file.errorString());
        throw(tr("无法保存文件 %1:\n %2.").arg(SAVE_FILE).arg(file.errorString()));
        return;
    }
    QTextStream txtOutput(&file);
    txtOutput.setCodec("UTF-8");
    txtOutput << doc.toJson();
    qDebug("save file, fileName : %s.", SAVE_FILE);
    file.close();
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
    saveSettings();
    qApp->exit();
}
void MainWindow::setisCanHide(bool val){_isCanHide = val;}
MainWindow::~MainWindow()
{
    delete ui;
    delete _trayIcon;
    delete _trayMenu;
    delete _aboutDialog;
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
    {
        _aboutDialog = new AboutDialog(this);
    }
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
void MainWindow::copyBtn(AppButton *btn)
{
    if(_btnShearPlate == nullptr)
        delete _btnShearPlate;
    _btnShearPlate = new AppButton("");
    _btnShearPlate->copyFrom(*btn);
}
// @brief 剪切按钮
void MainWindow::shearBtn(AppButton *btn)
{
    copyBtn(btn);
    btn->clear();
}
// @brief 粘贴按钮
void MainWindow::pasteBtn(AppButton *btn)
{
    if(!btn->getFileName().isEmpty())
    {
        _isCanHide = false;
        QMessageBox warningBox(QMessageBox::Warning, 
                               "警告", 
                               "该操作会覆盖该按钮的设置, 请确认.", 
                               QMessageBox::Yes|QMessageBox::No, 
                               this, Qt::WindowStaysOnTopHint);
        if( warningBox.exec() == QMessageBox::Yes)
        {
            btn->copyFrom(*_btnShearPlate);
        }
        _isCanHide = true;
    }
    else
    {
        btn->copyFrom(*_btnShearPlate);
    }
}
// @brief 删除按钮
void MainWindow::deleteBtn(AppButton *btn)
{
    if(!btn->getFileName().isEmpty())
    {
        _isCanHide = false;
        QMessageBox warningBox(QMessageBox::Warning, 
                               "警告", 
                               "确认删除该按钮的数据?", 
                               QMessageBox::Yes|QMessageBox::No, 
                               this, Qt::WindowStaysOnTopHint);
        if( warningBox.exec() == QMessageBox::Yes)
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
            hideWindow();
            break;
        case QEvent::WindowStateChange:
            if(this->isMinimized())
            {
                event->ignore();// 截断事件
                hideWindow();
            }
            break;
        case QEvent::Close:
            event->ignore();// 截断事件
            hideWindow();
            return true;
            break;
        case QEvent::Resize:
            ui->tabWidget->setStyleSheet("QTabBar::tab {min-width:" + QString::number(this->width() / 10 - 3) + "px;min-height:50px;}");
            break;
        }
    }
    return false;
}
void MainWindow::keyPressEvent(QKeyEvent *keyEvent)
{
    switch(keyEvent->key())
    {
    case Qt::Key_Escape:
        hideWindow();
        break;
    case Qt::Key_C:
        if(keyEvent->modifiers() == Qt::ControlModifier)
        {
            QList<AppButton *> appButtonList = ui->tabWidget->currentWidget()->findChildren<AppButton *>();
            for(AppButton* btn : appButtonList) // 遍历所有AppButton，寻找当前鼠标指向的按钮
            {
                if(btn->isBeMousePointing())
                {
                    copyBtn(btn);
                }
            }
        }
        break;
    case Qt::Key_X:
        if(keyEvent->modifiers() == Qt::ControlModifier)
        {
            QList<AppButton *> appButtonList = ui->tabWidget->currentWidget()->findChildren<AppButton *>();
            for(AppButton* btn : appButtonList) // 遍历所有AppButton，寻找当前鼠标指向的按钮
            {
                if(btn->isBeMousePointing())
                {
                    shearBtn(btn);
                }
            }
        }
        break;
    case Qt::Key_V:
        if(keyEvent->modifiers() == Qt::ControlModifier)
        {
            QList<AppButton *> appButtonList = ui->tabWidget->currentWidget()->findChildren<AppButton *>();
            for(AppButton* btn : appButtonList) // 遍历所有AppButton
            {
                if(btn->isBeMousePointing())// 找到被鼠标指向的AppButton
                {
                    pasteBtn(btn);
                }
            }
        }
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
