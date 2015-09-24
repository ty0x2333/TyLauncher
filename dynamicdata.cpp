#include "dynamicdata.h"
#include "StaticSetting.h"
#include "model/appinfo.h"
#include "appbutton.h"
#include <QSettings>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QString>
#include <QLocale>
#include <QFile>
#include <QDir>
#include <QStandardPaths>
#include <QTextStream>
#include "TyLog_Qt.h"
#include "datasettings.h"
#include <QObject>
#include <QApplication>
#include <QStringList>
static DynamicData *s_shareDynamicData = nullptr;
DynamicData::DynamicData()
    : _btnShearPlate(nullptr)
    , _theme(QString())
    , _language(QString())
    , _userSettingsFileNames(QString())
{
}

QString DynamicData::defaultSaveFileName()
{
    return QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/" + qApp->applicationName() + "/" + SAVE_FILE;
}
DynamicData* DynamicData::getInstance()
{
    if(s_shareDynamicData == nullptr){
        s_shareDynamicData = new DynamicData();
        s_shareDynamicData->loadAppConfig();// 读取应用配置
    }
    return s_shareDynamicData;
}

// @brief 获取按钮剪切缓存
AppButton* DynamicData::getBtnShearPlate(){    return _btnShearPlate;}
// @brief 设置按钮剪切缓存
void DynamicData::setBtnShearPlate(AppButton *btn)
{
    if(_btnShearPlate != nullptr){
        delete _btnShearPlate;
        _btnShearPlate = nullptr;
    }
    _btnShearPlate = new AppButton("");
    _btnShearPlate->copyFrom(*btn);
}
// @brief 保存设置
void DynamicData::saveAppConfig()
{
    QSettings *configIniWrite = new QSettings(CONFIG_FILE, QSettings::IniFormat);
    configIniWrite->setValue("theme", _theme);
    configIniWrite->setValue("filename/save", _userSettingsFileNames);
    configIniWrite->setValue("language", _language);
    TyLogInfo("success save ConfigFile: {\n\ttheme: %s\n\tfilename: %s\n\tlanguage: %s\n}", 
               _theme.toUtf8().data(), 
               _userSettingsFileNames.toUtf8().data(),
               _language.toUtf8().data());
    delete configIniWrite;// 使用完后销毁
}
// @brief 读取设置
void DynamicData::loadAppConfig()
{
    QSettings *configIniRead = new QSettings(CONFIG_FILE, QSettings::IniFormat);
    _theme = configIniRead->value("theme", ":/css/res/default.qss").toString();
    _userSettingsFileNames = configIniRead->value("filename/save", defaultSaveFileName()).toString();
    this->loadUserSaveFile(_userSettingsFileNames);
    _language = configIniRead->value("language", "").toString();
    if(_language.isEmpty())// 当取不到语言设置时,使用系统当前语言
        _language = QLocale::system().name();
    delete configIniRead;;// 使用完后销毁
    TyLogInfo("Load Settins:{Theme: %s\n\tSaveFileName: %s\n\tLanguage: %s\n}", 
               _theme.toUtf8().data(), 
               _userSettingsFileNames.toUtf8().data(), 
               _language.toUtf8().data());
}
// @brief 重置存档路径
void DynamicData::resetSaveFileName()
{
    _userSettingsFileNames = defaultSaveFileName();
}

bool DynamicData::BtnShearPlateIsEmpty(){    return _btnShearPlate == nullptr;}

// @brief 读取存档文件
void DynamicData::loadUserSaveFile(const QString fileName)
{
    QFile file(fileName);
    // 当存档文件不存在时,丢出异常,重新建立存档
    if(!file.exists()){
        TyLogWarning("UserSaveFile is not exists.fileName: %s", fileName.toUtf8().data());
        resetUserSaveFile();
        return;
    }
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text)){
        TyLogFatal("Open Save File Failure");
        resetUserSaveFile();
        return;
    }
    
    _userSaveData.clear();
    
    QJsonParseError parseErr;
    QJsonDocument doc = QJsonDocument::fromJson(file.readAll(),&parseErr);
    if(parseErr.error != QJsonParseError::NoError)
         throw QString("Save File failure!");
    if(!doc.isArray())
        throw QString("Save File Failure!");
    QJsonArray tabArr = doc.array();
    for(int i = 0; i < DEFAULT_TAB_COUNT; ++i){// 每一个Tab
        QVector<AppInfo> btnVector;
        QJsonValue val = tabArr.at(i);
        if(!val.isArray())
            throw QString("Save File Failure!");
        QJsonArray arr = val.toArray();
        for(int i = 0; i < arr.count(); ++i){
            QJsonValue valObj = arr.at(i);
            if(!valObj.isObject())
                throw QString("Save File Failure!");
            QJsonObject obj = valObj.toObject();
            AppInfo appInfo(obj[KEY_APP_NAME].toString(), obj[KEY_FILE_NAME].toString(), obj[KEY_HOT_KEY].toString());
            btnVector.append(appInfo);
        }
        _userSaveData.append(btnVector);
    }
}

void DynamicData::saveUserSaveFile(const QString &content)
{
    QFile file(_userSettingsFileNames);
    if (!QFile::exists(_userSettingsFileNames)){
        TyLogWarning("%s is not exists!", _userSettingsFileNames.toUtf8().data());
        QFileInfo fileInfo(file);
        QDir dir;
        if (!dir.exists(fileInfo.path())){
            dir.mkpath(fileInfo.path());
            TyLogWarning("make path: \"%s\".", fileInfo.path().toUtf8().data());
        }
    }
    if(!file.open(QFile::WriteOnly)){
        TyLogFatal("%s", QObject::tr("Can not save the file %1:\n %2.").arg(_userSettingsFileNames).arg(file.errorString()).toUtf8().data());
        return;
    }
    QTextStream txtOutput(&file);
    txtOutput.setCodec("UTF-8");
    txtOutput << content;
    file.close();
    TyLogInfo("success save UserSaveFile to %s.", _userSettingsFileNames.toUtf8().data());
}

void DynamicData::resetUserSaveFile()
{
    QString btnStr[3][10] = {{"Q", "W", "E", "R", "T", "Y", "U", "I", "O", "P"}
                             ,{"A", "S", "D", "F", "G", "H", "J", "K", "L", ";"}
                             ,{"Z", "X", "C", "V", "B", "N", "M", ",", ".", "/"}
                            };
    _userSaveData.clear();
    for(int i = 0; i < DEFAULT_TAB_COUNT; ++i){// 每一个Tab
        QVector<AppInfo> btnVector;
        // 每一列
        for(int i = 0; i < DEFAULT_TAB_COLUMN_COUNT * DEFAULT_TAB_ROW_COUNT; ++i){
            AppInfo appInfo;
            appInfo.setHotKey(btnStr[i / DEFAULT_TAB_COLUMN_COUNT][i % DEFAULT_TAB_COLUMN_COUNT]);
            btnVector.append(appInfo);
        }
        _userSaveData.append(btnVector);
    }
}

QString DynamicData::getTheme() const{return _theme;}
void DynamicData::setTheme(const QString &theme){_theme = theme;}

QString DynamicData::getUserSettingsFileNames() const{return _userSettingsFileNames;}
void DynamicData::setUserSettingsFileNames(const QString &userSettingsFileNames){_userSettingsFileNames = userSettingsFileNames;}

QString DynamicData::getLanguage(){    return _language;}
void DynamicData::setLanguage(const QString &language){ _language = language;}

QStringList DynamicData::getLanguageList()
{
    QStringList strList;
    strList.append(DEFAULT_LANGUAGE);
    QDir dir(FILE_NAME_LANGUAGE);
    QFileInfoList fileInfoList = dir.entryInfoList(QStringList("*.qm"));
    for (QFileInfo info : fileInfoList){
        strList.append(info.baseName());
    }
    return strList;
}

QVector<QVector<AppInfo> > DynamicData::getUserSaveData() const{return _userSaveData;}
