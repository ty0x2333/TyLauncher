#ifndef DYNAMICDATA_H
#define DYNAMICDATA_H
#include <QtGlobal>
#include <QString>
#include <QVector>
#include <QHash>
#include <QVariant>

class AppButton;
class AppInfo;
class QStringList;
class Option;

#define DYNAMIC_DATA DynamicData::getInstance()

class DynamicData
{
public:
    static DynamicData* getInstance();

    /// @brief 获取按钮剪切缓存是否为空
    bool BtnShearPlateIsEmpty();

    /// @brief 保存设置
    void saveAppConfig();
    void loadAppConfig();

    /// @brief 重置存档路径
    void resetSaveFileName();

    /// @brief 读取存档文件
    void loadUserSaveFile(const QString fileName);
    
    /// @brief 保存存档文件
    void saveUserSaveFile(const QString& content);
    
    void resetUserSaveFile();
    
    AppButton* getBtnShearPlate();
    void setBtnShearPlate(AppButton *btn);
    
    QString getLanguage() const;
    void setLanguage(const QString &language);
    
    QStringList getLanguageList();
    
    QString getUserSettingsFileNames() const;
    void setUserSettingsFileNames(const QString &userSettingsFileNames);
    
    QString getTheme() const;
    void setTheme(const QString &theme);
    
    QVector<QVector<AppInfo> > getUserSaveData() const;
    
    QVariant value(const QString &name) const;
    void setValue(const QString &name, const QVariant &value);
    
    bool getAlwaysOnTop() const;
    void setAlwaysOnTop(bool alwaysOnTop);
    
private:
    DynamicData();
    
    void initOptions();
    
    QVector<QVector<AppInfo>> _userSaveData;
    /// @brief 存档路径
    QString _userSettingsFileNames;
    /**
     * @brief 按钮剪切缓存
     * 用来保存复制的按钮地址
     */
    AppButton *_btnShearPlate;
    
    QHash<QString, Option> _options;
    
    QString defaultSaveFileName();
};

#endif // DYNAMICDATA_H
