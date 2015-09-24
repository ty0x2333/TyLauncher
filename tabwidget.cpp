#include "tabwidget.h"
#include "ui_tabwidget.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QGridLayout>
#include <QTabBar>
#include <QMenu>
#include "AppButton.h"
#include "datasettings.h"
#include "TyLog_Qt.h"
#include "appbuttondialog.h"
#include "dynamicdata.h"
#include "utils/shearplateutils.h"
TabWidget::TabWidget(QWidget *parent)
    : QTabWidget(parent)
    , ui(new Ui::TabWidget)
    , _rowCount(DEFAULT_TAB_ROW_COUNT)
    , _columnCount(DEFAULT_TAB_COLUMN_COUNT)
    , _btnMenu(nullptr)
    , _btnCurMenu(nullptr)
{
    ui->setupUi(this);
    initBtnRightMenu();
    initTabs();
}

TabWidget::~TabWidget()
{
    if(_btnMenu!=nullptr)
        delete _btnMenu;
}

QString TabWidget::jsonString()
{
    QJsonDocument doc;
    QJsonArray tabArr;
    // 遍历所有tab
    for(int i = 0; i < this->count(); ++i){
        QJsonArray arr;
        QList<AppButton *> appButtonList = this->widget(i)->findChildren<AppButton *>();
        for(AppButton* btn : appButtonList){ // 遍历所有AppButton
            QJsonObject obj;
            obj.insert(KEY_HOT_KEY, btn->text());// 按钮的快捷键
            obj.insert(KEY_APP_NAME, btn->getAppName());// 按钮的应用名
            obj.insert(KEY_FILE_NAME, btn->getFileName());// 按钮的应用文件路径
            arr.append(obj);
        }
        tabArr.append(arr);
    }
    doc.setArray(tabArr);
    return doc.toJson();
}

bool TabWidget::configFromVector(QVector<QVector<AppInfo> > dataVector)
{
    Q_ASSERT(dataVector.size() == DEFAULT_TAB_COUNT); 
    try{
        // 每一个Tab
        for(int i = 0; i < DEFAULT_TAB_COUNT; ++i){
            QWidget *tab = this->widget(i);
            QGridLayout *layout = dynamic_cast<QGridLayout *>(tab->layout());
            Q_ASSERT_X(layout != nullptr, "configFromVector", "tab->layout() is not QGridLayout class!"); 
            QVector<AppInfo> arr = dataVector[i];
            Q_ASSERT_X(arr.size() == _rowCount * _columnCount, 
                       "configFromVector", 
                       QString("arr.size() == _rowCount * _columnCount, %1 != %2").arg(QString::number(arr.size())).arg(QString::number(_rowCount * _columnCount)).toUtf8().data());
            // 每一列
            for(int c = 0; c < _columnCount; ++c){
                // 每一行
                for(int r = 0; r < _rowCount; ++r){
                    QLayoutItem *item = layout->itemAtPosition(r, c);
                    QWidget *widget = item->widget();
                    AppButton *btn = dynamic_cast<AppButton*>(widget);
                    Q_ASSERT_X(btn != nullptr, "configFromVector", "item->widget() is not AppButton class!"); 
                    btn->setDataFromAppInfo(arr[c*_rowCount + r]);
                    connect(btn, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(onAppButtonRightClicked(QPoint)));
                }
            }
        }
    }catch(QString e){
        return false;
    }
    return true;
}

void TabWidget::clearAllAppBtnData()
{
    for(int i = 0; i < DEFAULT_TAB_COUNT; ++i){
        QWidget *tab = this->widget(i);
        QGridLayout *layout = dynamic_cast<QGridLayout *>(tab->layout());
        Q_ASSERT_X(layout != nullptr, "configFromVector", "tab->layout() is not QGridLayout class!"); 
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
}

void TabWidget::initTabs()
{
    for(int i = 0; i < 10; ++i){
        QWidget *tab = new QWidget();
        QGridLayout *layout = new QGridLayout();
        for(int c = 0; c < 10; ++c){
            for(int r = 0; r < 3; ++r){
                layout->addWidget(new AppButton(), r, c);
            }
        }
        tab->setLayout(layout);
        this->addTab(tab, QString::number((i + 1)%10));
    }
}

void TabWidget::initBtnRightMenu()
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

void TabWidget::onAppButtonRightClicked(QPoint)
{
    _btnCurMenu = (AppButton*)sender();
    bool isNotBtnEmpty = !_btnCurMenu->isEmpty();
    bool isNotBtnShearPlateEmpty = !DynamicData::getInstance()->BtnShearPlateIsEmpty();
    ui->actionOpenFolder->setEnabled(isNotBtnEmpty);// 打开文件夹
    ui->actionDelete->setEnabled(isNotBtnEmpty);// 删除
    ui->actionCopy->setEnabled(isNotBtnEmpty);// 复制
    ui->actionShear->setEnabled(isNotBtnEmpty);// 剪切
    ui->actionPaste->setEnabled(isNotBtnShearPlateEmpty);// 粘贴
    _btnMenu->exec(this->cursor().pos());
}

void TabWidget::on_actionOpenFolder_triggered()
{
    if(_btnCurMenu == nullptr)
        return;
    _btnCurMenu->openFileDirectory();
    _btnCurMenu = nullptr;
}

void TabWidget::on_actionDelete_triggered()
{
    if(_btnCurMenu == nullptr)
        return;
    ShearPlateUtils::remove(_btnCurMenu);
    _btnCurMenu = nullptr;
}

void TabWidget::on_actionCopy_triggered()
{
    if(_btnCurMenu == nullptr)
        return;
    ShearPlateUtils::copy(_btnCurMenu);
    _btnCurMenu = nullptr;
}

void TabWidget::on_actionShear_triggered()
{
    if(_btnCurMenu == nullptr)
        return;
    ShearPlateUtils::shear(_btnCurMenu);
    _btnCurMenu = nullptr;
}

void TabWidget::on_actionPaste_triggered()
{
    if(_btnCurMenu == nullptr)
        return;
    ShearPlateUtils::paste(_btnCurMenu);
    _btnCurMenu = nullptr;
}

void TabWidget::on_actionEdit_triggered()
{
    if(_btnCurMenu == nullptr)
        return;
//    _isCanHide = false;
    AppButtonDialog *appBtnDialog = new AppButtonDialog(this, _btnCurMenu);
    appBtnDialog->exec();
    _btnCurMenu = nullptr;
//    _isCanHide = true;
}
