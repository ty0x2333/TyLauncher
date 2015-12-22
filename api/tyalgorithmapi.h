#ifndef __TYALGORITHM_API_H__
#define __TYALGORITHM_API_H__
#include <QObject>
#include <QString>
static const QString APP_ID = "9a3ccf3ff5160a6b4074737f674129ce";
static const QString HTTP = "http://";
static const QString HOST = "localhost/tyyapps/index.php/";
static const QString API = "api/";
static const QString BASE_URL = HTTP + HOST + API;
class TyAlgorithmAPI
{
public:
    TyAlgorithmAPI();
    /**
     * @brief 检查更新
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
     */
    static void checkUpdate(const QObject *receiver, 
                         const char *finishedMember,
                         const char *errorMember = nullptr);
};

#endif // __TYALGORITHM_API_H__
