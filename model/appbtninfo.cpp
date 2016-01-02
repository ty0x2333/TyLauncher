#include "appbtninfo.h"
#include <QString>

AppBtnInfo::AppBtnInfo()
    : _name(QString())
    , _fileName(QString())
    , _hotKey(QString())
{
}

AppBtnInfo::AppBtnInfo(const QString &name, const QString &fileName, const QString &hotKey)
    : _name(name)
    , _fileName(fileName)
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
    return _name;
}

void AppBtnInfo::setName(const QString &name)
{
    _name = name;
}
QString AppBtnInfo::fileName() const
{
    return _fileName;
}

void AppBtnInfo::setFileName(const QString &fileName)
{
    _fileName = fileName;
}


