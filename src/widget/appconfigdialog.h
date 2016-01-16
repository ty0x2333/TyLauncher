#ifndef APPCONFIGDIALOG_H
#define APPCONFIGDIALOG_H

#include <QDialog>
#include <QHash>

class Option;
class QAbstractButton;

namespace Ui {
class AppConfigDialog;
}

class AppConfigDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit AppConfigDialog(QWidget *parent = 0);
    ~AppConfigDialog();
    
private slots:
    void apply();
    void on_buttonBox_clicked(QAbstractButton *button);
    
private:
    Ui::AppConfigDialog *ui;
    
    QHash<QString, Option> _options;
    
    void initOptions();
    void initLanguages();
    void initThemes();
};

#endif // APPCONFIGDIALOG_H
