#ifndef __STRINGUTILS_H__
#define __STRINGUTILS_H__

#include <QHash>
QT_BEGIN_NAMESPACE
class QString;
QT_END_NAMESPACE
class Option;

class StringUtils
{
public:
    static QString toString(QHash<QString, Option> options);
};

#endif // __STRINGUTILS_H__
