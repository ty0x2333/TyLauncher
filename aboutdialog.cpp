#include "aboutdialog.h"
#include "ui_aboutdialog.h"
#include "mainwindow.h"
AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutDialog)
{
    ui->setupUi(this);
    //setWindowFlags(Qt::FramelessWindowHint);
    this->setWindowTitle(tr("About ") + qApp->applicationName());
    ui->appNameLbl->setText(qApp->applicationName());
    ui->versionLbl->setText(qApp->applicationVersion());
}

AboutDialog::~AboutDialog()
{
    delete ui;
}

void AboutDialog::on_AboutDialog_finished(int)
{
    this->close();
}

void AboutDialog::on_buttonBox_accepted()
{
    this->close();
}
