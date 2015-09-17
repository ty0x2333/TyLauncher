#include "apputils.h"
#include "TyLog_Qt.h"

#ifdef Q_OS_WIN32
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
    HANDLE m_hMutex = CreateMutex(NULL, FALSE,  L"TyyAppManager" );
    // 检查错误代码
    if(GetLastError() == ERROR_ALREADY_EXISTS){
        // 如果已有互斥量存在则释放句柄并复位互斥量
        CloseHandle(m_hMutex);
        m_hMutex  =  NULL;
        return false;
    }
#elif (defined(Q_OS_LINUX) || defined(Q_OS_MAC))
    const char filename[]  = "/tmp/tyyappmanager_lockfile";
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
