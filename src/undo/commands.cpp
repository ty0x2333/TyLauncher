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
#include "commands.h"
/**
 * @brief RemoveAppButtonCommand
 */
RemoveAppButtonCommand::RemoveAppButtonCommand(AppButton *appBtn, AppInfo appInfo, QUndoCommand *parent)
    : QUndoCommand(parent)
{
    setText(QObject::tr("Remove %1").arg(appInfo.name()));
    _appBtn = appBtn;
    _appInfo = appInfo;
}

void RemoveAppButtonCommand::undo()
{
    _appBtn->setAppInfo(_appInfo);
}

void RemoveAppButtonCommand::redo()
{
    _appBtn->clear();
}
/**
 * @brief ReplaceAppButtonCommand
 */
ReplaceAppButtonCommand::ReplaceAppButtonCommand(AppButton *replacedAppBtn, AppInfo appInfo, AppInfo replacedAppInfo,QUndoCommand *parent)
    : QUndoCommand(parent)
{
    setText(QObject::tr("Replace %1 to %2").arg(replacedAppInfo.name()).arg(appInfo.name()));
    _replacedAppBtn = replacedAppBtn;
    _appInfo = appInfo;
    _replacedAppInfo = replacedAppInfo;
}
void ReplaceAppButtonCommand::undo()
{
    _replacedAppBtn->setAppInfo(_replacedAppInfo);
}

void ReplaceAppButtonCommand::redo()
{
    _replacedAppBtn->setAppInfo(_appInfo);
}
