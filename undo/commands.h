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
