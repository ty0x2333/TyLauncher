/**
 * Copyright (c) 2016, luckytianyiyan <luckytianyiyan@gmail.com>
 * 
 * This file is part of TyLauncher.
 * 
 * TyLauncher is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * TyLauncher is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with TyLauncher.  If not, see <http://www.gnu.org/licenses/>.
 */
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
