/**
 * Copyright (c) 2016, luckytianyiyan <luckytianyiyan@gmail.com>
 * 
 * This file is part of TyLauncher.
 * 
 * TyLauncher is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * TyLauncher is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with TyLauncher.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "dynamicdata.h"
#include "model/appbtninfo.h"
#include "widget/appbutton.h"
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
#include <QKeySequence>
#include "model/option.h"
#include "utils/stringutils.h"
#include "utils/apputils.h"
namespace {
QString userDataFileName()
{
    return QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/" + qApp->applicationName() + "/" + SAVE_FILE;
}
}// namespace

static DynamicData *s_shareDynamicData = nullptr;
DynamicData::DynamicData()
    : _options()
{
    initOptions();
}

void DynamicData::initOptions()
{
    _options[KEY_LANGUAGE] = Option(DEFAULT_LANGUAGE);
    _options[KEY_THEME] = Option(DEFAULT_THEME);
    _options[KEY_HOT_KEY] = Option(DEFAULT_HOT_KEY);
}

DynamicData* DynamicData::instance()
{
    if(s_shareDynamicData == nullptr){
        s_shareDynamicData = new DynamicData();
        s_shareDynamicData->loadAppConfig();// 读取应用配置
    }
    return s_shareDynamicData;
}
// @brief 保存设置
void DynamicData::saveAppConfig()
{
    QSettings configIniWrite(CONFIG_FILE, QSettings::IniFormat);
    foreach ( const QString &key, _options.keys() ) {
        configIniWrite.setValue( key, _options[key].value() );
    }
    TyLogInfo("Success Save AppConfig: %s", StringUtils::toString(_options).toUtf8().data());
}
// @brief 读取设置
void DynamicData::loadAppConfig()
{
    QSettings configIniRead(CONFIG_FILE, QSettings::IniFormat);
    foreach ( const QString &key, _options.keys() ) {
        if ( configIniRead.contains(key) ) {
            QVariant value = configIniRead.value(key);
            if ( !value.isValid() || !_options[key].setValue(value) ){
                TyLogWarning("Invalid value for option \"%s\"", key.toUtf8().data());
            }
        }else{
            _options[key].reset();
        }
    }
    loadUserDataFile();
    if (!themeList().contains(theme())){
        TyLogFatal("not exists theme file, reset theme to default \"%s\"", DEFAULT_THEME);
        _options[KEY_THEME].reset();
    }
//    _language = configIniRead->value(KEY_LANGUAGE, "").toString();
//    if(_language.isEmpty())// 当取不到语言设置时,使用系统当前语言
//        _language = QLocale::system().name();
    TyLogInfo("Load AppConfig: %s", StringUtils::toString(_options).toUtf8().data());
}

void DynamicData::loadUserDataFile()
{
    QFile file(userDataFileName());
    // 当存档文件不存在时,丢出异常,重新建立存档
    if(!file.exists()){
        TyLogWarning("UserDataFile is not exists.fileName: %s", userDataFileName().toUtf8().data());
        resetUserDataFile();
        return;
    }
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text)){
        TyLogFatal("Open Save File Failure");
        resetUserDataFile();
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
        QVector<AppBtnInfo> btnVector;
        QJsonValue val = tabArr.at(i);
        if(!val.isArray())
            throw QString("Save File Failure!");
        QJsonArray arr = val.toArray();
        for(int i = 0; i < arr.count(); ++i){
            QJsonValue valObj = arr.at(i);
            if(!valObj.isObject())
                throw QString("Save File Failure!");
            QJsonObject obj = valObj.toObject();
            AppBtnInfo appBtnInfo(obj[KEY_APP_NAME].toString(), obj[KEY_FILE_NAME].toString(), obj[KEY_HOT_KEY].toString());
            btnVector.append(appBtnInfo);
        }
        _userSaveData.append(btnVector);
    }
}

void DynamicData::saveUserDataFile(const QString &content)
{
    saveUserDataFile(content, userDataFileName());
}

void DynamicData::saveUserDataFile(const QString& content, const QString& fileName)
{
    QFile file(fileName);
    if (!QFile::exists(fileName)){
        TyLogWarning("%s is not exists!", fileName.toUtf8().data());
        QFileInfo fileInfo(file);
        QDir dir;
        if (!dir.exists(fileInfo.path())){
            dir.mkpath(fileInfo.path());
            TyLogWarning("make path: \"%s\".", fileInfo.path().toUtf8().data());
        }
    }
    if(!file.open(QFile::WriteOnly)){
        TyLogFatal("%s", QObject::tr("Can not save the file %1:\n %2.").arg(fileName).arg(file.errorString()).toUtf8().data());
        return;
    }
    QTextStream txtOutput(&file);
    txtOutput.setCodec("UTF-8");
    txtOutput << content;
    file.close();
    TyLogInfo("Success Save UserDataFile to %s.", fileName.toUtf8().data());
}

void DynamicData::resetUserDataFile()
{
    QString btnStr[3][10] = {{"Q", "W", "E", "R", "T", "Y", "U", "I", "O", "P"}
                             ,{"A", "S", "D", "F", "G", "H", "J", "K", "L", ";"}
                             ,{"Z", "X", "C", "V", "B", "N", "M", ",", ".", "/"}
                            };
    _userSaveData.clear();
    for(int i = 0; i < DEFAULT_TAB_COUNT; ++i){// 每一个Tab
        QVector<AppBtnInfo> btnVector;
        for(int i = 0; i < DEFAULT_TAB_COLUMN_COUNT * DEFAULT_TAB_ROW_COUNT; ++i){
            AppBtnInfo appInfo;
            appInfo.setHotKey(btnStr[i / DEFAULT_TAB_COLUMN_COUNT][i % DEFAULT_TAB_COLUMN_COUNT]);
            btnVector.append(appInfo);
        }
        _userSaveData.append(btnVector);
    }
}

QStringList DynamicData::languageList() const
{
    QStringList strList = AppUtils::fileNameList(FILE_NAME_LANGUAGE, QStringList("*.qm"));
    strList.insert(0, DEFAULT_LANGUAGE);
    return strList;
}

QStringList DynamicData::themeList() const
{
    QStringList strList = AppUtils::fileNameList(FILE_NAME_THEME, QStringList("*.qss"));
    strList.insert(0, SYSTEM_THEME);
    return strList;
}

QString DynamicData::theme() const{return value(KEY_THEME).toString();}
void DynamicData::setTheme(const QString &theme){setValue(KEY_THEME, theme);}

QString DynamicData::language() const{return value(KEY_LANGUAGE).toString();}
void DynamicData::setLanguage(const QString &language){setValue(KEY_LANGUAGE, language);}

QKeySequence DynamicData::globalShortcut() const{return QKeySequence(value(KEY_HOT_KEY).toString());}
void DynamicData::setGlobalShortcut(QKeySequence keySequence){setValue(KEY_HOT_KEY, keySequence.toString());}

QVector<QVector<AppBtnInfo> > DynamicData::userSaveData() const{return _userSaveData;}

QVariant DynamicData::value(const QString &name) const
{
    Q_ASSERT(_options.contains(name));
    return _options[name].value();
}

void DynamicData::setValue(const QString &name, const QVariant &value)
{
    if (!_options.contains(name)){
        TyLogWarning("Key \"%s\" is not find.", name.toUtf8().data());
        return;
    }
    if ( _options[name].value() == value )
        return;
    if ( !value.isValid() || !_options[name].setValue(value) ){
        TyLogWarning("Invalid value for option \"%s\"", name.toUtf8().data());
        return;
    }
    emit appConfigChanged(name);
    if (name == KEY_THEME){
        emit themeConfigChanged();
    }
}
