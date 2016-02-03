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
     * @param receiver
     * @param finishedMember
     *          receive QNetworkReply::finished().
     *          e.g. SLOT(function())
     * @param errorMember
     *          receive QNetworkReply::error(QNetworkReply::NetworkError).
     *          nullable
     *          default: nullptr
     *          e.g. SLOT(function(QNetworkReply::NetworkError))
     * @param sslErrorsReadMember
     *          receive QNetworkReply::sslErrors(QList<QSslError>).
     *          nullable
     *          default: nullptr
     *          e.g. SLOT(function(QList<QSslError>))
     * 
     * @see     QMetaObject::Connection connect(const QObject *sender, const char *signal, const QObject *receiver, const char *member, Qt::ConnectionType = Qt::AutoConnection);
     */
    void get(const QNetworkRequest& request, const QObject *receiver,
             const char *finishedMember,
             const char *errorMember = nullptr,
             const char *sslErrorsReadMember = nullptr);
    /**
     * @brief post
     * @param request
     * @param data
     * @param receiver
     * @param finishedMember
     *          receive QNetworkReply::finished().
     *          e.g. SLOT(function())
     *         
     * @param errorMember
     *          receive QNetworkReply::error(QNetworkReply::NetworkError).
     *          nullable
     *          default: nullptr
     *          e.g. SLOT(function(QNetworkReply::NetworkError))
     * @param sslErrorsReadMember
     *          receive QNetworkReply::sslErrors(QList<QSslError>).
     *          nullable
     *          default: nullptr
     *          e.g. SLOT(function(QList<QSslError>))
     * 
     * @see     QMetaObject::Connection connect(const QObject *sender, const char *signal,
     *                  const QObject *receiver, const char *member, Qt::ConnectionType = Qt::AutoConnection);
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
     * @pre   must be use before the application destroy
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
