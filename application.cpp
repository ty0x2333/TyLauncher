#include "application.h"
#include "dynamicdata.h"
#include "TyLog_Qt.h"
#include "utils/stringutils.h"
#include <QFile>
Application::Application(int &argc, char **argv, int flags)
    : QApplication(argc, argv, flags)
{
    connect(DYNAMIC_DATA, SIGNAL(themeConfigChanged()), this, SLOT(updateTheme()));
}

void Application::updateTheme()
{
    // 设置样式
    QString qss;
    QString fileName = StringUtils::themeFileName(DYNAMIC_DATA->getTheme());
    TyLogDebug("fileName: %s", fileName.toUtf8().data());
    QFile qssFile(fileName);
    qssFile.open(QFile::ReadOnly);
    if(qssFile.isOpen()){
        qss = QLatin1String(qssFile.readAll());
        this->setStyleSheet(qss);
        qssFile.close();
    }else{
        this->setStyleSheet("");
    }
    
}
