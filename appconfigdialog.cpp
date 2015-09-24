#include "appconfigdialog.h"
#include "ui_appconfigdialog.h"

AppConfigDialog::AppConfigDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AppConfigDialog)
{
    ui->setupUi(this);
}

AppConfigDialog::~AppConfigDialog()
{
    delete ui;
}
