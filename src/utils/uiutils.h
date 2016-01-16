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
#ifndef __UI_UTILS_H__
#define __UI_UTILS_H__
#include <QString>
#include <QMessageBox>

#define kCriticalMsgBoxTitle "Error"
#define kInfomationMsgBoxTitle "Information"
#define kWarningMsgBoxTitle "Warning"

class UIUtils
{
public:
    static int showCriticalMsgBox(const QString &content, QWidget *parent = 0, QMessageBox::StandardButton buttons = QMessageBox::Ok);
    static int showInfoMsgBox(const QString &content,  QWidget *parent = 0, QMessageBox::StandardButton buttons = QMessageBox::Ok);
    static int showWarnMsgBox(const QString &content, QWidget *parent = 0 , QMessageBox::StandardButton buttons = QMessageBox::Ok);
    static int showQuestionMsgBox(const QString &title, const QString &content, QWidget *parent = 0);
    /**
     * @brief showMessageBox
     * @param icon MessageBox Icon
     * @param title Dialog Title
     * @param content Message
     * @param parent Parent QWidget
     * @param buttons Dialog Buttons
     * @return Clicked Button Code
     */
    static int showMessageBox(QMessageBox::Icon icon, const QString &title, const QString &content, QWidget *parent = 0, QMessageBox::StandardButtons buttons = QMessageBox::Ok);
};

#endif // __UI_UTILS_H__
