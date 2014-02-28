#ifndef WHITEBOARD_H
#define WHITEBOARD_H

#include <QColor>
#include <QImage>
#include <QPoint>
#include <QWidget>

//! [0]
class WhiteBoard : public QWidget
{
    Q_OBJECT

public:
    WhiteBoard(QWidget *parent = 0);

    void setPenColor(const QColor &newColor);
    void setPenWidth(int newWidth);

    QColor penColor() const { return myPenColor; }
    int penWidth() const { return myPenWidth; }

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
    int myPenWidth;
    QColor myPenColor;
    QImage image;
    QPoint lastPoint;
};
#endif