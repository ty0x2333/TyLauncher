#include "apputils.h"
#include "TyLog_Qt.h"

#define MAC_ADDRESS_NULL "00:00:00:00:00:00:00:E0"

#ifdef Q_OS_WIN32
#include <QDir>
#include <QFileInfoList>
#include <QNetworkInterface>
#include <QProcess>
#include <windows.h>
#elif (defined(Q_OS_LINUX) || defined(Q_OS_MAC))
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#endif

bool AppUtils::isRunTimeOnly()
{
#ifdef Q_OS_WIN32
    // 创建互斥量
    HANDLE m_hMutex = CreateMutex(NULL, FALSE,  L"TyLauncher" );
    // 检查错误代码
    if(GetLastError() == ERROR_ALREADY_EXISTS){
        // 如果已有互斥量存在则释放句柄并复位互斥量
        CloseHandle(m_hMutex);
        m_hMutex  =  NULL;
        return false;
    }
#elif (defined(Q_OS_LINUX) || defined(Q_OS_MAC))
    const char filename[]  = "/tmp/tylauncher_lockfile";
    int fd = open(filename, O_WRONLY | O_CREAT , 0644);
    // 使用文件区域做进程锁
    int flock = lockf(fd, F_TLOCK, 0 );
    if (fd == -1) {
        TyLogCritical("open lockfile error/n");
        return false;
    }
    // 给文件加锁
    if (flock == -1) {
        TyLogCritical("lock file error/n");
        return false;
    }
#endif
    return true;
}

QStringList AppUtils::fileNameList(const QString &dirPath, const QStringList &filter)
{
    QStringList strList;
    QDir dir(dirPath);
    QFileInfoList fileInfoList = dir.entryInfoList(filter);
    for (QFileInfo info : fileInfoList){
        strList.append(info.baseName());
    }
    return strList;
}

QString AppUtils::macAddress()
{
    QList<QNetworkInterface> list = QNetworkInterface::allInterfaces();
    foreach (QNetworkInterface netInterface, list) {
        QString hardwareAddress = netInterface.hardwareAddress();
        if (!hardwareAddress.isEmpty() && hardwareAddress != MAC_ADDRESS_NULL){
            return hardwareAddress;
        }
    }
    return MAC_ADDRESS_NULL;
}

QString AppUtils::diskdriveSerialNumber()
{
    QProcess proc;
//  QStringList args;
//  args << "-c" << "ioreg -rd1 -c IOPlatformExpertDevice |  awk '/IOPlatformSerialNumber/ { print $3; }'";
//  proc.start( "/bin/bash", args );
//  若是想获取硬件ID可把上面的 IOPlatformSerialNumber 改为 IOPlatformUUID 即可
#if defined(Q_OS_WIN32)
    proc.start("wmic diskdrive get SerialNumber");
    proc.waitForFinished();
    QString info = proc.readAll().simplified();
    QStringList list = info.simplified().split(" ");
    return list[1];
#endif
}
