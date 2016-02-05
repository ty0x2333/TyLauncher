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
    
    bool isEmpty() const;
    
private:
    QString _name;
    QString _fileName;
};

#endif // APPINFO_H
