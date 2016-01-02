#include "tabwidget.h"
#include "ui_tabwidget.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QGridLayout>
#include <QTabBar>
#include <QResizeEvent>
#include <QKeyEvent>
#include "widget/appbutton.h"
#include "datasettings.h"
#include "TyLog_Qt.h"
#include "widget/appbuttondialog.h"
#include "dynamicdata.h"
#include "widget/appbuttonform.h"
#include "widget/tabbar.h"
#include "shearplate.h"

TabWidget::TabWidget(QWidget *parent)
    : QTabWidget(parent)
    , ui(new Ui::TabWidget)
    , _rowCount(DEFAULT_TAB_ROW_COUNT)
    , _columnCount(DEFAULT_TAB_COLUMN_COUNT)
{
    ui->setupUi(this);
    TabBar *tabBar = new TabBar(this);
    this->setTabBar(tabBar);
    this->tabBar()->setDocumentMode(true);
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

void TabWidget::keyReleaseEvent(QKeyEvent *keyEvent)
{
    if(keyEvent->modifiers() != Qt::ControlModifier){
        return;
    }
    
    QList<AppButton *> appButtonList = this->currentWidget()->findChildren<AppButton *>();
    switch(keyEvent->key())
    {
    case Qt::Key_C:
            for(AppButton* btn : appButtonList){ // 遍历所有AppButton，寻找当前鼠标指向的按钮
                if(btn->isBeMousePointing()){
                    SHEAR_PLATE->copy(btn);
                }
            }
        break;
    case Qt::Key_X:
            for(AppButton* btn : appButtonList){ // 遍历所有AppButton，寻找当前鼠标指向的按钮
                if(btn->isBeMousePointing()){
                    SHEAR_PLATE->shear(btn);
                }
            }
        break;
    case Qt::Key_V:
            for(AppButton* btn : appButtonList){ // 遍历所有AppButton
                if(btn->isBeMousePointing()){// 找到被鼠标指向的AppButton
                    SHEAR_PLATE->paste(btn);
                }
            }
        break;
    case Qt::Key_Z:
            SHEAR_PLATE->undo();
        break;
    default:
        break;
    }
}

void TabWidget::initTabs()
{
    for(int i = 0; i < DEFAULT_TAB_COUNT; ++i){
        this->addTab(new AppButtonForm(_rowCount, _columnCount, this), QString::number((i + 1)%10));
    }
}


