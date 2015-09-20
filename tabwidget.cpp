#include "tabwidget.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QGridLayout>
#include <QTabBar>
#include "AppButton.h"
#include "datasettings.h"
#include "TyLog_Qt.h"
TabWidget::TabWidget(QWidget *parent)
    : QTabWidget(parent)
    , _rowCount(DEFAULT_TAB_ROW_COUNT)
    , _columnCount(DEFAULT_TAB_COLUMN_COUNT)
{
    initTabs();
}

QString TabWidget::jsonString()
{
    QJsonDocument doc;
    QJsonArray tabArr;
    for(int i = 0; i < this->count(); ++i)// 遍历所有tab
    {
        QJsonArray arr;
        QList<AppButton *> appButtonList = this->findChildren<AppButton *>();
        for(AppButton* btn : appButtonList){ // 遍历所有AppButton
            QJsonObject obj;
            obj.insert(KEY_HOT_KEY, btn->text());// 按钮的快捷键
            obj.insert(KEY_APP_NAME, btn->getAppName());// 按钮的应用名
            obj.insert(KEY_FILE_NAME, btn->getFileName());// 按钮的应用文件路径
            arr.append(obj);
        }
        tabArr.append(arr);
    }
    doc.setArray(tabArr);
    return doc.toJson();
}

bool TabWidget::configFromVector(QVector<QVector<AppInfo> > dataVector)
{
    Q_ASSERT(dataVector.size() == DEFAULT_TAB_COUNT); 
    try
    {
        for(int i = 0; i < DEFAULT_TAB_COUNT; ++i)// 每一个Tab
        {
            QWidget *tab = this->widget(i);
            QGridLayout *layout = dynamic_cast<QGridLayout *>(tab->layout());
            Q_ASSERT_X(layout != nullptr, "configFromVector", "tab->layout() is not QGridLayout class!"); 
            QVector<AppInfo> arr = dataVector[i];
            Q_ASSERT(arr.size() == _rowCount * _columnCount * DEFAULT_TAB_COUNT); 
            // 每一列
            for(int c = 0; c < _columnCount; ++c){
                // 每一行
                for(int r = 0; r < _rowCount; ++r){
                    QLayoutItem *item = layout->itemAtPosition(r, c);
                    QWidget *widget = item->widget();
                    AppButton *btn = dynamic_cast<AppButton*>(widget);
                    Q_ASSERT_X(btn != nullptr, "configFromVector", "item->widget() is not AppButton class!"); 
                    btn->setDataFromAppInfo(arr[i * _rowCount * _columnCount + c*_rowCount + r]);
                }
            }
        }
    }catch(QString e){
        return false;
    }
    return true;
}

void TabWidget::clearAllAppBtnData()
{
    for(int i = 0; i < DEFAULT_TAB_COUNT; ++i)// 每一个Tab
    {
        QWidget *tab = this->widget(i);
        QGridLayout *layout = dynamic_cast<QGridLayout *>(tab->layout());
        Q_ASSERT_X(layout != nullptr, "configFromVector", "tab->layout() is not QGridLayout class!"); 
        // 每一列
        for(int c = 0; c < _columnCount; ++c){
            // 每一行
            for(int r = 0; r < _rowCount; ++r){
                QLayoutItem *item = layout->itemAtPosition(r, c);
                QWidget *widget = item->widget();
                AppButton *btn = dynamic_cast<AppButton*>(widget);
                Q_ASSERT_X(btn != nullptr, "configFromVector", "item->widget() is not AppButton class!"); 
                btn->clear();
            }
        }
    }
}

void TabWidget::initTabs()
{
    for(int i = 0; i < 10; ++i){
        QWidget *tab = new QWidget();
        QGridLayout *layout = new QGridLayout();
        for(int c = 0; c < 10; ++c){
            for(int r = 0; r < 3; ++r){
                layout->addWidget(new AppButton(), r, c);
            }
        }
        tab->setLayout(layout);
        this->addTab(tab, QString::number((i + 1)%10));
    }
}
