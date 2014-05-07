#ifndef PREMADEFORMS_H
#define PREMADEFORMS_H
#include <QPoint>
#include <QPainterPath>
#include <QRect>
#include <QWidget>
class PreMadeForms
{
public:
    PreMadeForms();
    void CreateRectangleStage1(QPoint point1);
    void CreateRectangleStage2(QPoint point2);
    void CreateEllipseStage1(QPoint origin);
    void CreateEllipseStage2(QPoint outerPoint);
    void CreateStraightLineStage1(QPoint origin);
    void CreateStraightLineStage2(QPoint end);
    void CreateTriangleStage1(QPoint origin);
    void CreateTriangleStage2(QPoint point2);
    void CreateTriangleStage3(QPoint point3);
    bool scribblingShape;
    bool TrianglePoint1;
    bool TrianglePoint2;
    QPainterPath myPath;
    QColor myFormColor;
    QPoint Point1;
    QPoint Point2;
    QPoint Point3;
    QPoint Point4;
private:

    QPoint CenterPoint;
    QPoint OuterPoint;
    QPoint Radius;

};

#endif // PREMADEFORMS_H
