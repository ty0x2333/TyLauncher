/**
 * Copyright (c) 2016, luckytianyiyan <luckytianyiyan@gmail.com>
 * 
 * This file is part of TyLauncher.
 * 
 * TyLauncher is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * TyLauncher is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with TyLauncher.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "application.h"
#include "dynamicdata.h"
#include "TyLog_Qt.h"
#include "utils/stringutils.h"
#include "StaticSetting.h"
#include <QFile>
Application::Application(int &argc, char **argv, int flags)
    : QApplication(argc, argv, flags)
{
    this->setApplicationName(VER_PRODUCTNAME_STR);
    this->setApplicationVersion(VER_FILEVERSION_DISPLAY_STR);
    
    updateTheme();
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
