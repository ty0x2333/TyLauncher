#include "tabwidget.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
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
