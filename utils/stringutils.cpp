#include "stringutils.h"
#include <QString>
#include "model/option.h"
#include "datasettings.h"

QString StringUtils::toString(QHash<QString, Option> options)
{
    QString str = "{";
    foreach ( const QString &key, options.keys() ) {
        str += QString("\n\t%1: %2,").arg(key).arg(options[key].value().toString());
    }
    str += "\n}";
    return str;
}

QString StringUtils::themeFileName(const QString &theme)
{
    return QString("%1%2%3%4").arg(FILE_NAME_THEME).arg("/").arg(theme).arg(".qss");
}
