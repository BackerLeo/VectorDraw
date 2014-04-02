#ifndef BLACKBOARD_H
#define BLACKBOARD_H

#include <QColor>
#include <QImage>
#include <QPoint>
#include <QWidget>
#include <QSvgGenerator>
#include <QtWidgets>
#include <QGraphicsScene>
#include <QPaintEvent>

class BlackBoard : public QWidget
{
    Q_OBJECT

public:
    BlackBoard(QWidget *parent = 0);

    void drawBackground(QPainter *p, const QRectF &rect);

public slots:

protected:
    //void mousePressEvent(QMouseEvent *event);
    //void mouseMoveEvent(QMouseEvent *event);
    //void mouseReleaseEvent(QMouseEvent *event);
    //void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent *event);

private:
    //void drawLineTo(const QPoint &endPoint);
    void resizeImage(QImage *image, const QSize &newSize);

    bool begin;
    QImage image;
};
#endif
