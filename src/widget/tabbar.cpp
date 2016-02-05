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
#include "tabbar.h"
#include "TyLog_Qt.h"
#include <QHBoxLayout>
#include <QStyleOptionTab>

TabBar::TabBar(QWidget *parent)
    : QTabBar(parent)
{
    setDrawBase(false);
}

void TabBar::resizeEvent(QResizeEvent *e)
{
    QTabBar::resizeEvent(e);
    this->setStyleSheet(QString("QTabBar::tab { min-width: %1px;}")
                          .arg(this->parentWidget()->size().width() / this->count()));
}
