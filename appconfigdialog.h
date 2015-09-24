#ifndef APPCONFIGDIALOG_H
#define APPCONFIGDIALOG_H

#include <QDialog>

namespace Ui {
class AppConfigDialog;
}

class AppConfigDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit AppConfigDialog(QWidget *parent = 0);
    ~AppConfigDialog();
    
private:
    Ui::AppConfigDialog *ui;
    
    void initLanguages();
};

#endif // APPCONFIGDIALOG_H
