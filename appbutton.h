#ifndef APPBUTTON_H
#define APPBUTTON_H

#include <QPushButton>
#include <QDragEnterEvent>
#include <QLabel>
class AppButton : public QPushButton
{
    Q_OBJECT
public:
    explicit AppButton(const QString &text, QWidget *parent=0);
    explicit AppButton(const QString &text, const QString &fileName, QWidget *parent=0);
    QString getFileName();
    QString getAppName();
    bool isBeMousePointing();
    // @brief 从其它按钮中拷贝数据
    void copyFrom(AppButton &btn);
    // @brief 清除按钮数据
    void clear();
    void setAppName(const QString &text);
    // @brief 打开所在文件夹
    void openFileDirectory();
    ~AppButton();
signals:
    
public slots:
    void on_clicked();
protected:
    // @brief 拖拽文件进入
    void dragEnterEvent(QDragEnterEvent *);
    // @brief 拖拽文件释放
    void dropEvent(QDropEvent *);
    bool eventFilter(QObject *, QEvent *);
private:
    // @brief 是否被鼠标指着
    bool _isBeMousePointing;
    // @brief 文件路径
    QString _fileName;
    // @brief 应用名称
    QLabel *_appName;
    // @brief 应用图标
    QLabel *_appIcon;
    void init();
};

#endif // APPBUTTON_H
