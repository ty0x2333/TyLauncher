#include "shearplateutils.h"
#include "dynamicdata.h"
#include "AppButton.h"

bool ShearPlateUtils::copy(AppButton *btn)
{
    if(btn->isEmpty())
        return false;
    DynamicData::getInstance()->setBtnShearPlate(btn);
    return true;
}

void ShearPlateUtils::shear(AppButton *btn)
{
    if(copy(btn))
        btn->clear();// 在复制成功的情况下清除按钮
}

void ShearPlateUtils::paste(AppButton *btn)
{
    if(DynamicData::getInstance()->BtnShearPlateIsEmpty())
        return;
    if(!btn->isEmpty()){
//        _isCanHide = false;
//        if( UIUtils::showWarnMsgBox(tr("Replace the button?"), this) == QMessageBox::Yes)
//            btn->copyFrom(*DynamicData::getInstance()->getBtnShearPlate());
//        _isCanHide = true;
    }else{
        btn->copyFrom(*DynamicData::getInstance()->getBtnShearPlate());
    }
}

void ShearPlateUtils::remove(AppButton *btn)
{
    if (btn->isEmpty())
        return;
//    _isCanHide = false;
//    if( UIUtils::showWarnMsgBox(tr("Delete the button?"), this) == QMessageBox::Yes){
//        btn->clear();
//    }
//    _isCanHide = true;
}
