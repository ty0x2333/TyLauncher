/**
 * Copyright (c) 2016, luckytianyiyan <luckytianyiyan@gmail.com>
 * 
 * This file is part of TyLauncher.
 * 
 * TyLauncher is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * TyLauncher is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with TyLauncher.  If not, see <http://www.gnu.org/licenses/>.
 */
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
    
    static QString driveUniqueID();
    
    static QString currentSystem();
    
    static QString currentSystemVersion();
};

#endif // __APP_UTILS_H__
