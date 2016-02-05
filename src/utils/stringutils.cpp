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
#include "stringutils.h"
#include <QString>
#include "model/option.h"
#include "datasettings.h"

QString StringUtils::toString(QHash<QString, Option> options)
{
    QString str = "{";
    foreach ( const QString &key, options.keys() ) {
        str += QString("\n\t%1: %2,").arg(key).arg(options[key].value().toString());
    }
    str += "\n}";
    return str;
}

QString StringUtils::themeFileName(const QString &theme)
{
    return QString("%1%2%3%4").arg(FILE_NAME_THEME).arg("/").arg(theme).arg(".qss");
}

QString StringUtils::networkErrorString(QNetworkReply::NetworkError networkError)
{
    QString result;
    switch (networkError) {
    case QNetworkReply::NoError:
        result = QString();
        break;
    case QNetworkReply::ConnectionRefusedError:
        result = QObject::tr("Connection refused\nPlease check your network connection.");
        break;
    default:
        result = QObject::tr("Unknown network error");
        break;
    }
    return result;
}
