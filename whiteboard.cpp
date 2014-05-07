#include "whiteboard.h"
#include "premadeforms.h"

WhiteBoard::WhiteBoard(QWidget *parent)
    : QWidget(parent)
{
    setAttribute(Qt::WA_StaticContents);
    modified = false;
    scribbling = false;
    begin = true;
    myPenWidth = 1;
    myPenColor = Qt::black;
    myBackColor = Qt::white;
    oldPath = "";
    path = "";
    beginDrawing = true;
    Rect.setCoords(0, 0, 500, 500);

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
    counter = 0;
}

void WhiteBoard::setPenColor(const QColor &newColor)
{
    myPenColor = newColor;
}

void WhiteBoard::setBackColor(const QColor &newColor)
{
    myBackColor = newColor;
    image.fill(myBackColor);
    update();
}

void WhiteBoard::setPenWidth(int newWidth)
{
    myPenWidth = newWidth;
}
void WhiteBoard::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        if(mode == 0){
            lastPoint = event->pos();
            scribbling = true;
        }
        else{
        if((mode == 1)&& !(scribblingShape)){
            position = event->pos();
            qDebug()<< position;
            CreateEllipseStage1(position);
        }
        if((mode == 1)&& scribblingShape){
            position = event->pos();
            qDebug()<< position;
            CreateEllipseStage2(position);
        }
        if((mode == 2)&& !(scribblingShape)){
            position = event->pos();
            qDebug()<< "Ponto 1:" << position;
            CreateRectangleStage1(position);
        }
        if((mode == 2)&& (scribblingShape)){
            position = event->pos();
            qDebug()<< "Ponto 2:" << position;
            CreateRectangleStage2(position);
        }
        if((mode == 3)&& !(scribblingShape)){
            position = event->pos();
            qDebug()<< position;
            CreateStraightLineStage1(position);
        }
        if((mode == 3)&& (scribblingShape)){
            position = event->pos();
            qDebug()<< position;
            CreateStraightLineStage2(position);
        }
        if((mode == 4)&& !(TrianglePoint1)&& !(TrianglePoint2)){
            position = event->pos();
            qDebug()<< position;
            CreateTriangleStage1(position);
        }
        if((mode == 4)&& (TrianglePoint1)&& !(TrianglePoint2)){
            position = event->pos();
            qDebug()<< position;
            CreateTriangleStage2(position);
        }
        if((mode == 4)&&!(TrianglePoint1)&&(TrianglePoint2)){
            position = event->pos();
            qDebug()<< position;
            CreateTriangleStage3(position);
        }

            qDebug() << "Vou checar a myFormColor";
            forms.myFormColor = myPenColor;
            QPainter painter(&image);
            painter.setPen(QPen(forms.myFormColor, myPenWidth, Qt::SolidLine, Qt::RoundCap,
                                Qt::RoundJoin));

            painter.drawPath(forms.myPath);
            //qDebug()<< forms.myPath;
            //update( QRect(forms.Point1,forms.Point2).normalized());//(qMax(qMax(forms.Point1.rx(),forms.Point2.rx()),
                    //      qMax(forms.Point3.rx(),forms.Point4.rx())),
                    // (qMax(qMax(forms.Point1.ry(),forms.Point2.ry()),
                    //       qMax(forms.Point3.ry(),forms.Point4.ry()))),
                     //100, 100));
            modified = true;

            //painting on the svg
            if (beginDrawing)
            {
                path = "C:/Qt/Qt5.2.1/Tools/QtCreator/bin/build-VectorDraw-Desktop_Qt_5_2_1_MinGW_32bit-Debug/default.svg";
                generator.setFileName(path);
                generator.setSize(QSize(500, 500));
                generator.setViewBox(Rect);
                generator.setTitle(tr("SVG Drawing"));
                generator.setDescription(tr("An SVG drawing created by VectorDraw"));
                paintersvg.begin(&generator);
                oldPath = path;
                //QPainter painter;
                paintersvg.fillRect(Rect, myBackColor);
                beginDrawing = false;
            }
            paintersvg.setClipRect(Rect);
            paintersvg.setPen(QPen(myPenColor, myPenWidth, Qt::SolidLine, Qt::RoundCap,
                                Qt::RoundJoin));
            paintersvg.drawPath(forms.myPath);
        }
   }

}

void WhiteBoard::mouseMoveEvent(QMouseEvent *event)
{
    if ((event->buttons() & Qt::LeftButton) && scribbling)
        drawLineTo(event->pos());
}

void WhiteBoard::mouseReleaseEvent(QMouseEvent *event){
    if (event->button() == Qt::LeftButton && scribbling) {
        drawLineTo(event->pos());
        scribbling = false;
    }
}

void WhiteBoard::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QRect dirtyRect = event->rect();
    painter.drawImage(dirtyRect, image, dirtyRect);
}

void WhiteBoard::resizeEvent(QResizeEvent *event)
{
    if (width() >= image.width() || height() >= image.height()) {
        //int newWidth = qMax(width() , 500);
        int newWidth = 400;
        //int newHeight = qMax(height() , 500);
        int newHeight = 500;
        resizeImage(&image, QSize(newWidth, newHeight));
        update();
    }
    QWidget::resizeEvent(event);
}


void WhiteBoard::drawLineTo(const QPoint &endPoint)
{
    QPainter painter(&image);
    painter.setPen(QPen(myPenColor, myPenWidth, Qt::SolidLine, Qt::RoundCap,
                        Qt::RoundJoin));
    painter.drawLine(lastPoint, endPoint);
    modified = true;

    int rad = (myPenWidth / 2) + 2;
    update(QRect(lastPoint, endPoint).normalized()
                                     .adjusted(-rad, -rad, +rad, +rad));

    //painting on the svg

    if (beginDrawing)
    {
        /*
         * QString newPath = QFileDialog::getSaveFileName(this, tr("Save SVG"),
            path, tr("SVG files (*.svg)"));

        if (newPath.isEmpty())
            return;
        */
        path = "C:/Qt/Qt5.2.1/Tools/QtCreator/bin/build-VectorDraw-Desktop_Qt_5_2_1_MinGW_32bit-Debug/default.svg";
        generator.setFileName(path);
        generator.setSize(QSize(500, 500));
        generator.setViewBox(Rect);
        generator.setTitle(tr("SVG Drawing"));
        generator.setDescription(tr("An SVG drawing created by VectorDraw"));
        paintersvg.begin(&generator);
        oldPath = path;


    }
    //QPainter painter;
    if (beginDrawing)
    {
        paintersvg.fillRect(Rect, myBackColor);
        beginDrawing = false;
    }

    paintersvg.setClipRect(Rect);
    paintersvg.setPen(QPen(myPenColor, myPenWidth, Qt::SolidLine, Qt::RoundCap,
                        Qt::RoundJoin));
    paintersvg.drawLine(QLine(lastPoint, endPoint));
    //paintersvg.end();
    lastPoint = endPoint;

}

void WhiteBoard::drawLineTo(const QPoint &startPoint, const QPoint &endPoint)
{
    QPainter painter(&image);
    painter.setPen(QPen(myPenColor, myPenWidth, Qt::SolidLine, Qt::RoundCap,
                        Qt::RoundJoin));
    painter.drawLine(startPoint, endPoint);
    modified = true;

    int rad = (myPenWidth / 2) + 2;
    update(QRect(startPoint, endPoint).normalized()
                                     .adjusted(-rad, -rad, +rad, +rad));
}

 void WhiteBoard::svgSaver()
{
    paintersvg.end();

}


void WhiteBoard::resizeImage(QImage *image, const QSize &newSize)
{

    if (image->size() == newSize)
        return;

    if (begin) {
    QImage newImage(newSize, QImage::Format_RGB32);
    newImage.fill(myBackColor);
    QPainter painter(&newImage);
    painter.drawImage(QPoint(0, 0), *image);
    *image = newImage;
    begin = false;
    }

}

/* objeto para desenhar formas pré-definidas
void WhiteBoard::automaticPaint(QPainter &painter) //a função recebe o painter
{
    //pensar se os painters já estão ajustados corretamente

    painter.setPen(Qt::NoPen); //não vamos usar a caneta nesse momento

    //case para as formas
    case "forma"
    {
        painter.translate(); //setar posição de início da forma
        painter.setBrush(); //cor do desenho
        painter.drawPath("forma"); //desenhar forma
        painter.translate(); //transladar o retorno
    }

    painter.setPen(Qt::black); //voltar a caneta ao "normal"
}
*/

void WhiteBoard::CreateRectangleStage1(QPoint point1){
        Point1 = point1;
        qDebug()<< "Stage 1 Ponto 1:" << position;
        scribblingShape = true;
}

 void WhiteBoard::CreateRectangleStage2(QPoint point2){
        if(point2==Point1) {
            return;
        }
        Point2 = point2;
        qDebug()<< "Stage 2 Ponto 2:" << position;
        Point3.rx() = Point2.rx();
        Point3.ry() = Point1.ry();
        Point4.rx() = Point1.rx();
        Point4.ry() = Point2.ry();

        // Set pen to this point.
        //myPath.moveTo (Point1.rx(), Point1.ry());
        // Draw line from pen point to this point.

        //myPath.lineTo (Point3.rx(), Point3.ry());
        drawLineTo(Point1, Point3);

        //path.moveTo (endPointX1, endPointY1); // <- no need to move
        //myPath.lineTo (Point2.rx(), Point2.ry());
        drawLineTo(Point3, Point2);

        //path.moveTo (endPointX2,   endPointY2); // <- no need to move
        //myPath.lineTo (Point4.rx(), Point4.ry());
        drawLineTo(Point2, Point4);

        //myPath.lineTo (Point1.rx(), Point1.ry());
        drawLineTo(Point4, Point1);

        scribblingShape = false;
 }

 void WhiteBoard::CreateStraightLineStage1(QPoint origin){

         Point1 = origin;
         scribblingShape = true;
 }

 void WhiteBoard::CreateStraightLineStage2 (QPoint end){
     if(end==Point1) {
         return;
     }
         Point2 = end;
         //QPainterPath myPath;
         // Set pen to this point.
         //myPath.moveTo (Point1.rx(), Point1.ry());
         // Draw line from pen point to this point.
         //myPath.lineTo (Point2.rx(), Point2.ry());
         drawLineTo(Point1, Point2);
         scribblingShape = false;
 }

 void WhiteBoard::CreateTriangleStage1(QPoint origin){

         Point1 = origin;
         TrianglePoint1 = true;
 }
 void WhiteBoard::CreateTriangleStage2(QPoint point2){
     if(point2==Point1) {
         return;
     }
         Point2 = point2;
         TrianglePoint1 = false;
         TrianglePoint2 = true;
 }
 void WhiteBoard::CreateTriangleStage3(QPoint point3){
     if(point3==Point2) {
         return;
     }
         Point3 = point3;
         //QPainterPath myPath;
         //myPath.moveTo (Point1.rx(), Point1.ry());
         //myPath.lineTo(Point2.rx(),Point2.ry());
         drawLineTo(Point1, Point2);
         //myPath.lineTo(Point3.rx(),Point3.ry());
         drawLineTo(Point2,Point3);
         //myPath.lineTo(Point1.rx(), Point1.ry());
         drawLineTo(Point3,Point1);
         TrianglePoint1 = false;
         TrianglePoint2 = false;

 }


 void WhiteBoard::CreateEllipseStage1(QPoint origin){
         CenterPoint = origin;
         scribblingShape = true;
 }

  void WhiteBoard::CreateEllipseStage2(QPoint outerPoint){
      if(outerPoint==CenterPoint) {
          return;
      }
         qreal PI = 52163 / 16604;
         double counter = 0;
         OuterPoint = outerPoint;
         Radius.rx()= qSqrt(qPow(OuterPoint.rx() - CenterPoint.rx(),2) + qPow(OuterPoint.ry() - CenterPoint.ry(),2));
         //Radius.ry()= OuterPoint.ry() - CenterPoint.ry();
         Radius.ry() = Radius.rx();

         Point1 = CenterPoint;

         for (counter = 0  ; counter <= 1.25 ; counter = counter + 0.001 )
         {
             qDebug() << counter;
             Point1.rx() = CenterPoint.rx() + Radius.rx() * qCos( counter * 2*PI);
             Point1.ry() = CenterPoint.ry() + Radius.rx() * qSin( counter * 2*PI);
             Point2.rx() = CenterPoint.rx() + Radius.rx() * qCos( (counter+0.001) * 2*PI);
             Point2.ry() = CenterPoint.ry() + Radius.rx() * qSin( (counter+0.001) * 2*PI);
             drawLineTo(Point1, Point2);

         }

         //myPath.addEllipse(CenterPoint.rx(),CenterPoint.ry(),30,30);
         scribblingShape = false;

 }
