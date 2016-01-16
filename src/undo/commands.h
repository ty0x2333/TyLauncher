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
#ifndef COMMANDS_H
#define COMMANDS_H

#include <QUndoCommand>
#include "widget/appbutton.h"
/**
 * @brief RemoveAppButtonCommand
 */
class RemoveAppButtonCommand : public QUndoCommand
{
public:
    RemoveAppButtonCommand(AppButton *appBtn, AppInfo appInfo, QUndoCommand *parent = 0);
    void undo() Q_DECL_OVERRIDE;
    void redo() Q_DECL_OVERRIDE;

private:
    AppButton *_appBtn;
    AppInfo _appInfo;
};

/**
 * @brief ReplaceAppButtonCommand
 */
class ReplaceAppButtonCommand : public QUndoCommand
{
public:
    ReplaceAppButtonCommand(AppButton *replacedAppBtn, AppInfo appInfo, AppInfo replacedAppInfo, QUndoCommand *parent = 0);
    void undo() Q_DECL_OVERRIDE;
    void redo() Q_DECL_OVERRIDE;

private:
    AppButton *_replacedAppBtn;
    AppInfo _appInfo;
    AppInfo _replacedAppInfo;
};

#endif // COMMANDS_H
