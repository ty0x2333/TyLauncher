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
#ifndef APPBUTTON_H
#define APPBUTTON_H

#include <QPushButton>
#include "model/appbtninfo.h"
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
    explicit AppButton(const AppBtnInfo &appBtnInfo, QWidget *parent=0);
    
    void setAppBtnInfo(const AppBtnInfo &appBtnInfo);
    AppBtnInfo appBtnInfo();
    
    /**
     * @brief setAppInfo
     * 
     * @note  icon will remove when appInfo is empty.
     * @param appInfo
     */
    void setAppInfo(const AppInfo &appInfo);
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
