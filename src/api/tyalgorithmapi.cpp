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
#include "tyalgorithmapi.h"
#include "asynchttphelper.h"
#include <QNetworkRequest>
#include <QUrl>
#include <QCoreApplication>
#include "utils/apputils.h"

TyAlgorithmAPI::TyAlgorithmAPI()
{
    
}

void TyAlgorithmAPI::checkUpdate(const QObject *receiver, const char *finishedMember, const char *errorMember)
{
    QUrl url(BASE_URL + "check_update");
    QByteArray param;
    param.append("appId=");
    param.append(APP_ID);
    param.append("&version=");
    param.append(qApp->applicationVersion());
    param.append("&UUID=");
    param.append(AppUtils::driveUniqueID());
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    AsyncHttpHelper::getInstance()->post(request, param, receiver, finishedMember, errorMember);
}

