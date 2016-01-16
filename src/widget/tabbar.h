#ifndef TABBAR_H
#define TABBAR_H

#include <QTabBar>

class TabBar : public QTabBar
{
    Q_OBJECT
public:
    explicit TabBar(QWidget *parent = 0);
    
protected:
//    QSize sizeHint() const;
    
signals:
    
public slots:
};

#endif // TABBAR_H
