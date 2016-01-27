#ifndef APPICONLABEL_H
#define APPICONLABEL_H
#include <QLabel>
#include <QIcon>

class AppIconLabel : public QLabel
{
public:
    explicit AppIconLabel(QWidget *parent=0, Qt::WindowFlags f=0);
    
    void setIconFromFileName(const QString& fileName);
    
    void resizeEvent(QResizeEvent *event);
    
    void setIcon(const QIcon &icon);
};

#endif // APPICONLABEL_H
