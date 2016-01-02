#include "appinfo.h"

AppInfo::AppInfo()
    : _name(QString())
    , _fileName(QString())
{}

AppInfo::AppInfo(const QString &name, const QString &fileName) 
    : _name(name)
    , _fileName(fileName)
{}

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



