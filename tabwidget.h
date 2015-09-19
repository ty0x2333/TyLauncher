#ifndef TABWIDGET_H
#define TABWIDGET_H

#include <QTabWidget>
#include <QString>

class TabWidget : public QTabWidget
{
public:
    explicit TabWidget(QWidget *parent = 0);
    QString jsonString();
};

#endif // TABWIDGET_H
