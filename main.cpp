#include "widget/mainwindow.h"
#include "application.h"
#include <QTranslator>
#include <QFile>
#include "dynamicdata.h"
#include "utils/apputils.h"
#include "utils/uiutils.h"
#include <QObject>
#include "utils/stringutils.h"

int main(int argc, char *argv[])
{
    Application a(argc, argv);
#ifndef QT_DEBUG
    // 检查程序是否 已经启动
    if(!AppUtils::isRunTimeOnly()){
        UIUtils::showInfoMsgBox(QObject::tr("%1 is runnig.").arg(a.applicationName()));
        return 0;
    }
#endif
    
    MainWindow w;
    w.show();
    return a.exec();
}
