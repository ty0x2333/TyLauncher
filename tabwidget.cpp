#include "tabwidget.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QGridLayout>
#include "AppButton.h"
#include "datasettings.h"
TabWidget::TabWidget(QWidget *parent)
    : QTabWidget(parent)
{
}

QString TabWidget::jsonString()
{
    QJsonDocument doc;
    QJsonArray tabArr;
    for(int i = 0; i < this->count(); ++i)// 遍历所有tab
    {
        QJsonArray arr;
        QList<AppButton *> appButtonList = this->findChildren<AppButton *>();
        for(AppButton* btn : appButtonList) // 遍历所有AppButton
        {
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
    this->clear();// 清除所有tab
    try
    {
        for(int i = 0; i < 10; ++i)// 每一个Tab
        {
            QWidget *tab = new QWidget();
            QGridLayout *layout = new QGridLayout();
            QVector<AppInfo> arr = dataVector[i];
            // 每一列
            for(int c = 0; c < 10; ++c){
                // 每一行
                for(int r = 0; r < 3; ++r){
                    AppInfo appInfo = arr[c*3 + r];
                    AppButton *btn = new AppButton(appInfo);
                    connect(btn, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(onBtnRightClicked(QPoint)));
                    layout->addWidget(btn, r, c);
                }
            }
            tab->setLayout(layout);
            this->addTab(tab, QString::number((i + 1) % 10));
        }
    }catch(QString e){
        return false;
    }
    return true;
}
