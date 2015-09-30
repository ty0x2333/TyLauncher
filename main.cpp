#include "widget/mainwindow.h"
#include <QApplication>
#include "StaticSetting.h"
#include <QTranslator>
#include <QFile>
#include "dynamicdata.h"
#include "utils/apputils.h"
#include "utils/uiutils.h"
#include <QObject>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName(VER_PRODUCTNAME_STR);
    a.setApplicationVersion(VER_FILEVERSION_DISPLAY_STR);
#ifndef QT_DEBUG
    // 检查程序是否 已经启动
    if(!AppUtils::isRunTimeOnly()){
        UIUtils::showInfoMsgBox(QObject::tr("%1 is runnig.").arg(a.applicationName()));
        return 0;
    }
#endif
    // 设置样式
    QString qss;
    QFile qssFile(DYNAMIC_DATA->getTheme());
    qssFile.open(QFile::ReadOnly);
    if(qssFile.isOpen()){
        qss = QLatin1String(qssFile.readAll());
        qApp->setStyleSheet(qss);
        qssFile.close();
    }
    
    MainWindow w;
    w.show();
    return a.exec();
}
