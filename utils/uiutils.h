#ifndef __UI_UTILS_H__
#define __UI_UTILS_H__
#include <QString>
#include <QMessageBox>

#define kCriticalMsgBoxTitle "Error"
#define kInfomationMsgBoxTitle "Information"
#define kWarningMsgBoxTitle "Warning"

class UIUtils
{
public:
    static int showCriticalMsgBox(const QString &content, QWidget *parent = 0);
    static int showInfoMsgBox(const QString &content, QWidget *parent = 0);
    static int showWarnMsgBox(const QString &content, QWidget *parent = 0);
};

#endif // __UI_UTILS_H__
