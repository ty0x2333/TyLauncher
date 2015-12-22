#include "tyalgorithmapi.h"
#include "asynchttphelper.h"
#include <QNetworkRequest>
#include <QUrl>
#include <QCoreApplication>

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
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    AsyncHttpHelper::getInstance()->post(request, param, receiver, finishedMember, errorMember);
}

