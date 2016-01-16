#ifndef TABWIDGET_H
#define TABWIDGET_H

#include <QTabWidget>
#include <QString>
#include "model/appbtninfo.h"
QT_BEGIN_NAMESPACE
class QMenu;
class AppButton;
class QKeyEvent;
QT_END_NAMESPACE

namespace Ui {
class TabWidget;
}

class TabWidget : public QTabWidget
{
    Q_OBJECT
    
public:
    explicit TabWidget(QWidget *parent = 0);
    ~TabWidget();
    QString jsonString() const;
    bool configFromVector(QVector<QVector<AppBtnInfo>>);
    /**
     * @brief clear all app button data
     * @note  hotkey will not clear.
     */
    void clearAllAppBtnData();
    
protected:
    
    void keyReleaseEvent(QKeyEvent* keyEvent);
    
private slots:
    
private:
    Ui::TabWidget *ui;
    int _rowCount;
    int _columnCount;
    void initTabs();
};

#endif // TABWIDGET_H
