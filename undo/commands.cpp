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
    _appBtn->setDataFromAppInfo(_appInfo);
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
    _replacedAppBtn->setDataFromAppInfo(_replacedAppInfo);
}

void ReplaceAppButtonCommand::redo()
{
    _replacedAppBtn->setDataFromAppInfo(_appInfo);
}
