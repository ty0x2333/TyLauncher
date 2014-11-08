#include "dynamicdata.h"
#include <QSettings>
#include "StaticSetting.h"
static DynamicData *s_shareDynamicData = nullptr;
DynamicData::DynamicData():
    _btnShearPlate(nullptr),
    _theme(""),
    _saveFileName(SAVE_FILE)
{
}
DynamicData* DynamicData::getInstance()
{
    if(s_shareDynamicData == nullptr)
    {
        s_shareDynamicData = new DynamicData();
        s_shareDynamicData->loadSettings();// 读取设置
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
// @brief 保存设置
void DynamicData::saveSettings()
{
    QSettings *configIniWrite = new QSettings(CONFIG_FILE, QSettings::IniFormat);
    configIniWrite->setValue("theme", _theme);
    configIniWrite->setValue("filename/save", _saveFileName);
    qDebug(configIniWrite->fileName().toUtf8());
    delete configIniWrite;// 使用完后销毁
}
// @brief 读取设置
void DynamicData::loadSettings()
{
    QSettings *configIniRead = new QSettings(CONFIG_FILE, QSettings::IniFormat);
    _theme = configIniRead->value("theme", ":/css/res/default.qss").toString();
    _saveFileName = configIniRead->value("filename/save", SAVE_FILE).toString();
    qDebug(_theme.toUtf8());// 输出读取的内容
    delete configIniRead;;// 使用完后销毁
}
// @brief 获取主题
QString DynamicData::getTheme()
{
    return _theme;
}
// @brief 设置存档路径
void DynamicData::setSaveFileName(const QString &fileName)
{
    _saveFileName = fileName;
}
// @brief 获取存档路径
QString DynamicData::getSaveFileName()
{
    return _saveFileName;
}
// @brief 重置存档路径
void DynamicData::resetSaveFileName()
{
    _saveFileName = SAVE_FILE;
}
// @brief 设置主题
void DynamicData::setTheme(const QString &theme)
{
    _theme = theme;
}

bool DynamicData::BtnShearPlateIsEmpty(){    return _btnShearPlate == nullptr;}
