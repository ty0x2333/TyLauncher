#ifndef APPBUTTON_H
#define APPBUTTON_H

#include <QPushButton>
#include "model/appinfo.h"
QT_BEGIN_NAMESPACE
class QDragEnterEvent;
class QLabel;
QT_END_NAMESPACE

class AppButton : public QPushButton
{
    Q_OBJECT
public:
    explicit AppButton(QWidget *parent=0);
    explicit AppButton(const QString &text, QWidget *parent=0);
    explicit AppButton(const AppInfo &appInfo, QWidget *parent=0);
    
    void setDataFromAppInfo(const AppInfo &appInfo);
    
    AppInfo appInfo();
    
    QString getFileName();
    
    /// @brief 是否被鼠标所指向
    bool isBeMousePointing();
    /// @brief 从其它按钮中拷贝数据
    void copyFrom(AppButton &btn);
    /// @brief 清除按钮数据
    void clear();
    /**
     * @brief 设置应用名称
     * @param text 名称
     */
    void setAppName(const QString &text);
    QString getAppName();
    
    /**
     * @brief 设置应用路径
     * @param fileName 应用路径
     */
    void setAppFileName(const QString &fileName);
    
    /// @brief 打开所在文件夹
    void openFileDirectory();
    /// @brief 获取图标
    const QPixmap* getPixmap();
    /// @brief 指示按钮是否为空
    bool isEmpty();
    ~AppButton();
signals:
    
public slots:
    void on_clicked();
protected:
    /// @brief 拖拽文件进入
    void dragEnterEvent(QDragEnterEvent *);
    /// @brief 拖拽文件释放
    void dropEvent(QDropEvent *);
    bool eventFilter(QObject *, QEvent *);
private:
    /// @brief 是否被鼠标指着
    bool _isBeMousePointing;
    /// @brief 文件路径
    QString _fileName;
    /// @brief 应用名称
    QLabel *_appName;
    /// @brief 应用图标
    QLabel *_appIcon;
    /**
     * @brief 初始化
     * 用于在构造函数中调用
     */
    void init();
};

#endif // APPBUTTON_H
