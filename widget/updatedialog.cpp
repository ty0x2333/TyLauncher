#include "updatedialog.h"
#include "ui_updatedialog.h"

UpdateDialog::UpdateDialog(QWidget *parent, const QString &lastVersion, const QString &explainText)
    : QDialog(parent)
    , ui(new Ui::UpdateDialog)
{
    ui->setupUi(this);
    ui->lblCurrentVersion->setText(tr("Current Version: %1").arg(qApp->applicationVersion()));
    if (!lastVersion.isEmpty()){
        setLastVersion(lastVersion);
        if (!explainText.isEmpty()){
            setExplain(explainText);
        }
    }
}

UpdateDialog::~UpdateDialog()
{
    delete ui;
}

void UpdateDialog::setExplain(const QString &explainText)
{
    ui->textEditExplain->setText(explainText);
}

void UpdateDialog::setLastVersion(const QString &lastVersion)
{
    ui->lblLastVersion->setText(tr("Last Version: %1").arg(lastVersion));
}
