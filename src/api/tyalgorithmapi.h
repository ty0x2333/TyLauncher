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
#ifndef __TYALGORITHM_API_H__
#define __TYALGORITHM_API_H__
#include <QObject>
#include <QString>
#ifdef QT_DEBUG
static const QString APP_ID = "43d492365884cf7331130587eac9d305";
#else
static const QString APP_ID = "41f14ff474c07266a4124105a00da6b2";
#endif
static const QString HTTP = "http://";
static const QString HOST = "api.tylauncher.com/index.php/";
static const QString API = "api/";
static const QString BASE_URL = HTTP + HOST + API;
class TyAlgorithmAPI
{
public:
    TyAlgorithmAPI();
    /**
     * @brief check the application update
     * @param receiver
     * @param finishedMember
     *          receive QNetworkReply::finished().
     *          e.g. SLOT(function())
     * @param errorMember
     *          receive QNetworkReply::error(QNetworkReply::NetworkError).
     *          nullable
     *          default: nullptr
     *          e.g. SLOT(function(QNetworkReply::NetworkError))
     * @see   QMetaObject::Connection connect(const QObject *sender, const char *signal, const QObject *receiver, const char *member, Qt::ConnectionType = Qt::AutoConnection);
     * 
     */
    static void checkUpdate(const QObject *receiver, 
                         const char *finishedMember,
                         const char *errorMember = nullptr);
};

#endif // __TYALGORITHM_API_H__
