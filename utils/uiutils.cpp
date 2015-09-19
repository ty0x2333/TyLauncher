#include "uiutils.h"
#include <QObject>

int UIUtils::showCriticalMsgBox(const QString &content, QWidget *parent, QMessageBox::StandardButton buttons)
{
    return showMessageBox(QMessageBox::Critical, QObject::tr(kCriticalMsgBoxTitle), content, parent, buttons);
}

int UIUtils::showInfoMsgBox(const QString &content, QWidget *parent, QMessageBox::StandardButton buttons)
{
    return showMessageBox(QMessageBox::Information, QObject::tr(kInfomationMsgBoxTitle), content, parent, buttons);
}

int UIUtils::showWarnMsgBox(const QString &content, QWidget *parent, QMessageBox::StandardButton buttons)
{
    return showMessageBox(QMessageBox::Warning, QObject::tr(kWarningMsgBoxTitle), content, parent, buttons);
}

int UIUtils::showMessageBox(QMessageBox::Icon icon, const QString &title, const QString &content, QWidget *parent, QMessageBox::StandardButton buttons)
{
    QMessageBox msgBox(icon, title, content, buttons, parent, Qt::WindowStaysOnTopHint);
    return msgBox.exec();
}

