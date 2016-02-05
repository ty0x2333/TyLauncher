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


