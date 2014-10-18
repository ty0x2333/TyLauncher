#include "appbutton.h"
#include <QMimeData>
#include <QUrl>
#include <QList>
#include <QFileInfo>
#include <QFileIconProvider>
#include <QVBoxLayout>
#include <QDesktopServices>
#include <QDir>
AppButton::AppButton(const QString &text, QWidget *parent) :
    QPushButton(text, parent),
    _isBeMousePointing(false),
    _fileName(""),
    _appName(nullptr),
    _appIcon(nullptr)
{
    init();
}
AppButton::AppButton(const QString &text, const QString &fileName, QWidget *parent) :
    QPushButton(text, parent),
    _isBeMousePointing(false),
    _appName(nullptr),
    _appIcon(nullptr)
{
    init();
    if(fileName.isEmpty())
    {
        _fileName = "";
        return;
    }
    QFile file(fileName);
    if(file.open(QFile::ReadOnly))
    {
        _fileName = fileName;
        QFileInfo fileInfo(_fileName);
        QFileIconProvider iconProvider;
        _appName->setText(fileInfo.baseName());
        _appIcon->setPixmap(iconProvider.icon(fileInfo).pixmap(QSize(48, 48)));
    }
    else
    {
        _fileName = "";
    }
    file.close();
}
// @brief 初始化
// 用于在构造函数中调用
void AppButton::init()
{
    setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    setAcceptDrops(true);// 允许拖拽
    _appIcon = new QLabel();
    _appIcon->setAlignment(Qt::AlignHCenter | Qt::AlignCenter);// 设置图标位置为正中
    //_appIcon->setStyleSheet("border:2px solid #00F");
    _appName = new QLabel();
    _appName->setAlignment(Qt::AlignHCenter | Qt::AlignTop);// 设置文本位置为中上
    _appName->setWordWrap(true);// 允许自动换行
    _appName->adjustSize();
    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(this->_appIcon);
    layout->addWidget(this->_appName);
    setLayout(layout);
    connect(this, SIGNAL(clicked()), this, SLOT(on_clicked()));
    installEventFilter(this);
    setContextMenuPolicy(Qt::CustomContextMenu);
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
    if (urls.isEmpty())
        return;
    _fileName = urls.first().toLocalFile();
    if (_fileName.isEmpty())
        return;
    QFileInfo fileInfo(_fileName);
    QFileIconProvider iconProvider;
    
    if(fileInfo.isSymLink())
    {
        _fileName = fileInfo.symLinkTarget();
    }
    else
    {
        _fileName = fileInfo.filePath();
    }
    _appName->setText(fileInfo.baseName());
    qDebug("Icon Type : %s", iconProvider.type(QFileInfo(_fileName)).toUtf8().data());
    _appIcon->setPixmap(iconProvider.icon(QFileInfo(_fileName)).pixmap(QSize(48, 48)));
}
// @brief 从其它按钮中拷贝数据
void AppButton::copyFrom(AppButton &btn)
{
    _appName->setText( btn.getAppName());
    _fileName = btn.getFileName();
    QFileInfo fileInfo(_fileName);
    QFileIconProvider iconProvider;
    _appName->setText(fileInfo.baseName());
    _appIcon->setPixmap(iconProvider.icon(fileInfo).pixmap(QSize(48, 48)));
}
// @brief 清除按钮数据
void AppButton::clear()
{
    _fileName = "";
    _appName->clear();
    _appIcon->clear();
}

QString AppButton::getFileName(){return _fileName;}
QString AppButton::getAppName(){return _appName->text();}
const QPixmap* AppButton::getPixmap(){return _appIcon->pixmap();}
// @brief 判断是否被鼠标所指向
// @param[out] 是否被鼠标指向
bool AppButton::isBeMousePointing(){return _isBeMousePointing;}
// @brief 设置应用名称
// @param[in] 名称
void AppButton::setAppName(const QString &text){_appName->setText(text);}
// @brief 设置应用路径
// @param[in] 应用路径
// @param[in] 是否更新图标
void AppButton::setAppFileName(const QString &fileName, bool isUpdateIcon)
{
    _fileName = fileName;
    if(isUpdateIcon)
    {
        QFileInfo fileInfo(_fileName);
        QFileIconProvider iconProvider;
        _appName->setText(fileInfo.baseName());
        _appIcon->setPixmap(iconProvider.icon(fileInfo).pixmap(QSize(48, 48)));
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
AppButton::~AppButton()
{
    delete _appName;
    delete _appIcon;
}
