#ifndef DYNAMICDATA_H
#define DYNAMICDATA_H
#include <QtGlobal>
#include <QString>
class AppButton;
class AppInfo;

class DynamicData
{
public:
    static DynamicData* getInstance();

    /// @brief 设置按钮剪切缓存
    void setBtnShearPlate(AppButton *btn);
    AppButton* getBtnShearPlate();

    /// @brief 获取按钮剪切缓存是否为空
    bool BtnShearPlateIsEmpty();

    /// @brief 保存设置
    void saveAppConfig();
    void loadAppConfig();

    /// @brief 设置存档路径
    void setSaveFileName(const QString &fileName);
    QString getSaveFileName();

    /// @brief 重置存档路径
    void resetSaveFileName();

    /// @brief 设置主题
    void setTheme(const QString &theme);
    QString getTheme();

    /// @brief 读取存档文件
    QVector< QVector<AppInfo> > loadSaveFile(const QString fileName);
    
    /// @brief 保存存档文件
    void saveUserSaveFile(const QString& content);

    void setLanguage(const QString &language);
    QString getLanguage();
private:
    DynamicData();

    QString _theme;

    QString _language;
    /// @brief 存档路径
    QString _saveFileName;
    /**
     * @brief 按钮剪切缓存
     * 用来保存复制的按钮地址
     */
    AppButton *_btnShearPlate;
    
    QString defaultSaveFileName();
};

#endif // DYNAMICDATA_H
