#include "aboutdialog.h"
#include "ui_aboutdialog.h"
#include "mainwindow.h"
AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutDialog)
{
    ui->setupUi(this);
    //setWindowFlags(Qt::FramelessWindowHint);
    QString str = "";
    str += tr("Name: ") + qApp->applicationName() + "\n";
    str += tr("Version: ") + qApp->applicationVersion();
    ui->textBrowser->setText(str);
}

AboutDialog::~AboutDialog()
{
    delete ui;
}

void AboutDialog::on_AboutDialog_finished(int)
{
    ((MainWindow*)this->parent())->setisCanHide(true);
    this->close();
}

void AboutDialog::on_pushButton_clicked()
{
    ((MainWindow*)this->parent())->setisCanHide(true);
    this->close();
}
