    #include "premadeforms.h"
    #include <QGraphicsScene>
    #include <QGraphicsItem>
    #include <QGraphicsView>
    #include "whiteboard.h"
    #include "qmath.h"
    #include "mainwindow.h"


    PreMadeForms::PreMadeForms(){

        Point1 = QPoint(0,0);
        Point2 = QPoint(0,0);
        Point3 = QPoint(0,0);
        Point4 = QPoint(0,0);
        CenterPoint = QPoint(0,0);
        OuterPoint = QPoint(0,0);
        Radius = QPoint(0,0);
        scribblingShape = false;
        TrianglePoint1 = false;
        TrianglePoint2 = false;
        myPath = QPainterPath(QPoint(0,0));
        myFormColor = Qt::black;
    }

    void PreMadeForms::CreateEllipseStage1(QPoint origin){
            CenterPoint = origin;
            scribblingShape = true;
    }
     void PreMadeForms::CreateEllipseStage2(QPoint outerPoint){
         if(outerPoint==CenterPoint) {
             return;
         }
            OuterPoint = outerPoint;
            Radius.rx()= qSqrt(qPow(OuterPoint.rx() - CenterPoint.rx(),2) + qPow(OuterPoint.ry() - CenterPoint.ry(),2));
            //Radius.ry()= OuterPoint.ry() - CenterPoint.ry();
            Radius.ry() = Radius.rx();
            myPath.addEllipse(CenterPoint,Radius.rx(),Radius.ry());
            //myPath.addEllipse(CenterPoint.rx(),CenterPoint.ry(),30,30);
            scribblingShape = false;

    }
    void PreMadeForms::CreateRectangleStage1(QPoint point1){
            Point1 = point1;
            scribblingShape = true;
    }
     void PreMadeForms::CreateRectangleStage2(QPoint point2){
            if(point2==Point1) {
                return;
            }
            Point2 = point2;
            Point3.rx() = Point2.rx();
            Point3.ry() = Point1.ry();
            Point4.rx() = Point1.rx();
            Point4.ry() = Point2.ry();

            // Set pen to this point.
            myPath.moveTo (Point1.rx(), Point1.ry());
            // Draw line from pen point to this point.

            //myPath.lineTo (Point3.rx(), Point3.ry());
            //drawLineTo(Point1, Point3);

            //path.moveTo (endPointX1, endPointY1); // <- no need to move
            myPath.lineTo (Point2.rx(), Point2.ry());

            //path.moveTo (endPointX2,   endPointY2); // <- no need to move
            myPath.lineTo (Point4.rx(), Point4.ry());
            myPath.lineTo (Point1.rx(), Point1.ry());
            scribblingShape = false;

    }
    void PreMadeForms::CreateStraightLineStage1(QPoint origin){

            Point1 = origin;
            scribblingShape = true;
    }

    void PreMadeForms::CreateStraightLineStage2 (QPoint end){
        if(end==Point1) {
            return;
        }
            Point2 = end;
            //QPainterPath myPath;
            // Set pen to this point.
            myPath.moveTo (Point1.rx(), Point1.ry());
            // Draw line from pen point to this point.
            myPath.lineTo (Point2.rx(), Point2.ry());
            scribblingShape = false;
    }

    void PreMadeForms::CreateTriangleStage1(QPoint origin){

            Point1 = origin;
            TrianglePoint1 = true;
    }
    void PreMadeForms::CreateTriangleStage2(QPoint point2){
        if(point2==Point1) {
            return;
        }
            Point2 = point2;
            TrianglePoint1 = false;
            TrianglePoint2 = true;
    }
    void PreMadeForms::CreateTriangleStage3(QPoint point3){
        if(point3==Point2) {
            return;
        }
            Point3 = point3;
            //QPainterPath myPath;
            myPath.moveTo (Point1.rx(), Point1.ry());
            myPath.lineTo(Point2.rx(),Point2.ry());
            myPath.lineTo(Point3.rx(),Point3.ry());
            myPath.lineTo(Point1.rx(), Point1.ry());
            TrianglePoint1 = false;
            TrianglePoint2 = false;

    }
