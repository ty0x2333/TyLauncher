#include "shearplateutils.h"
#include "dynamicdata.h"
#include "widget/appbutton.h"
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
    if(DYNAMIC_DATA->isBtnShearPlateEmpty())
        return;
    if(!btn->isEmpty()){
        if( UIUtils::showQuestionMsgBox(QObject::tr("Replace the button"), QObject::tr("Replace the button\nThe target button data will be erased.")) == QMessageBox::Yes)
            btn->copyFrom(*DYNAMIC_DATA->getBtnShearPlate());
    }else{
        btn->copyFrom(*DYNAMIC_DATA->getBtnShearPlate());
    }
}

void ShearPlateUtils::remove(AppButton *btn)
{
    if (btn->isEmpty())
        return;
    if( UIUtils::showQuestionMsgBox(QObject::tr("Delete the button"), QObject::tr("Delete the button\nThe target button data will be erased.")) == QMessageBox::Yes){
        btn->clear();
    }
}
