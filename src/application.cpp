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
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include "utils/apputils.h"
Application::Application(int &argc, char **argv, int flags)
    : QApplication(argc, argv, flags)
{
    this->setObjectName("Application");

    configFromJsonFile();
    
    updateTheme();
    connect(DYNAMIC_DATA, SIGNAL(themeConfigChanged()), this, SLOT(updateTheme()));
    
    TyLogDebug("Current Environment: %s", this->currentEnvironmentDescription().toUtf8().data());
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

QString Application::currentEnvironmentDescription() const
{
    QString description = "{";
    description.append("\n\tSystem: ");
    description.append(AppUtils::currentSystem());
    description.append("\n\tSystemVersion: ");
    description.append(AppUtils::currentSystemVersion());
    description.append("\n\tmacAddress: ");
    description.append(AppUtils::macAddress());
    description.append("\n\tdiskdriveSerialNumber: ");
    description.append(AppUtils::diskdriveSerialNumber());
    description.append("\n}");
    return description;
}

void Application::configFromJsonFile()
{
    QFile configFile(":/config.json");
    if(!configFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        TyLogFatal("can't open config.json");
        throw;
    }
    QByteArray bytes = configFile.readAll();
    configFile.close(); 
    
    QJsonParseError parseErr;
    QJsonDocument doc = QJsonDocument::fromJson(bytes,&parseErr);
    if(parseErr.error != QJsonParseError::NoError || !doc.isObject()){
        TyLogFatal("QJsonParseError: %s\n ", bytes.toStdString().data());
    }
    QJsonObject jsonObj = doc.object();
    QJsonObject applicationObj = jsonObj[this->objectName()].toObject();
    QStringList stringList = applicationObj.keys();
    
#if LOG_DEBUG
    QString logStr = "Application configuration {";
#endif
    for (QString key : stringList) {
        this->setProperty(key.toUtf8().data(), applicationObj[key].toString());
#if LOG_DEBUG
    logStr += QString("\n\t%1: %2").arg(key, applicationObj[key].toString());
#endif
    }
    TyLogDebug("%s\n}", logStr.toUtf8().data());
}
QString Application::applicationDescription() const
{
    return _applicationDescription;
}

void Application::setApplicationDescription(const QString &applicationDescription)
{
    _applicationDescription = applicationDescription;
}

QString Application::copyright() const
{
    return _copyright;
}

void Application::setCopyright(const QString &copyright)
{
    _copyright = copyright;
}

QString Application::organizationEmail() const
{
    return _organizationEmail;
}

void Application::setOrganizationEmail(const QString &organizationEmail)
{
    _organizationEmail = organizationEmail;
}

QString Application::githubRepository() const
{
    return _githubRepository;
}

void Application::setGithubRepository(const QString &githubRepository)
{
    _githubRepository = githubRepository;
}

QString Application::issuesPostLink() const
{
    return githubRepository().isEmpty() ? QString() : githubRepository() + "/issues/new";
}

