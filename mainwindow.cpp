#include <QtWidgets>
#include <QFileDialog>
#include <QPainter>
#include <QtSvg>
#include "mainwindow.h"
#include "whiteboard.h"

//! [0]
MainWindow::MainWindow()
{

    setWindowTitle(tr("VectorDraw"));
    resize(500, 500);
}


//! [save SVG]
void MainWindow::saveSvg()
{
    QString newPath = QFileDialog::getSaveFileName(this, tr("Save SVG"),
        path, tr("SVG files (*.svg)"));

    if (newPath.isEmpty())
        return;

    path = newPath;

//![configure SVG generator]
    QSvgGenerator generator;
    generator.setFileName(path);
    generator.setSize(QSize(500, 500));
    generator.setViewBox(QRect(0, 0, 500, 500));
    generator.setTitle(tr("SVG Drawing"));
    generator.setDescription(tr("An SVG drawing created by VectorDraw"));

//![begin painting]
    QPainter painter;
    painter.begin(&generator);
//![begin painting]
    whiteboard = new WhiteBoard;
    setCentralWidget(whiteboard);
//![end painting]
    painter.end();
}

