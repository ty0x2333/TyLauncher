#ifndef __APP_UTILS_H__
#define __APP_UTILS_H__
#include <QString>
#include <QStringList>
class AppUtils
{
public:
    /**
     * @brief Check whether the application is running
     * @return Whether already exists
     */
    static bool isRunTimeOnly();
    static QStringList fileNameList(const QString& dirPath, const QStringList &filter);
};

#endif // __APP_UTILS_H__
