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
#include <QRect>
#include "premadeforms.h"


class WhiteBoard : public QWidget
{
    Q_OBJECT

public:
    WhiteBoard(QWidget *parent = 0);

    void setPenColor(const QColor &newColor);
    void setBackColor(const QColor &newColor);
    void setPenWidth(int newWidth);

    QColor backColor() const { return myBackColor; }
    QColor penColor() const { return myPenColor; }
    int penWidth() const { return myPenWidth; }

    void drawBackground(QPainter *p, const QRectF &rect);
    void svgSaver();
    QString oldPath;
    PreMadeForms forms;
    int mode;
    void drawLineTo(const QPoint &endPoint);
    void drawLineTo(const QPoint &startPoint, const QPoint &endPoint);

public slots:


protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent *event);

private:
    //void drawLineTo(const QPoint &endPoint);
    void resizeImage(QImage *image, const QSize &newSize);
    void CreateRectangleStage1(QPoint point1);
    void CreateRectangleStage2(QPoint point2);
    void CreateEllipseStage1(QPoint origin);
    void CreateEllipseStage2(QPoint outerPoint);
    void CreateStraightLineStage1(QPoint origin);
    void CreateStraightLineStage2(QPoint end);
    void CreateTriangleStage1(QPoint origin);
    void CreateTriangleStage2(QPoint point2);
    void CreateTriangleStage3(QPoint point3);

    bool modified;
    bool scribbling;
    bool begin;
    bool beginDrawing;
    int myPenWidth;
    QColor myPenColor;
    QColor myBackColor;
    QImage image;
    QPoint lastPoint;
    QPoint position;
    QString path;
    QSvgGenerator generator;
    QPainter paintersvg;
    QRect Rect;

    bool scribblingShape;
    bool TrianglePoint1;
    bool TrianglePoint2;
    QPainterPath myPath;
    QColor myFormColor;
    QPoint Point1;
    QPoint Point2;
    QPoint Point3;
    QPoint Point4;
    QPoint CenterPoint;
    QPoint OuterPoint;
    QPoint Radius;
    int counter;
};
#endif
