#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <QSystemTrayIcon>
#include <QCloseEvent>
#include "aboutdialog.h"
#include "appbutton.h"
#include "StaticSetting.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    // @brief 保存设置
    void saveSettings();
    // @brief 还原窗口
    virtual void restoreWindow();
    // @brief 隐藏窗口
    void hideWindow();
    // @brief 设置是否可以隐藏窗口
    void setisCanHide(bool val);
    ~MainWindow();
private slots:
    // @brief 托盘图标点击
    void onSystemTrayIconClicked(QSystemTrayIcon::ActivationReason reason);
    // @brief 退出菜单项响应
    // 这里包括 托盘菜单 以及 菜单栏中文件菜单的退出菜单项
    void on_Quit_triggered();
    void on_hotKey_triggered();
    // @brief 托盘菜单的显示主界面菜单项响应
    void on_actionShowWindow_triggered();
    // @brief "关于"菜单项被点击
    void on_actionAbout_triggered();
    // @brief "设置热键"菜单项被点击
    void on_actionHotKey_triggered();
    // @brief 按钮右键点击响应
    void onBtnRightClicked(QPoint);
    // @brief 按钮右键菜单中的打开文件夹菜单项被点击
    void on_actionActionBtnOpenDir_triggered();
    // @brief 按钮右键菜单中的复制菜单项被点击
    void on_actionCopy_triggered();
    // @brief 按钮右键菜单中的粘贴菜单项被点击
    void on_actionPaste_triggered();
    // @brief 按钮右键菜单中的剪切菜单项被点击
    void on_actionShear_triggered();
    // @brief 按钮右键菜单中的删除菜单项被点击
    void on_actionDelete_triggered();
    // @brief 按钮右键菜单中的编辑菜单项被点击
    void on_actionEdit_triggered();
    // @brief "保存"菜单项响应
    void on_actionSave_triggered();
    
private:
    Ui::MainWindow *ui;
    // @brief 是否可以隐藏
    bool _isCanHide;
    // @brief 托盘图标
    QSystemTrayIcon *_trayIcon;
    // @brief 托盘菜单
    QMenu *_trayMenu;
    // @brief 按钮右键菜单
    QMenu *_btnMenu;
    // @brief 关于对话框
    AboutDialog *_aboutDialog;
    // @brief 读取存档文件
    bool loadSaveFile(const QString fileName);
    // @brief 重置数据
    void reset();
    // @brief 按钮剪切缓存
    // 用来保存复制的按钮地址
    AppButton *_btnShearPlate;
    // @brief 按钮右键菜单缓存
    // 用来保存右键菜单的按钮地址
    AppButton *_btnRightMenu;
    // @brief 复制按钮
    // @param[out] 是否操作成功
    bool copyBtn(AppButton *btn);
    // @brief 剪切按钮
    void shearBtn(AppButton *btn);
    // @brief 粘贴按钮
    void pasteBtn(AppButton *btn);
    // @brief 删除按钮
    void deleteBtn(AppButton *btn);
protected:
    virtual bool eventFilter(QObject *, QEvent *);
    virtual void keyPressEvent(QKeyEvent *);
};

#endif // MAINWINDOW_H
