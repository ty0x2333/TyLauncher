#ifndef DYNAMICDATA_H
#define DYNAMICDATA_H
#include <QObject>
#include <QtGlobal>
#include <QString>
#include <QVector>
#include <QHash>
#include <QVariant>

QT_BEGIN_NAMESPACE
class QStringList;
class QKeySequence;
QT_END_NAMESPACE
class AppButton;
class AppInfo;
class Option;

#define DYNAMIC_DATA DynamicData::getInstance()

class DynamicData : public QObject
{
    Q_OBJECT
    
public:
    static DynamicData* getInstance();

    /// @brief 获取按钮剪切缓存是否为空
    bool BtnShearPlateIsEmpty();

    /// @brief 保存设置
    void saveAppConfig();
    void loadAppConfig();

    /// @brief 读取存档文件
    void loadUserSaveFile(const QString fileName);
    
    /// @brief 保存存档文件
    void saveUserSaveFile(const QString& content);
    
    void resetUserSaveFile();
    
    QStringList getLanguageList() const;
    
    QKeySequence getGlobalShortcut() const;
    void setGlobalShortcut(QKeySequence keySequence);
    
    AppButton* getBtnShearPlate();
    void setBtnShearPlate(AppButton *btn);
    
    QString getLanguage() const;
    void setLanguage(const QString &language);
    
    QString userSettingsFileName() const;
    void setUserSettingsFileName(const QString &userSettingsFileNames);
    
    QString getTheme() const;
    void setTheme(const QString &theme);
    
    QVector<QVector<AppInfo> > getUserSaveData() const;
    
    QVariant value(const QString &name) const;
    void setValue(const QString &name, const QVariant &value);
    
signals:
    void appConfigChanged(const QString &key);
    
private:
    DynamicData();
    
    void initOptions();
    
    QVector<QVector<AppInfo>> _userSaveData;
    /**
     * @brief 按钮剪切缓存
     * 用来保存复制的按钮地址
     */
    AppButton *_btnShearPlate;
    
    QHash<QString, Option> _options;
};

#endif // DYNAMICDATA_H
