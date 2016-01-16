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
