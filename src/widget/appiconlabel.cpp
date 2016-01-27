#include "appiconlabel.h"
#include <QFileIconProvider>
#include <QResizeEvent>
#include "TyLog_Qt.h"

static const int kDefaultIconExtent = 48;
static const int kDefaultMinExtent = 48;

AppIconLabel::AppIconLabel(QWidget *parent, Qt::WindowFlags f)
    : QLabel(parent, f)
{
    this->setMinimumSize(kDefaultMinExtent, kDefaultMinExtent);
    this->setSizePolicy(QSizePolicy::MinimumExpanding,QSizePolicy::MinimumExpanding);
    this->setAlignment(Qt::AlignCenter);
    this->setScaledContents(true);
}

void AppIconLabel::setIconFromFileName(const QString &fileName)
{
    if (fileName.isEmpty()) {
        return;
    }
    QFileIconProvider iconProvider;
    QIcon icon = iconProvider.icon(QFileInfo(fileName));
    this->setIcon(icon);
}

void AppIconLabel::setIcon(const QIcon &icon)
{
//    QList<QSize> availableSizes = icon.availableSizes();
//    QSize maxSize;
//    for (QSize size : availableSizes) {
//        if (size.width() > maxSize.width()) {
//            maxSize = size;
//        }
//    }
    this->setPixmap(icon.pixmap(kDefaultIconExtent));
}

void AppIconLabel::resizeEvent(QResizeEvent *event)
{
    QLabel::resizeEvent(event);
    QSize size = event->size();
    if (size.height() == size.width()) {
        return;
    }
    int minExtent = size.width() < size.height() ? size.width() : size.height();
    this->resize(QSize(minExtent, minExtent));
}


