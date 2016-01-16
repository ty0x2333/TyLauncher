#include "tabbar.h"

TabBar::TabBar(QWidget *parent)
    : QTabBar(parent)
{
//    tabBar->setObjectName(QLatin1String("qt_tabwidget_tabbar"));
    // Importent! Remove the white line on border-top
    setDrawBase(false);
//    setDocumentMode(true);
}

//QSize TabBar::sizeHint() const
//{
//    QWidget *parent = this->parentWidget();
//    QSize result = QTabBar::sizeHint();
//    if (parent != nullptr){
//        result.setWidth(parent->geometry().width());
//    }
//    return result;
//}
