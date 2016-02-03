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
#ifndef APPSETTINGSDIALOG_H
#define APPSETTINGSDIALOG_H

#include <QDialog>
#include <QHash>

class Option;
class QAbstractButton;

namespace Ui {
class AppSettingsDialog;
}

class AppSettingsDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit AppSettingsDialog(QWidget *parent = 0);
    ~AppSettingsDialog();
    
private slots:
    void apply();
    void on_buttonBox_clicked(QAbstractButton *button);
    
private:
    Ui::AppSettingsDialog *ui;
    
    QHash<QString, Option> _options;
    
    void initOptions();
    void initLanguages();
    void initThemes();
};

#endif // APPSETTINGSDIALOG_H
