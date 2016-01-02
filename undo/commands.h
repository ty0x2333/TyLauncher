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
    RemoveAppButtonCommand(AppButton *appBtn, AppBtnInfo appBtnInfo, QUndoCommand *parent = 0);
    void undo() Q_DECL_OVERRIDE;
    void redo() Q_DECL_OVERRIDE;

private:
    AppButton *_appBtn;
    AppBtnInfo _appBtnInfo;
};

/**
 * @brief ReplaceAppButtonCommand
 */
class ReplaceAppButtonCommand : public QUndoCommand
{
public:
    ReplaceAppButtonCommand(AppButton *replacedAppBtn, AppBtnInfo appBtnInfo, AppBtnInfo replacedAppBtnInfo,QUndoCommand *parent = 0);
    void undo() Q_DECL_OVERRIDE;
    void redo() Q_DECL_OVERRIDE;

private:
    AppButton *_replacedAppBtn;
    AppBtnInfo _appBtnInfo;
    AppBtnInfo _replacedAppBtnInfo;
};

#endif // COMMANDS_H
