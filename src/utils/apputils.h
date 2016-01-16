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
    static QString macAddress();
    /**
     * @brief diskdriveSerialNumber
     * @return 硬盘物理ID
     */
    static QString diskdriveSerialNumber();
};

#endif // __APP_UTILS_H__
