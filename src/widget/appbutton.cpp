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
#include "appbutton.h"
#include <QMimeData>
#include <QUrl>
#include <QList>
#include <QFileInfo>
#include <QFileIconProvider>
#include <QVBoxLayout>
#include <QDesktopServices>
#include <QDir>
#include <QDragEnterEvent>
#include <QLabel>
#include "TyLog_Qt.h"

static const int kAppIconMargin = 10;

AppButton::AppButton(QWidget *parent)
    :QPushButton(parent)
    , _isBeMousePointing(false)
    , _fileName(QString())
    , _appName(nullptr)
    , _appIcon(nullptr)
{
    init();
}

AppButton::AppButton(const QString &text, QWidget *parent) :
    QPushButton(text, parent),
    _isBeMousePointing(false),
    _fileName(QString()),
    _appName(nullptr),
    _appIcon(nullptr)
{
    init();
}
AppButton::AppButton(const AppBtnInfo &appBtnInfo, QWidget *parent) :
    QPushButton(parent),
    _isBeMousePointing(false),
    _fileName(""),
    _appName(nullptr),
    _appIcon(nullptr)
{
    init();
    setAppBtnInfo(appBtnInfo);
}

void AppButton::setAppBtnInfo(const AppBtnInfo &appBtnInfo)
{
    this->setText(appBtnInfo.hotKey());
    setAppInfo(appBtnInfo);
}

AppBtnInfo AppButton::appBtnInfo()
{
    return AppBtnInfo(_appName->text(), _fileName, this->text());
}

void AppButton::setAppInfo(const AppInfo &appInfo)
{
    _appName->setText(appInfo.name());// 设置文件名
    // 设置文件路径
    if (appInfo.isEmpty()) {
        _fileName = QString();
        _appIcon->setPixmap(QPixmap());
    } else {
        setAppFileName(appInfo.fileName());
    }
}

AppInfo AppButton::appInfo()
{
    return AppInfo(_appName->text(), _fileName);
}

void AppButton::init()
{
    setStyleSheet("text-align:left top;");
    setSizePolicy(QSizePolicy::MinimumExpanding,QSizePolicy::MinimumExpanding);
    setAcceptDrops(true);
    
    _appIcon = new AppIconLabel(this);
    _appIcon->setMargin(kAppIconMargin);
    
    _appName = new QLabel(this);
    // Alignment Top Center
    _appName->setAlignment(Qt::AlignHCenter | Qt::AlignTop);
    _appName->setWordWrap(true);
    _appName->adjustSize();
    
    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(this->_appIcon);
    layout->addWidget(this->_appName);
    layout->setSpacing(0);
    setLayout(layout);
    
    connect(this, SIGNAL(clicked()), this, SLOT(on_clicked()));
    installEventFilter(this);
    setContextMenuPolicy(Qt::CustomContextMenu);
    
    int layoutMarginVertical = this->layout()->contentsMargins().top() + this->layout()->contentsMargins().bottom();
    setMinimumHeight(_appIcon->minimumHeight() + _appName->geometry().height() + layoutMarginVertical);
    
    // Test
//    _appName->setStyleSheet("background: green");
//    _appIcon->setStyleSheet("background: red");
}

void AppButton::openFileDirectory()
{
    if(_fileName.isEmpty())// 如果储存的路径为空,则跳出
        return;
    QFileInfo fileInfo(_fileName);
    QDesktopServices::openUrl(QUrl::fromLocalFile(fileInfo.path()));
}

void AppButton::on_clicked()
{
    if(_fileName.isEmpty())// 如果储存的路径为空,则跳出
        return;
    QDesktopServices::openUrl(QUrl::fromLocalFile(_fileName));
}
// @brief 拖拽文件进入
void AppButton::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasUrls())
           event->acceptProposedAction();
}
// @brief 拖拽文件释放
void AppButton::dropEvent(QDropEvent *event)
{
    QList<QUrl> urls = event->mimeData()->urls();
    if (urls.isEmpty()) {
        return;
    }
    _fileName = urls.first().toLocalFile();
    if (_fileName.isEmpty()) {
        return;
    }
    QFileInfo fileInfo(_fileName);
    QFileIconProvider iconProvider;
    
    if(fileInfo.isSymLink()) {
        _fileName = fileInfo.symLinkTarget();
    } else {
        _fileName = fileInfo.filePath();
    }
    _appName->setText(fileInfo.baseName());
    _appIcon->setIconFromFileName(_fileName);
}
// @brief 从其它按钮中拷贝数据
void AppButton::copyFrom(AppButton &btn)
{
    _appName->setText( btn.getAppName());
    _fileName = btn.getFileName();
    const QPixmap *pixmap = btn.getPixmap();
    if(pixmap != nullptr) {
        _appIcon->setPixmap(*pixmap);
    }
}
// @brief 清除按钮数据
void AppButton::clear()
{
    _fileName = "";
    _appName->clear();
    _appIcon->clear();
}

QString AppButton::getFileName(){return _fileName;}
const QPixmap* AppButton::getPixmap(){return _appIcon->pixmap();}
// @brief 判断是否被鼠标所指向
// @param[out] 是否被鼠标指向
bool AppButton::isBeMousePointing(){return _isBeMousePointing;}

void AppButton::setAppFileName(const QString &fileName)
{
    if (_fileName == fileName) {
        return;
    }
    _fileName = fileName;
    QFileInfo fileInfo(_fileName);
    QFileIconProvider iconProvider;
    if(fileInfo.exists()) {
        _appIcon->setIcon(iconProvider.icon(fileInfo));
    } else {
        _appIcon->setIcon(iconProvider.icon(QFileIconProvider::File));
    }
}
bool AppButton::eventFilter(QObject *, QEvent *event)
{
    if(event->type() == QEvent::Enter)
        _isBeMousePointing = true;
    else if(event->type() == QEvent::Leave)
        _isBeMousePointing = false;
    return false;
}
// @brief 指示按钮是否为空
bool AppButton::isEmpty()
{
    return _fileName.isEmpty() && _appName->text().isEmpty();
}

void AppButton::setAppName(const QString &text){_appName->setText(text);}
QString AppButton::getAppName(){return _appName->text();}
