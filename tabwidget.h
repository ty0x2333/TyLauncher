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
    /**
     * @brief clear all app button data
     * @note  hotkey will not clear.
     */
    void clearAllAppBtnData();
private:
    int _rowCount;
    int _columnCount;
    void initTabs();
};

#endif // TABWIDGET_H
