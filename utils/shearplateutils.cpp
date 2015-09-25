#include "shearplateutils.h"
#include "dynamicdata.h"
#include "AppButton.h"
#include "utils/uiutils.h"
#include <QObject>

bool ShearPlateUtils::copy(AppButton *btn)
{
    if(btn->isEmpty())
        return false;
    DYNAMIC_DATA->setBtnShearPlate(btn);
    return true;
}

void ShearPlateUtils::shear(AppButton *btn)
{
    if(copy(btn))
        btn->clear();// 在复制成功的情况下清除按钮
}

void ShearPlateUtils::paste(AppButton *btn)
{
    if(DYNAMIC_DATA->BtnShearPlateIsEmpty())
        return;
    if(!btn->isEmpty()){
        if( UIUtils::showWarnMsgBox(QObject::tr("Replace the button?")) == QMessageBox::Ok)
            btn->copyFrom(*DYNAMIC_DATA->getBtnShearPlate());
    }else{
        btn->copyFrom(*DYNAMIC_DATA->getBtnShearPlate());
    }
}

void ShearPlateUtils::remove(AppButton *btn)
{
    if (btn->isEmpty())
        return;
    if( UIUtils::showWarnMsgBox(QObject::tr("Delete the button?")) == QMessageBox::Ok){
        btn->clear();
    }
}
