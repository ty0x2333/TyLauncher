#ifndef TABWIDGET_H
#define TABWIDGET_H

#include <QTabWidget>
#include <QString>
#include "model/appinfo.h"
QT_BEGIN_NAMESPACE
class QMenu;
class AppButton;
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
    bool configFromVector(QVector<QVector<AppInfo>>);
    /**
     * @brief clear all app button data
     * @note  hotkey will not clear.
     */
    void clearAllAppBtnData();
    
//    void setAppButtonsRightMenu
//    const char *readyReadMember
    
private slots:
    
private:
    Ui::TabWidget *ui;
    int _rowCount;
    int _columnCount;
    void initTabs();
};

#endif // TABWIDGET_H
