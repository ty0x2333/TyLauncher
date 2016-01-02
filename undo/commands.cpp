#include "commands.h"

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
