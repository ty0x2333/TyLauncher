#include "dynamicdata.h"
#include "StaticSetting.h"
#include "appbutton.h"
#include <QSettings>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QString>
#include <QLocale>
#include <QFile>
static DynamicData *s_shareDynamicData = nullptr;
DynamicData::DynamicData():
    _btnShearPlate(nullptr),
    _theme(""),
    _language(""),
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
    configIniWrite->setValue("language", _language);
    //qDebug(configIniWrite->fileName().toUtf8());
    delete configIniWrite;// 使用完后销毁
}
// @brief 读取设置
void DynamicData::loadSettings()
{
    QSettings *configIniRead = new QSettings(CONFIG_FILE, QSettings::IniFormat);
    _theme = configIniRead->value("theme", ":/css/res/default.qss").toString();
    _saveFileName = configIniRead->value("filename/save", SAVE_FILE).toString();
    _language = configIniRead->value("language", "").toString();
    if(_language.isEmpty())// 当取不到语言设置时,使用系统当前语言
        _language = QLocale::system().name();
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

// @brief 读取存档文件
QVector<QVector<AppInfo>> DynamicData::loadSaveFile(const QString fileName)
{
    QVector<QVector<AppInfo>> tabVector;
    QFile file(fileName);
    if(!file.exists())// 当存档文件不存在时,丢出异常,重新建立存档
        throw QString("");
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
        throw QString("Open Save File Failure");
        
    QJsonParseError parseErr;
    QJsonDocument doc = QJsonDocument::fromJson(file.readAll(),&parseErr);
    if(parseErr.error != QJsonParseError::NoError)
         throw QString("Save File failure!");
    if(!doc.isArray())
        throw QString("Save File Failure!");
    QJsonArray tabArr = doc.array();
    for(int i = 0; i < 10; ++i)// 每一个Tab
    {
        QVector<AppInfo> btnVector;
        QJsonValue val = tabArr.at(i);
        if(!val.isArray())
            throw QString("Save File Failure!");
        QJsonArray arr = val.toArray();
        for(int i = 0; i < arr.count(); ++i)
        {
            QJsonValue valObj = arr.at(i);
            if(!valObj.isObject())
                throw QString("Save File Failure!");
            QJsonObject obj = valObj.toObject();
            AppInfo appInfo(obj[XML_KEY_APP_NAME].toString(), obj[XML_KEY_FILE_NAME].toString());
            appInfo.hotKey = obj[XML_KEY_HOT_KEY].toString();
            btnVector.append(appInfo);
        }
        tabVector.append(btnVector);
    }
    
    return tabVector;
}
QString DynamicData::getLanguage(){    return _language;}
// @brief 设置语言
void DynamicData::setLanguage(const QString &language){ _language = language;}
