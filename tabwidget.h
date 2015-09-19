#ifndef TABWIDGET_H
#define TABWIDGET_H

#include <QTabWidget>
#include <QString>
#include "model/appinfo.h"

class TabWidget : public QTabWidget
{
public:
    explicit TabWidget(QWidget *parent = 0);
    QString jsonString();
    bool configFromVector(QVector<QVector<AppInfo>>);
};

#endif // TABWIDGET_H
