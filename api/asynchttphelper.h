/**
 * @file asynchttphelper.h
 * @brief Async Http Helper
 *     You can get more help through the following way:
 *     1. My WebSite: http://tianyiyan.com
 *     2. GitHub: https://github.com/luckytianyiyan/TyClassLibrary
 *
 * @author luckytianyiyan@gmail.com
 * @version 1.2
 * @date 2015-7-14
 */
#ifndef ASYNCHTTPHELPER_H
#define ASYNCHTTPHELPER_H
#include <QtNetwork/QNetworkAccessManager>
#include <QObject>
class AsyncHttpHelper : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief get
     * @param request
     *          发送的请求
     * @param receiver
     *          槽拥有者
     * @param finishedMember
     *          槽, 它将接收 QNetworkReply::finished() 信号.
     *          传入参数应形如 SLOT(function())
     *          详情查看
     *              QMetaObject::Connection connect(const QObject *sender, const char *signal,
     *                  const QObject *receiver, const char *member, Qt::ConnectionType = Qt::AutoConnection);
     * @param errorMember
     *          槽, 它将接收 QNetworkReply::error(QNetworkReply::NetworkError) 信号.
     *          默认为nullptr
     *          传入参数应形如 SLOT(function(QNetworkReply::NetworkError))
     *          详情查看
     *              QMetaObject::Connection connect(const QObject *sender, const char *signal,
     *                  const QObject *receiver, const char *member, Qt::ConnectionType = Qt::AutoConnection);
     *          Note : 当值为nullptr时, 将忽略 QNetworkReply::error 信号
     * @param sslErrorsReadMember
     *          槽, 它将接收 QNetworkReply::sslErrors(QList<QSslError>) 信号.
     *          默认为nullptr
     *          传入参数应形如 SLOT(function(QList<QSslError>))
     *          详情查看
     *              QMetaObject::Connection connect(const QObject *sender, const char *signal,
     *                  const QObject *receiver, const char *member, Qt::ConnectionType = Qt::AutoConnection);
     *          Note : 当值为nullptr时, 将忽略 QNetworkReply::sslErrors 信号
     */
    void get(const QNetworkRequest& request, const QObject *receiver,
             const char *finishedMember,
             const char *errorMember = nullptr,
             const char *sslErrorsReadMember = nullptr);
    /**
     * @brief post
     * @param request
     *          发送的请求
     * @param data
     *          发送的数据
     * @param receiver
     *          槽拥有者
     * @param finishedMember
     *          槽, 它将接收 QNetworkReply::finished() 信号.
     *          传入参数应形如 SLOT(function())
     *          详情查看
     *              QMetaObject::Connection connect(const QObject *sender, const char *signal,
     *                  const QObject *receiver, const char *member, Qt::ConnectionType = Qt::AutoConnection);
     * @param errorMember
     *          槽, 它将接收 QNetworkReply::error(QNetworkReply::NetworkError) 信号.
     *          默认为nullptr
     *          传入参数应形如 SLOT(function(QNetworkReply::NetworkError))
     *          详情查看
     *              QMetaObject::Connection connect(const QObject *sender, const char *signal,
     *                  const QObject *receiver, const char *member, Qt::ConnectionType = Qt::AutoConnection);
     *          Note : 当值为nullptr时, 将忽略 QNetworkReply::error 信号
     * @param sslErrorsReadMember
     *          槽, 它将接收 QNetworkReply::sslErrors(QList<QSslError>) 信号.
     *          默认为nullptr
     *          传入参数应形如 SLOT(function(QList<QSslError>))
     *          详情查看
     *              QMetaObject::Connection connect(const QObject *sender, const char *signal,
     *                  const QObject *receiver, const char *member, Qt::ConnectionType = Qt::AutoConnection);
     *          Note : 当值为nullptr时, 将忽略 QNetworkReply::sslErrors 信号
     */
    void post(const QNetworkRequest& request,
              const QByteArray &data,
              const QObject *receiver,
              const char *finishedMember,
              const char *errorMember = nullptr,
              const char *sslErrorsReadMember = nullptr);

    static AsyncHttpHelper* getInstance();

    /**
     * @brief destroy
     *          destroy QNetworkAccessManager
     *          Note: must be use before the application destroy
     */
    void destroy();

private slots:

    void onApplicationQuit();

private:
    QNetworkAccessManager* _netManager;

    static AsyncHttpHelper* _sharedAsyncHttpHelper;
    AsyncHttpHelper();
    ~AsyncHttpHelper();
    AsyncHttpHelper(const AsyncHttpHelper&);
    AsyncHttpHelper& operator=(const AsyncHttpHelper&);
};

#endif // ASYNCHTTPHELPER_H
