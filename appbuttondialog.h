#ifndef APPBUTTONDIALOG_H
#define APPBUTTONDIALOG_H

#include <QDialog>
#include "appbutton.h"
namespace Ui {
class AppButtonDialog;
}

class AppButtonDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit AppButtonDialog(QWidget *parent = 0, AppButton *btn = nullptr);
    ~AppButtonDialog();
    
private slots:
    void on_pushButtonOk_clicked();
    
    void on_pushButtonFile_clicked();
    
    void on_pushButtonDir_clicked();
    
    void on_pushButtonCancel_clicked();
    
private:
    Ui::AppButtonDialog *ui;
    AppButton *_btn;
};

#endif // APPBUTTONDIALOG_H
