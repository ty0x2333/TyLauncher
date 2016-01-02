#include "appbtninfo.h"
#include <QString>

AppBtnInfo::AppBtnInfo()
    : _appInfo(QString(), QString())
    , _hotKey(QString())
{
}

AppBtnInfo::AppBtnInfo(const QString &name, const QString &fileName, const QString &hotKey)
    : _appInfo(AppInfo(name, fileName))
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
QString AppBtnInfo::name() const
{
    return _appInfo.name();
}

void AppBtnInfo::setName(const QString &name)
{
    _appInfo.setName(name);
}
QString AppBtnInfo::fileName() const
{
    return _appInfo.fileName();
}

void AppBtnInfo::setFileName(const QString &fileName)
{
    _appInfo.setFileName(fileName);
}
AppInfo AppBtnInfo::appInfo() const
{
    return _appInfo;
}

void AppBtnInfo::setAppInfo(const AppInfo &appInfo)
{
    _appInfo = appInfo;
}



