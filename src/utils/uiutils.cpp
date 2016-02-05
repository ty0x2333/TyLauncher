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
#include "uiutils.h"
#include <QObject>

int UIUtils::showCriticalMsgBox(const QString &content, QWidget *parent, QMessageBox::StandardButton buttons)
{
    return showMessageBox(QMessageBox::Critical, QObject::tr(kCriticalMsgBoxTitle), content, parent, buttons);
}

int UIUtils::showInfoMsgBox(const QString &content, QWidget *parent, QMessageBox::StandardButton buttons)
{
    return showMessageBox(QMessageBox::Information, QObject::tr(kInfomationMsgBoxTitle), content, parent, buttons);
}

int UIUtils::showWarnMsgBox(const QString &content, QWidget *parent, QMessageBox::StandardButton buttons)
{
    return showMessageBox(QMessageBox::Warning, QObject::tr(kWarningMsgBoxTitle), content, parent, buttons);
}

int UIUtils::showQuestionMsgBox(const QString &title, const QString &content, QWidget *parent)
{
    return showMessageBox(QMessageBox::Question, title, content, parent, QMessageBox::Yes | QMessageBox::No);
}

int UIUtils::showMessageBox(QMessageBox::Icon icon, const QString &title, const QString &content, QWidget *parent, QMessageBox::StandardButtons buttons)
{
    QMessageBox msgBox(icon, title, content, buttons, parent, Qt::WindowStaysOnTopHint);
    return msgBox.exec();
}

