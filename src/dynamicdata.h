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
#ifndef DYNAMICDATA_H
#define DYNAMICDATA_H
#include <QObject>
#include <QtGlobal>
#include <QString>
#include <QVector>
#include <QHash>
#include <QVariant>

QT_FORWARD_DECLARE_CLASS(QStringList)
QT_FORWARD_DECLARE_CLASS(QKeySequence)
QT_FORWARD_DECLARE_CLASS(AppButton)
QT_FORWARD_DECLARE_CLASS(AppBtnInfo)
QT_FORWARD_DECLARE_CLASS(Option)

#define DYNAMIC_DATA DynamicData::getInstance()

class DynamicData : public QObject
{
    Q_OBJECT
    
public:
    static DynamicData* getInstance();

    /// @brief 保存设置
    void saveAppConfig();
    void loadAppConfig();

    /// @brief 读取存档文件
    void loadUserSaveFile(const QString fileName);
    
    /// @brief 保存存档文件
    void saveUserSaveFile(const QString& content);
    
    void resetUserSaveFile();
    
    QStringList getLanguageList() const;
    QStringList getThemeList() const;
    
    QKeySequence getGlobalShortcut() const;
    void setGlobalShortcut(QKeySequence keySequence);
    
    QString getLanguage() const;
    void setLanguage(const QString &language);
    
    QString userSettingsFileName() const;
    void setUserSettingsFileName(const QString &userSettingsFileNames);
    
    QString getTheme() const;
    void setTheme(const QString &theme);
    
    QVector<QVector<AppBtnInfo> > getUserSaveData() const;
    
    QVariant value(const QString &name) const;
    void setValue(const QString &name, const QVariant &value);
    
signals:
    void appConfigChanged(const QString &key);
    void themeConfigChanged();
private:
    DynamicData();
    
    void initOptions();
    
    QVector<QVector<AppBtnInfo>> _userSaveData;
    
    QHash<QString, Option> _options;
};

#endif // DYNAMICDATA_H
