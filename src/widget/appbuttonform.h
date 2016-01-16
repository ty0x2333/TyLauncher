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
#ifndef APPBUTTONFORM_H
#define APPBUTTONFORM_H

#include <QWidget>
#include <QVector>

QT_FORWARD_DECLARE_CLASS(AppButton)
QT_FORWARD_DECLARE_CLASS(AppBtnInfo)
QT_FORWARD_DECLARE_CLASS(QJsonArray)
QT_FORWARD_DECLARE_CLASS(QMenu)

namespace Ui {
class AppButtonForm;
}

class AppButtonForm : public QWidget
{
    Q_OBJECT
    
public:
    explicit AppButtonForm(const int &rowCount, const int &columnCount, QWidget *parent = 0);
    ~AppButtonForm();
    
    bool configFromVector(QVector<AppBtnInfo> dataVector);
    QJsonArray jsonArray() const;
    /**
     * @brief clear all app button data
     * @note  hotkey will not clear.
     */
    void clearAllAppBtnData();
private slots:
    void onAppButtonRightClicked(QPoint);
    void on_actionOpenFolder_triggered();
    void on_actionDelete_triggered();
    void on_actionCopy_triggered();
    void on_actionShear_triggered();
    void on_actionPaste_triggered();
    void on_actionEdit_triggered();
private:
    Ui::AppButtonForm *ui;
    int _rowCount;
    int _columnCount;
    /**
     * @brief 按钮右键菜单缓存
     * 用来保存右键菜单的按钮地址
     */
    AppButton *_btnCurMenu;
    /// @brief 按钮右键菜单
    QMenu *_btnMenu;
    
    void initBtnRightMenu();
};

#endif // APPBUTTONFORM_H
