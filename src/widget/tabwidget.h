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
#ifndef TABWIDGET_H
#define TABWIDGET_H

#include <QTabWidget>
#include <QString>
#include "model/appbtninfo.h"
QT_BEGIN_NAMESPACE
class QMenu;
class AppButton;
class QKeyEvent;
QT_END_NAMESPACE

namespace Ui {
class TabWidget;
}

class TabWidget : public QTabWidget
{
    Q_OBJECT
    
public:
    explicit TabWidget(QWidget *parent = 0);
    ~TabWidget();
    QString jsonString() const;
    bool configFromVector(QVector<QVector<AppBtnInfo>>);
    /**
     * @brief clear all app button data
     * @note  hotkey will not clear.
     */
    void clearAllAppBtnData();
    
protected:
    
    void keyReleaseEvent(QKeyEvent* keyEvent);
    
private slots:
    
private:
    Ui::TabWidget *ui;
    int _rowCount;
    int _columnCount;
    void initTabs();
};

#endif // TABWIDGET_H
