#include "dynamicdata.h"

static DynamicData *s_shareDynamicData = nullptr;
DynamicData::DynamicData():
    _btnShearPlate(nullptr)
{
}
DynamicData* DynamicData::getInstance()
{
    if(s_shareDynamicData == nullptr)
    {
        s_shareDynamicData = new DynamicData();
    }
    return s_shareDynamicData;
}
// @brief 获取按钮剪切缓存
AppButton* DynamicData::getBtnShearPlate(){    return _btnShearPlate;}
// @brief 设置按钮剪切缓存
void DynamicData::setBtnShearPlate(AppButton *btn)
{
    if(_btnShearPlate != nullptr)
    {
        delete _btnShearPlate;
        _btnShearPlate = nullptr;
    }
    _btnShearPlate = new AppButton("");
    _btnShearPlate->copyFrom(*btn);
}
bool DynamicData::BtnShearPlateIsEmpty(){    return _btnShearPlate == nullptr;}
