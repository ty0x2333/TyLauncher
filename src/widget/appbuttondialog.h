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
#ifndef APPBUTTONDIALOG_H
#define APPBUTTONDIALOG_H

#include <QDialog>

class AppButton;

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
    void on_pushButtonFile_clicked();
    
    void on_pushButtonDir_clicked();
        
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::AppButtonDialog *ui;
    AppButton *_btn;
};

#endif // APPBUTTONDIALOG_H
