#ifndef COMMANDS_H
#define COMMANDS_H

#include <QUndoCommand>
#include "widget/appbutton.h"

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

#endif // COMMANDS_H
