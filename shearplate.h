#ifndef SHEARPLATE_H
#define SHEARPLATE_H

#include <QObject>

#define SHEAR_PLATE ShearPlate::getInstance()

QT_FORWARD_DECLARE_CLASS(AppButton)
QT_FORWARD_DECLARE_CLASS(QUndoStack)

class ShearPlate : public QObject
{
    Q_OBJECT
public:
    static ShearPlate* getInstance();
    
    bool copy(AppButton *btn);
    void shear(AppButton *btn);
    void paste(AppButton *btn);
    void remove(AppButton *btn);
    
    void undo();
    void redo();

    AppButton* getBtnShearPlate();
    void setBtnShearPlate(AppButton *btn);
    
    /// @brief 获取按钮剪切缓存是否为空
    bool isBtnShearPlateEmpty();
    
    QUndoStack *undoStack() const;
    
signals:
    
public slots:
    
private:
    explicit ShearPlate(QObject *parent = 0);
    /**
     * @brief 按钮剪切缓存
     * 用来保存复制的按钮地址
     */
    AppButton *_btnShearPlate;
    
    QUndoStack *_undoStack;
};

#endif // SHEARPLATE_H
