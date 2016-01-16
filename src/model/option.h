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
#ifndef __OPTION_H__
#define __OPTION_H__

#include <QVariant>

QT_BEGIN_NAMESPACE
class QObject;
QT_END_NAMESPACE

class Option
{
public:
    Option();
    /**
     * @brief Option
     * @param defaultValue 默认值
     * @param propertyName 控件属性Key
     * @param obj 控件
     */
    Option(const QVariant &defaultValue, 
           const char *propertyName = nullptr, 
           QObject *obj = nullptr
            );
    
    QString tooltip() const;
    
    QVariant value() const;
    bool setValue(const QVariant &val);
    
    void reset();
    
private:
    QVariant _defaultValue;
    QVariant _value;
    const char *_propertyName;
    QObject *_obj;
};

#endif // __OPTION_H__
