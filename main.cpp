#include "mainwindow.h"
#include <QApplication>
#include "StaticSetting.h"
#include <QTranslator>
#include <QFile>
#include "dynamicdata.h"
#ifdef Q_OS_WIN32   //for win  
#include <windows.h>

bool checkOnly()  
{  
    //  创建互斥量  
    HANDLE m_hMutex = CreateMutex(NULL, FALSE,  L"TyyAppManager" );  
    //  检查错误代码  
    if(GetLastError() == ERROR_ALREADY_EXISTS)  {  
        // 如果已有互斥量存在则释放句柄并复位互斥量
        CloseHandle(m_hMutex);  
        m_hMutex  =  NULL;
        return false;
    }  
    else  
        return true;  
}  
#endif  
#ifdef  Q_OS_LINUX   //for linux  
#include <sys/types.h>  
#include <sys/stat.h>  
#include <fcntl.h>  
#include <unistd.h>  
bool checkOnly()  
{  
    const char filename[]  = "/tmp/lockfile";  
    int fd = open (filename, O_WRONLY | O_CREAT , 0644);  
    int flock = lockf(fd, F_TLOCK, 0 );  
    if (fd == -1) {  
        perror("open lockfile/n");  
        return false;  
    }  
    //给文件加锁  
    if (flock == -1) {  
        perror("lock file error/n");  
        return false;  
    }  
    //程序退出后，文件自动解锁  
    return true;  
}  
#endif  

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //检查程序是否 已经启动过  
//    if(checkOnly() == false)
//        return 0;
    
    a.setApplicationName(VER_PRODUCTNAME_STR);
    a.setApplicationVersion(VER_FILEVERSION_DISPLAY_STR);
    
    // 设置样式
    QString qss;
    QFile qssFile(DynamicData::getInstance()->getTheme());
    qssFile.open(QFile::ReadOnly);
    if(qssFile.isOpen())
    {
        qss = QLatin1String(qssFile.readAll());
        qApp->setStyleSheet(qss);
        qssFile.close();
    }
    
    MainWindow w;
    w.show();
    return a.exec();
}
