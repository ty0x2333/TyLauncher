#include "appbuttonform.h"
#include "ui_appbuttonform.h"
#include "appbutton.h"
#include "model/appinfo.h"
#include "TyLog_Qt.h"
#include "datasettings.h"
#include <QGridLayout>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMenu>
#include "appbuttondialog.h"
#include "dynamicdata.h"
#include "shearplate.h"

AppButtonForm::AppButtonForm(const int &rowCount, const int &columnCount, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::AppButtonForm)
    , _rowCount(rowCount)
    , _columnCount(columnCount)
    , _btnMenu(nullptr)
    , _btnCurMenu(nullptr)
{
    ui->setupUi(this);
    QGridLayout *layout = new QGridLayout();
    for(int c = 0; c < _columnCount; ++c){
        for(int r = 0; r < _rowCount; ++r){
            layout->addWidget(new AppButton(), r, c);
        }
    }
    this->setLayout(layout);
    
    initBtnRightMenu();
}

void AppButtonForm::initBtnRightMenu()
{
    _btnMenu = new QMenu();
    _btnMenu->addAction(ui->actionOpenFolder);
    _btnMenu->addSeparator();
    _btnMenu->addAction(ui->actionEdit);
    _btnMenu->addSeparator();
    _btnMenu->addAction(ui->actionCopy);
    _btnMenu->addAction(ui->actionPaste);
    _btnMenu->addAction(ui->actionShear);
    _btnMenu->addAction(ui->actionDelete);
}

AppButtonForm::~AppButtonForm()
{
    delete ui;
    if(_btnMenu!=nullptr)
        delete _btnMenu;
}

bool AppButtonForm::configFromVector(QVector<AppInfo> dataVector)
{
    if (dataVector.size() != _rowCount * _columnCount){
        TyLogFatal("arr.size() == _rowCount * _columnCount, %d != %d", dataVector.size(), _rowCount * _columnCount);
        return false;
    }
    
    QGridLayout *layout = dynamic_cast<QGridLayout *>(this->layout());
    Q_ASSERT_X(layout != nullptr, "configFromVector", "layout() is not QGridLayout class!"); 
    for(int i = 0; i < _rowCount * _columnCount; ++i){
        QLayoutItem *item = layout->itemAtPosition(i / _columnCount, i % _columnCount);
        QWidget *widget = item->widget();
        AppButton *btn = dynamic_cast<AppButton*>(widget);
        Q_ASSERT_X(btn != nullptr, "configFromVector", "item->widget() is not AppButton class!"); 
        btn->setDataFromAppInfo(dataVector[i]);
        connect(btn, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(onAppButtonRightClicked(QPoint)));
    }
    return true;
}

void AppButtonForm::clearAllAppBtnData()
{
    QGridLayout *layout = dynamic_cast<QGridLayout *>(this->layout());
    Q_ASSERT_X(layout != nullptr, "configFromVector", "this->layout() is not QGridLayout class!"); 
    // 每一列
    for(int c = 0; c < _columnCount; ++c){
        // 每一行
        for(int r = 0; r < _rowCount; ++r){
            QLayoutItem *item = layout->itemAtPosition(r, c);
            QWidget *widget = item->widget();
            AppButton *btn = dynamic_cast<AppButton*>(widget);
            Q_ASSERT_X(btn != nullptr, "configFromVector", "item->widget() is not AppButton class!"); 
            btn->clear();
        }
    }
}

QJsonArray AppButtonForm::jsonArray() const
{
    QJsonArray result;
    QGridLayout *layout = dynamic_cast<QGridLayout *>(this->layout());
    for(int i = 0; i < _rowCount * _columnCount; ++i){
        QLayoutItem *item = layout->itemAtPosition(i / _columnCount, i % _columnCount);
        QWidget *widget = item->widget();
        AppButton *btn = dynamic_cast<AppButton*>(widget);
        QJsonObject obj;
        obj.insert(KEY_HOT_KEY, btn->text());// 按钮的快捷键
        obj.insert(KEY_APP_NAME, btn->getAppName());// 按钮的应用名
        obj.insert(KEY_FILE_NAME, btn->getFileName());// 按钮的应用文件路径
        result.append(obj);
    }
    return result;
}

void AppButtonForm::onAppButtonRightClicked(QPoint)
{
    _btnCurMenu = (AppButton*)sender();
    bool isNotBtnEmpty = !_btnCurMenu->isEmpty();
    bool isNotBtnShearPlateEmpty = !SHEAR_PLATE->isBtnShearPlateEmpty();
    ui->actionOpenFolder->setEnabled(isNotBtnEmpty);// 打开文件夹
    ui->actionDelete->setEnabled(isNotBtnEmpty);// 删除
    ui->actionCopy->setEnabled(isNotBtnEmpty);// 复制
    ui->actionShear->setEnabled(isNotBtnEmpty);// 剪切
    ui->actionPaste->setEnabled(isNotBtnShearPlateEmpty);// 粘贴
    _btnMenu->exec(this->cursor().pos());
}

void AppButtonForm::on_actionOpenFolder_triggered()
{
    if(_btnCurMenu == nullptr)
        return;
    _btnCurMenu->openFileDirectory();
    _btnCurMenu = nullptr;
}

void AppButtonForm::on_actionDelete_triggered()
{
    if(_btnCurMenu == nullptr)
        return;
    SHEAR_PLATE->remove(_btnCurMenu);
    _btnCurMenu = nullptr;
}

void AppButtonForm::on_actionCopy_triggered()
{
    if(_btnCurMenu == nullptr)
        return;
    SHEAR_PLATE->copy(_btnCurMenu);
    _btnCurMenu = nullptr;
}

void AppButtonForm::on_actionShear_triggered()
{
    if(_btnCurMenu == nullptr)
        return;
    SHEAR_PLATE->shear(_btnCurMenu);
    _btnCurMenu = nullptr;
}

void AppButtonForm::on_actionPaste_triggered()
{
    if(_btnCurMenu == nullptr)
        return;
    SHEAR_PLATE->paste(_btnCurMenu);
    _btnCurMenu = nullptr;
}

void AppButtonForm::on_actionEdit_triggered()
{
    if(_btnCurMenu == nullptr)
        return;
    AppButtonDialog *appBtnDialog = new AppButtonDialog(this, _btnCurMenu);
    appBtnDialog->exec();
    _btnCurMenu = nullptr;
}
