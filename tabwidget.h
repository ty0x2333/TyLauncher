#ifndef TABWIDGET_H
#define TABWIDGET_H

#include <QTabWidget>
#include <QString>
#include "model/appinfo.h"
QT_BEGIN_NAMESPACE
class QMenu;
class AppButton;
QT_END_NAMESPACE

namespace Ui {
class TabWidget;
}

class TabWidget : public QTabWidget
{
    Q_OBJECT
    
public:
    explicit TabWidget(QWidget *parent = 0);
    ~TabWidget();
    QString jsonString();
    bool configFromVector(QVector<QVector<AppInfo>>);
    /**
     * @brief clear all app button data
     * @note  hotkey will not clear.
     */
    void clearAllAppBtnData();
    
//    void setAppButtonsRightMenu
//    const char *readyReadMember
    
private slots:
    /// @brief 按钮右键点击响应
    void onAppButtonRightClicked(QPoint);
    /// @brief 按钮右键菜单中的打开文件夹菜单项被点击
    void on_actionOpenFolder_triggered();
    /// @brief 按钮右键菜单中的删除菜单项被点击
    void on_actionDelete_triggered();
    /// @brief 按钮右键菜单中的复制菜单项被点击
    void on_actionCopy_triggered();
    /// @brief 按钮右键菜单中的剪切菜单项被点击
    void on_actionShear_triggered();
    /// @brief 按钮右键菜单中的粘贴菜单项被点击
    void on_actionPaste_triggered();
    // @brief 按钮右键菜单中的编辑菜单项被点击
    void on_actionEdit_triggered();
    
private:
    Ui::TabWidget *ui;
    int _rowCount;
    int _columnCount;
    /**
     * @brief 按钮右键菜单缓存
     * 用来保存右键菜单的按钮地址
     */
    AppButton *_btnCurMenu;
    /// @brief 按钮右键菜单
    QMenu *_btnMenu;
    void initTabs();
    /// @brief 初始化按钮右键菜单
    void initBtnRightMenu();
};

#endif // TABWIDGET_H
