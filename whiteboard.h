#ifndef WHITEBOARD_H
#define WHITEBOARD_H

#include <QColor>
#include <QImage>
#include <QPoint>
#include <QWidget>
#include <QSvgGenerator>
#include <QtWidgets>
#include <QGraphicsScene>
#include <QPaintEvent>

class WhiteBoard : public QWidget
{
    Q_OBJECT

public:
    WhiteBoard(QWidget *parent = 0);

    void setPenColor(const QColor &newColor);
    void setPenWidth(int newWidth);

    QColor penColor() const { return myPenColor; }
    int penWidth() const { return myPenWidth; }

    void drawBackground(QPainter *p, const QRectF &rect);
    void svgSaver();
    QString oldPath;


public slots:


protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent *event);

private:
    void drawLineTo(const QPoint &endPoint);
    void resizeImage(QImage *image, const QSize &newSize);

    bool modified;
    bool scribbling;
    bool begin;
    bool beginDrawing;
    int myPenWidth;
    QColor myPenColor;
    QImage image;
    QPoint lastPoint;
    QString path;
    QSvgGenerator generator;
    QPainter paintersvg;

};
#endif
