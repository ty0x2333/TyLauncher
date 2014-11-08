#ifndef DYNAMICDATA_H
#define DYNAMICDATA_H
#include "appbutton.h"
class DynamicData
{
public:
    static DynamicData* getInstance();
    // @brief 获取按钮剪切缓存
    AppButton* getBtnShearPlate();
    // @brief 设置按钮剪切缓存
    void setBtnShearPlate(AppButton *btn);
    // @brief 获取按钮剪切缓存是否为空
    bool BtnShearPlateIsEmpty();
private:
    DynamicData();
    // @brief 按钮剪切缓存
    // 用来保存复制的按钮地址
    AppButton *_btnShearPlate;
};

#endif // DYNAMICDATA_H
