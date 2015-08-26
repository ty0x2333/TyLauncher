#ifndef DYNAMICDATA_H
#define DYNAMICDATA_H
#include "appbutton.h"
#include <QString>
class DynamicData
{
public:
    static DynamicData* getInstance();
    // @brief 获取按钮剪切缓存
    AppButton* getBtnShearPlate();
    // @brief 设置按钮剪切缓存
    void setBtnShearPlate(AppButton *btn);
    // @brief 获取按钮剪切缓存是否为空
    bool BtnShearPlateIsEmpty();
    // @brief 保存设置
    void saveSettings();
    // @brief 读取设置
    void loadSettings();
    // @brief 获取主题
    QString getTheme();
    // @brief 设置存档路径
    void setSaveFileName(const QString &fileName);
    // @brief 获取存档路径
    QString getSaveFileName();
    // @brief 重置存档路径
    void resetSaveFileName();
    // @brief 设置主题
    void setTheme(const QString &theme);
    // @brief 读取存档文件
    QVector< QVector<AppInfo> > loadSaveFile(const QString fileName);
    // @brief 获取语言
    QString getLanguage();
    // @brief 设置语言
    void setLanguage(const QString &language);
private:
    DynamicData();
    // @brief 主题
    QString _theme;
    // @brief 语言
    QString _language;
    // @brief 存档路径
    QString _saveFileName;
    // @brief 按钮剪切缓存
    // 用来保存复制的按钮地址
    AppButton *_btnShearPlate;
};

#endif // DYNAMICDATA_H
