#include "shearplate.h"
#include "widget/appbutton.h"
#include "utils/uiutils.h"
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
    if(copy(btn))
        btn->clear();// 在复制成功的情况下清除按钮
}

void ShearPlate::paste(AppButton *btn)
{
    if(this->isBtnShearPlateEmpty())
        return;
    if(!btn->isEmpty()){
        if( UIUtils::showQuestionMsgBox(QObject::tr("Replace the button"), QObject::tr("Replace the button\nThe target button data will be erased.")) == QMessageBox::Yes)
            btn->copyFrom(*_btnShearPlate);
    }else{
        btn->copyFrom(*_btnShearPlate);
    }
}

void ShearPlate::remove(AppButton *btn)
{
    if (btn->isEmpty())
        return;
    if( UIUtils::showQuestionMsgBox(QObject::tr("Delete the button"), QObject::tr("Delete the button\nThe target button data will be erased.")) == QMessageBox::Yes){
        btn->clear();
    }
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
