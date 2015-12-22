#include "appinfo.h"
#include <QString>

AppInfo::AppInfo()
    : _name(QString())
    , _fileName(QString())
    , _hotKey(QString())
{
}

AppInfo::AppInfo(const QString &name, const QString &fileName, const QString &hotKey)
    : _name(name)
    , _fileName(fileName)
    , _hotKey(hotKey)
{
}
QString AppInfo::hotKey() const
{
    return _hotKey;
}

void AppInfo::setHotKey(const QString &hotKey)
{
    _hotKey = hotKey;
}
QString AppInfo::name() const
{
    return _name;
}

void AppInfo::setName(const QString &name)
{
    _name = name;
}
QString AppInfo::fileName() const
{
    return _fileName;
}

void AppInfo::setFileName(const QString &fileName)
{
    _fileName = fileName;
}


