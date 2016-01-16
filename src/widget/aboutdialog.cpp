#include "aboutdialog.h"
#include "ui_aboutdialog.h"
#include "mainwindow.h"

static QString const kToolTipFormat = QString("<html><head/><body><p>%1</p><p><span style=\" font-weight:600;\">%2</span></p></body></html>");

AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutDialog)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags() | Qt::MSWindowsFixedSizeDialogHint);
    ui->versionLbl->setText(qApp->applicationVersion());
    
    ui->logoLbl->setToolTip(kToolTipFormat.arg(tr("Application Logo.")).arg(tr("If you think it is not good, or you have better design. Please contact me.")));

    ui->developerLbl->setToolTip(kToolTipFormat.arg(tr("Application Developer's email.")).arg(tr("You can <span style=\" font-weight:600\">contact me</span> through it.")));
    ui->websiteLbl->setToolTip(kToolTipFormat.arg(tr("Application Developer's personal website")).arg(tr("You can get more help here.")));
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
