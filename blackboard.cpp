#include "blackboard.h"


BlackBoard::BlackBoard(QWidget *parent)
    : QWidget(parent)
{
    setAttribute(Qt::WA_StaticContents);
    begin = true;
}

void BlackBoard::resizeEvent(QResizeEvent *event)
{
    if (width() >= image.width() || height() >= image.height()) {
        int newWidth = qMax(width() , 600);
        int newHeight = qMax(height() , 600);
        resizeImage(&image, QSize(newWidth, newHeight));
        update();
    }
    QWidget::resizeEvent(event);
}

void BlackBoard::resizeImage(QImage *image, const QSize &newSize)
{
    if (image->size() == newSize)
        return;

    qDebug() << begin;
    if (begin) {
    QImage newImage(newSize, QImage::Format_RGB32);
    newImage.fill(qRgb(0, 0, 0));
    begin = false;
    }
}
