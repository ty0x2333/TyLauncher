#include "apputils.h"
#ifdef Q_OS_WIN32
#include <windows.h>
#elif define(Q_OS_LINUX)
#include <sys/types.h>  
#include <sys/stat.h>  
#include <fcntl.h>  
#include <unistd.h>  
#endif
bool AppUtils::checkRunTimeOnly()
{
#ifdef Q_OS_WIN32   //for win  
    //  创建互斥量  
    HANDLE m_hMutex = CreateMutex(NULL, FALSE,  L"TyyAppManager" );  
    //  检查错误代码
    if(GetLastError() == ERROR_ALREADY_EXISTS)  {  
        // 如果已有互斥量存在则释放句柄并复位互斥量
        CloseHandle(m_hMutex);
        m_hMutex  =  NULL;
        return false;
    }
    else{
        return true;
    }
#elif define(Q_OS_LINUX)
    const char filename[]  = "/tmp/lockfile";  
    int fd = open (filename, O_WRONLY | O_CREAT , 0644);  
    int flock = lockf(fd, F_TLOCK, 0 );  
    if (fd == -1) {  
        perror("open lockfile/n");  
        return false;  
    }
    // 给文件加锁  
    if (flock == -1) {
        perror("lock file error/n");  
        return false;  
    }  
    // 程序退出后，文件自动解锁
    return true;
#else
    return true;
#endif  
}
