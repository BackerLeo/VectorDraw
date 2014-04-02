#include "whiteboard.h"

WhiteBoard::WhiteBoard(QWidget *parent)
    : QWidget(parent)
{
    setAttribute(Qt::WA_StaticContents);
    modified = false;
    scribbling = false;
    begin = true;
    myPenWidth = 1;
    myPenColor = Qt::black;
    oldPath = "";
    path = "";
    beginDrawing = true;
}

void WhiteBoard::setPenColor(const QColor &newColor)
{
    myPenColor = newColor;
}

void WhiteBoard::setPenWidth(int newWidth)
{
    myPenWidth = newWidth;
}

void WhiteBoard::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        lastPoint = event->pos();
        scribbling = true;
    }
}

void WhiteBoard::mouseMoveEvent(QMouseEvent *event)
{
    if ((event->buttons() & Qt::LeftButton) && scribbling)
        drawLineTo(event->pos());
}

void WhiteBoard::mouseReleaseEvent(QMouseEvent *event)
{
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
        generator.setViewBox(QRect(0, 0, 500, 500));
        generator.setTitle(tr("SVG Drawing"));
        generator.setDescription(tr("An SVG drawing created by VectorDraw"));
        paintersvg.begin(&generator);
        oldPath = path;


    }
    //QPainter painter;
    if (beginDrawing)
    {
        paintersvg.fillRect(QRect(0, 0, 500, 500), Qt::white);
        beginDrawing = false;
    }
    paintersvg.setClipRect(QRect(0, 0, 500, 500));
    paintersvg.setPen(QPen(myPenColor, myPenWidth, Qt::SolidLine, Qt::RoundCap,
                        Qt::RoundJoin));
    paintersvg.drawLine(QLine(lastPoint, endPoint));
    //paintersvg.end();

    lastPoint = endPoint;


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
    newImage.fill(qRgb(255, 255, 255));
    QPainter painter(&newImage);
    painter.drawImage(QPoint(0, 0), *image);
    *image = newImage;
    begin = false;
    }

}
