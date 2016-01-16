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
    void clearBtn(AppButton *btn);
    
    explicit ShearPlate(QObject *parent = 0);
    /**
     * @brief 按钮剪切缓存
     * 用来保存复制的按钮地址
     */
    AppButton *_btnShearPlate;
    
    QUndoStack *_undoStack;
};

#endif // SHEARPLATE_H
