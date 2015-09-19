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
    static int showCriticalMsgBox(const QString &content, QWidget *parent = 0, QMessageBox::StandardButton buttons = QMessageBox::Ok);
    static int showInfoMsgBox(const QString &content,  QWidget *parent = 0, QMessageBox::StandardButton buttons = QMessageBox::Ok);
    static int showWarnMsgBox(const QString &content, QWidget *parent = 0 , QMessageBox::StandardButton buttons = QMessageBox::Ok);
    /**
     * @brief showMessageBox
     * @param icon MessageBox Icon
     * @param title Dialog Title
     * @param content Message
     * @param parent Parent QWidget
     * @param buttons Dialog Buttons
     * @return Clicked Button Code
     */
    static int showMessageBox(QMessageBox::Icon icon, const QString &title, const QString &content, QWidget *parent = 0, QMessageBox::StandardButton buttons = QMessageBox::Ok);
};

#endif // __UI_UTILS_H__
