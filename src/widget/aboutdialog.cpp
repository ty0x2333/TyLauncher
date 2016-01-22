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
static QString const kLinkFormat = QString("<html><head/><body><style type=\"text/css\">a{color: hsl(219,58%,93%);text-decoration:none;}</style><p><a href=\"%1\">%2</a></p></body></html>");
AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutDialog)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags() | Qt::MSWindowsFixedSizeDialogHint);
    
    // ToolTip
    ui->developerLbl->setToolTip(kToolTipFormat.arg(tr("Application Developer's email.")).arg(tr("You can <span style=\" font-weight:600\">contact me</span> through it.")));
    ui->blogLbl->setToolTip(kToolTipFormat.arg(tr("Application Developer's personal website")).arg(tr("You can get more help here.")));
    // Text
    ui->versionLbl->setText(qApp->applicationVersion());
    ui->appNameLbl->setText(qAppName());
    ui->websiteURLLbl->setText(kLinkFormat.arg(qApp->organizationDomain(), qApp->organizationDomain()));
    ui->blogLbl->setText(kLinkFormat.arg("http://blog.tianyiyan.com", "http://blog.tianyiyan.com"));
    ui->developerLbl->setText(kLinkFormat.arg("mailto:luckytianyiyan@gmail.com", qApp->organizationName()));
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
