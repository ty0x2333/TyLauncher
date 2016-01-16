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
#include "option.h"
#include <QObject>

#define KEY_PROPERTY_TOOL_TIP "toolTip"

namespace {

QString getToolTip(const QObject &obj)
{
    return obj.property(KEY_PROPERTY_TOOL_TIP).toString();
}

QString toolTip(const QObject &obj)
{
    const QString toolTip = getToolTip(obj);

    if (toolTip.isEmpty() && obj.parent())
        return getToolTip(*obj.parent());

    return toolTip;
}

} // namespace

Option::Option()
    : _defaultValue()
    , _value()
    , _propertyName(nullptr)
    , _obj(nullptr)
{}

Option::Option(const QVariant &defaultValue, 
               const char *propertyName, 
               QObject *obj)
    : _defaultValue(defaultValue)
    , _value()
    , _propertyName(propertyName)
    , _obj(obj)
{
    if (_obj){
        _obj->setProperty(_propertyName, _defaultValue);
    }
}

QVariant Option::value() const
{
    return _obj == nullptr ? _value : _obj->property(_propertyName);
}

bool Option::setValue(const QVariant &val)
{
    if (_obj != nullptr) {
        _obj->setProperty(_propertyName, val);
        return _obj->property(_propertyName) == val;
    }

    _value = val;
    return true;
}

void Option::reset()
{
    setValue(_defaultValue);
}

QString Option::tooltip() const
{
    return _obj == nullptr ? QString() : toolTip(*_obj);
}
