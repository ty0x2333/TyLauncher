#include "updatedialog.h"
#include "ui_updatedialog.h"
#include <QDesktopServices>

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
    ui->logoLbl->setToolTip(
                "<html><head/><body><p>" + 
                tr("Application Logo.") + 
                "</p><p><span style=\" font-weight:600;\">" + 
                tr("If you think it is not good, or you have better design. Please contact me.") + 
                "</span></p></body></html>"
                );
    ui->pushButtonUpdate->setVisible(false);
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

void UpdateDialog::setUpdateLink(const QString &updateLink)
{
    _updateLink = updateLink;
    ui->pushButtonUpdate->setVisible(!_updateLink.isEmpty());
}

void UpdateDialog::on_pushButtonUpdate_clicked()
{
    if (!(_updateLink.isEmpty())) {
        QUrl url(_updateLink);
        QDesktopServices::openUrl(url);
    }
}

void UpdateDialog::on_pushButtonOk_clicked()
{
    this->close();
}

void UpdateDialog::on_pushButtonCancel_clicked()
{
    this->close();
}
