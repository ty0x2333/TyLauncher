#include "tabwidget.h"
#include "ui_tabwidget.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QGridLayout>
#include <QTabBar>
#include "widget/appbutton.h"
#include "datasettings.h"
#include "TyLog_Qt.h"
#include "widget/appbuttondialog.h"
#include "dynamicdata.h"
#include "widget/appbuttonform.h"
TabWidget::TabWidget(QWidget *parent)
    : QTabWidget(parent)
    , ui(new Ui::TabWidget)
    , _rowCount(DEFAULT_TAB_ROW_COUNT)
    , _columnCount(DEFAULT_TAB_COLUMN_COUNT)
{
    ui->setupUi(this);
    initTabs();
}

TabWidget::~TabWidget()
{
    delete ui;
}

QString TabWidget::jsonString() const
{
    QJsonDocument doc;
    QJsonArray tabArr;
    // 遍历所有tab
    for(int i = 0; i < this->count(); ++i){
        AppButtonForm* tab = dynamic_cast<AppButtonForm*>(this->widget(i));
        tabArr.append(tab->jsonArray());
    }
    doc.setArray(tabArr);
    return doc.toJson();
}

bool TabWidget::configFromVector(QVector<QVector<AppInfo> > dataVector)
{
    Q_ASSERT(dataVector.size() == DEFAULT_TAB_COUNT); 
    try{
        // 每一个Tab
        for(int i = 0; i < DEFAULT_TAB_COUNT; ++i){
            AppButtonForm *tab = dynamic_cast<AppButtonForm*>(this->widget(i));
            tab->configFromVector(dataVector[i]);
        }
    }catch(QString e){
        return false;
    }
    return true;
}

void TabWidget::clearAllAppBtnData()
{
    for(int i = 0; i < DEFAULT_TAB_COUNT; ++i){
        AppButtonForm *tab = dynamic_cast<AppButtonForm*>(this->widget(i));
        tab->clearAllAppBtnData();
    }
}

void TabWidget::initTabs()
{
    for(int i = 0; i < 10; ++i){
        this->addTab(new AppButtonForm(3, 10, this), QString::number((i + 1)%10));
    }
}


