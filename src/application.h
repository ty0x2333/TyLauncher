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
#ifndef APPLICATION_H
#define APPLICATION_H
#include <QApplication>
#if defined(qApp)
#undef qApp
#endif
#define qApp (static_cast<Application *>(QCoreApplication::instance()))

class Application : public QApplication
{
    Q_OBJECT
    Q_PROPERTY(QString githubRepository READ githubRepository WRITE setGithubRepository)

public:
    Application(int &argc, char **argv, int flags= ApplicationFlags);
    
    QString githubRepository() const;
    void setGithubRepository(const QString &githubRepository);
    
    QString issuesPostLink() const;
    
protected slots:
    void updateTheme();
    
protected:
    QString currentEnvironmentDescription() const;
    
    void configFromJsonFile();
    
    QString _githubRepository;
};

#endif // APPLICATION_H
