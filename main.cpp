#include "mainwindow.h"
#include <QApplication>
#include "StaticSetting.h"
#include <QTranslator>
#include <QFile>
#include "dynamicdata.h"
#include "utils/apputils.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // 检查程序是否 已经启动 
    if(AppUtils::isRunTimeOnly() == false)
        return 0;
    
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
