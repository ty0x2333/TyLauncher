#ifndef __SHEARPLATEUTILS_H__
#define __SHEARPLATEUTILS_H__
#include <QObject>
QT_BEGIN_NAMESPACE
class AppButton;
QT_END_NAMESPACE

class ShearPlateUtils
{
public:
    static bool copy(AppButton *btn);
    static void shear(AppButton *btn);
    static void paste(AppButton *btn);
    static void remove(AppButton *btn);
};

#endif // __SHEARPLATEUTILS_H__
