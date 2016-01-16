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
