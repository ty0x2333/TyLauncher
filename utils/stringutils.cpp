#include "stringutils.h"
#include <QString>
#include "model/option.h"

QString StringUtils::toString(QHash<QString, Option> options)
{
    QString str = "{";
    foreach ( const QString &key, options.keys() ) {
        str += QString("\n\t%1: %2,").arg(key).arg(options[key].value().toString());
    }
    str += "\n}";
    return str;
}
