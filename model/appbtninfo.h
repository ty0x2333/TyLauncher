#ifndef APP_BTN_INFO_H
#define APP_BTN_INFO_H
#include <QString>
#include "model/appinfo.h"
/**
 * @brief Application Button Information Model
 */
class AppBtnInfo
{
public:
    AppBtnInfo();
    
    AppBtnInfo(const QString &name, const QString &fileName = QString(), const QString &hotKey = QString());
    
    QString hotKey() const;
    void setHotKey(const QString &hotKey);
    
    QString name() const;
    void setName(const QString &name);
    
    QString fileName() const;
    void setFileName(const QString &fileName);
    
    AppInfo appInfo() const;
    void setAppInfo(const AppInfo &appInfo);
    
private:
    QString _hotKey;
    AppInfo _appInfo;
};

#endif // APPINFO_H
