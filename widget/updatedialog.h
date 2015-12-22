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
private:
    Ui::UpdateDialog *ui;
};

#endif // UPDATEDIALOG_H
