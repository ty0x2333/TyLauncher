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
#ifndef UPDATEDIALOG_H
#define UPDATEDIALOG_H

#include <QDialog>

namespace Ui {
class UpdateDialog;
}

class UpdateDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit UpdateDialog(QWidget *parent = 0, const QString& lastVersion = QString(), const QString& explainText = QString());
    ~UpdateDialog();
    
    void setExplain(const QString& explainText);
    void setLastVersion(const QString& lastVersion);
    void setUpdateLink(const QString& updateLink);
private slots:
    void on_pushButtonUpdate_clicked();
    
    void on_pushButtonOk_clicked();
    
    void on_pushButtonCancel_clicked();
    
private:
    Ui::UpdateDialog *ui;
    QString _updateLink;
};

#endif // UPDATEDIALOG_H
