#ifndef APPCONFIGDIALOG_H
#define APPCONFIGDIALOG_H

#include <QDialog>
#include <QHash>

class Option;

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
    
    QHash<QString, Option> _options;
    
    void initOptions();
    void initLanguages();
};

#endif // APPCONFIGDIALOG_H
