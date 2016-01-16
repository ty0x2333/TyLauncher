#include "shearplate.h"
#include "widget/appbutton.h"
#include "utils/uiutils.h"
#include "undo/commands.h"
#include <QUndoStack>
static ShearPlate *s_shareShearPlate = nullptr;
ShearPlate* ShearPlate::getInstance()
{
    if(s_shareShearPlate == nullptr){
        s_shareShearPlate = new ShearPlate();
    }
    return s_shareShearPlate;
}

ShearPlate::ShearPlate(QObject *parent) 
    : QObject(parent)
    , _btnShearPlate(nullptr)
{
    _undoStack = new QUndoStack(this);
}

bool ShearPlate::copy(AppButton *btn)
{
    if(btn->isEmpty())
        return false;
    this->setBtnShearPlate(btn);
    return true;
}

void ShearPlate::shear(AppButton *btn)
{
    if(copy(btn)) {
        clearBtn(btn);
    }
}

void ShearPlate::paste(AppButton *btn)
{
    if(this->isBtnShearPlateEmpty())
        return;
    AppInfo replacedinfo = btn->appInfo();
    if(!btn->isEmpty()){
        if( UIUtils::showQuestionMsgBox(QObject::tr("Replace the button"), QObject::tr("Replace the button\nThe target button data will be erased.")) == QMessageBox::Yes)
            btn->copyFrom(*_btnShearPlate);
    }else{
        btn->copyFrom(*_btnShearPlate);
    }
    _btnShearPlate->appInfo();
    _undoStack->push(new ReplaceAppButtonCommand(btn, _btnShearPlate->appInfo(), replacedinfo));
}

void ShearPlate::remove(AppButton *btn)
{
    if (btn->isEmpty())
        return;
    if( UIUtils::showQuestionMsgBox(QObject::tr("Delete the button"), QObject::tr("Delete the button\nThe target button data will be erased.")) != QMessageBox::Yes){
        return;
    }
    clearBtn(btn);
}

void ShearPlate::undo()
{
    _undoStack->undo();
}

void ShearPlate::redo()
{
    _undoStack->redo();
}

// @brief 获取按钮剪切缓存
AppButton* ShearPlate::getBtnShearPlate(){return _btnShearPlate;}
// @brief 设置按钮剪切缓存
void ShearPlate::setBtnShearPlate(AppButton *btn)
{
    if(_btnShearPlate != nullptr){
        delete _btnShearPlate;
        _btnShearPlate = nullptr;
    }
    _btnShearPlate = new AppButton("");
    _btnShearPlate->copyFrom(*btn);
}

bool ShearPlate::isBtnShearPlateEmpty(){    return _btnShearPlate == nullptr;}

QUndoStack *ShearPlate::undoStack() const
{
    return _undoStack;
}

void ShearPlate::clearBtn(AppButton *btn)
{
    AppInfo info = btn->appInfo();
    btn->clear();
    _undoStack->push(new RemoveAppButtonCommand(btn, info));
}
