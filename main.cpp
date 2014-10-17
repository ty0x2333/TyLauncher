#include "mainwindow.h"
#include <QApplication>
#include "StaticSetting.h"
#include <QTranslator>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName(VER_PRODUCTNAME_STR);
    a.setApplicationVersion(VER_FILEVERSION_DISPLAY_STR);
    MainWindow w;
    w.show();
    return a.exec();
}
