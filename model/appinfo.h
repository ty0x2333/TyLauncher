#ifndef APPINFO_H
#define APPINFO_H
#include <QString>

class AppInfo
{
public:
    AppInfo();
    AppInfo(const QString &name, const QString &fileName = QString());
    QString name() const;
    void setName(const QString &name);
    
    QString fileName() const;
    void setFileName(const QString &fileName);
    
private:
    QString _name;
    QString _fileName;
};

#endif // APPINFO_H
