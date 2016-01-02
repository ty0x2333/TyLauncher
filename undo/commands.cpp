#include "commands.h"
/**
 * @brief RemoveAppButtonCommand
 */
RemoveAppButtonCommand::RemoveAppButtonCommand(AppButton *appBtn, AppBtnInfo appBtnInfo, QUndoCommand *parent)
    : QUndoCommand(parent)
{
    setText(QObject::tr("Remove %1").arg(appBtnInfo.name()));
    _appBtn = appBtn;
    _appBtnInfo = appBtnInfo;
}

void RemoveAppButtonCommand::undo()
{
    _appBtn->setAppBtnInfo(_appBtnInfo);
}

void RemoveAppButtonCommand::redo()
{
    _appBtn->clear();
}
/**
 * @brief ReplaceAppButtonCommand
 */
ReplaceAppButtonCommand::ReplaceAppButtonCommand(AppButton *replacedAppBtn, AppBtnInfo appBtnInfo, AppBtnInfo replacedAppBtnInfo,QUndoCommand *parent)
    : QUndoCommand(parent)
{
    setText(QObject::tr("Replace %1 to %2").arg(replacedAppBtnInfo.name()).arg(appBtnInfo.name()));
    _replacedAppBtn = replacedAppBtn;
    _appBtnInfo = appBtnInfo;
    _replacedAppBtnInfo = replacedAppBtnInfo;
}
void ReplaceAppButtonCommand::undo()
{
    _replacedAppBtn->setAppBtnInfo(_replacedAppBtnInfo);
}

void ReplaceAppButtonCommand::redo()
{
    _replacedAppBtn->setAppBtnInfo(_appBtnInfo);
}
