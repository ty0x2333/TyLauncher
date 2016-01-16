#include "appbtninfo.h"
#include <QString>

AppBtnInfo::AppBtnInfo()
    : AppInfo()
    , _hotKey(QString())
{
}

AppBtnInfo::AppBtnInfo(const QString &name, const QString &fileName, const QString &hotKey)
    : AppInfo(name, fileName)
    , _hotKey(hotKey)
{
}
QString AppBtnInfo::hotKey() const
{
    return _hotKey;
}

void AppBtnInfo::setHotKey(const QString &hotKey)
{
    _hotKey = hotKey;
}


