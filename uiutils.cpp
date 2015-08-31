#include "uiutils.h"
#include <QObject>

int UIUtils::showCriticalMsgBox(const QString &content, QWidget *parent)
{
    QMessageBox msgBox(QMessageBox::Critical, 
                               QObject::tr(kCriticalMsgBoxTitle), 
                               content, 
                               QMessageBox::Yes, 
                               parent, Qt::WindowStaysOnTopHint);
    
    
    return msgBox.exec();
}

int UIUtils::showInfoMsgBox(const QString &content, QWidget *parent)
{
    QMessageBox msgBox(QMessageBox::Information, 
                           QObject::tr(kInfomationMsgBoxTitle), 
                           content, 
                           QMessageBox::Yes | QMessageBox::No, 
                           parent, Qt::WindowStaysOnTopHint);
    return msgBox.exec();
}

int UIUtils::showWarnMsgBox(const QString &content, QWidget *parent)
{
    QMessageBox msgBox(QMessageBox::Information, 
                           QObject::tr(kWarningMsgBoxTitle), 
                           content, 
                           QMessageBox::Yes | QMessageBox::No, 
                           parent, Qt::WindowStaysOnTopHint);
    return msgBox.exec();
}

