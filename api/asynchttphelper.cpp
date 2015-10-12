#include "asynchttphelper.h"
#include <QNetworkReply>
#include <QApplication>
AsyncHttpHelper* AsyncHttpHelper::_sharedAsyncHttpHelper = nullptr;

void AsyncHttpHelper::get(const QNetworkRequest& request, const QObject *receiver, 
                          const char *finishedMember,
                          const char *errorMember,
                          const char *sslErrorsReadMember)
{
    if (_netManager == nullptr)
        _netManager = new QNetworkAccessManager(this);
    QNetworkReply *reply = _netManager->get(request);
    connect(reply, SIGNAL(finished()), receiver, finishedMember);
    if (errorMember != nullptr)
        connect(reply, SIGNAL(error(QNetworkReply::NetworkError)), receiver, errorMember);
    if (sslErrorsReadMember != nullptr)
        connect(reply, SIGNAL(sslErrors(QList<QSslError>)), receiver, sslErrorsReadMember);
}

void AsyncHttpHelper::post(const QNetworkRequest &request, const QByteArray &data,
                           const QObject *receiver,
                           const char *finishedMember,
                           const char *errorMember,
                           const char *sslErrorsReadMember)
{
    if (_netManager == nullptr)
        _netManager = new QNetworkAccessManager(this);
    QNetworkReply *reply = _netManager->post(request, data);
    connect(reply, SIGNAL(finished()), receiver, finishedMember);
    if (errorMember != nullptr)
        connect(reply, SIGNAL(error(QNetworkReply::NetworkError)), receiver, errorMember);
    if (sslErrorsReadMember != nullptr)
        connect(reply, SIGNAL(sslErrors(QList<QSslError>)), receiver, sslErrorsReadMember);
}

AsyncHttpHelper* AsyncHttpHelper::getInstance()
{
    if (_sharedAsyncHttpHelper == nullptr)
        _sharedAsyncHttpHelper = new AsyncHttpHelper();
    return _sharedAsyncHttpHelper;
}

void AsyncHttpHelper::destroy()
{
    delete _netManager;
    _netManager = nullptr;
}

void AsyncHttpHelper::onApplicationQuit()
{
    destroy();
}

AsyncHttpHelper::AsyncHttpHelper()
    : _netManager(nullptr)
{
    _netManager = new QNetworkAccessManager(this);
    connect(qApp, SIGNAL(aboutToQuit()), this, SLOT(onApplicationQuit()));
}

AsyncHttpHelper::~AsyncHttpHelper()
{
    if (_netManager != nullptr)
        delete _netManager;
    _sharedAsyncHttpHelper = nullptr;
}

