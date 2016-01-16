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
