#ifndef APP_BTN_INFO_H
#define APP_BTN_INFO_H
#include <QString>
#include "model/appinfo.h"
/**
 * @brief Application Button Information Model
 */
class AppBtnInfo : public AppInfo
{
public:
    AppBtnInfo();
    
    AppBtnInfo(const QString &name, const QString &fileName = QString(), const QString &hotKey = QString());
    
    QString hotKey() const;
    void setHotKey(const QString &hotKey);
    
private:
    QString _hotKey;
};

#endif // APPINFO_H
