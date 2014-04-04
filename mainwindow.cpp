#include <QtWidgets>
#include <QFileDialog>
#include <QPainter>
#include <QtSvg>
#include <QFile>
#include "mainwindow.h"
#include "whiteboard.h"

MainWindow::MainWindow()
{
    QMenu *fileMenu = new QMenu(tr("&File"), this);
    QAction *saveAction = fileMenu->addAction(tr("&Save and Exit"));
    saveAction->setShortcut(QKeySequence(tr("Ctrl+S")));
    QAction *penColorAct = fileMenu->addAction(tr("Change Color"));
    //QAction *openAction = fileMenu->addAction(tr("&Open..."));
    //openAction->setShortcut(QKeySequence(tr("Ctrl+O")));
    QAction *quitAction = fileMenu->addAction(tr("E&xit"));
    quitAction->setShortcuts(QKeySequence::Quit);

    menuBar()->addMenu(fileMenu);

    connect(saveAction, SIGNAL(triggered()), this, SLOT(saveSvg()));
    //connect(openAction, SIGNAL(triggered()), this, SLOT(openSvg()));
    connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
    connect(penColorAct, SIGNAL(triggered()), this, SLOT(penColor()));

    whiteboard = new WhiteBoard;
    //blackboard = new BlackBoard;
    //setCentralWidget(blackboard);
    setCentralWidget(whiteboard);

    setWindowTitle(tr("VectorDraw"));
    resize(500, 525);


}


//! [save SVG]
void MainWindow::saveSvg()
{
    /*QString newPath = QFileDialog::getSaveFileName(this, tr("Save SVG"),
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
    //whiteboardsvg = new WhiteBoard;
    setCentralWidget(whiteboard);
//![end painting]
    painter.end();

    */
    whiteboard->svgSaver();
    QString oldPath = whiteboard->oldPath;
    QString newPath = QFileDialog::getSaveFileName(this, tr("Save SVG"),
        path, tr("SVG files (*.svg)"));

    if (newPath.isEmpty())
        return;

    qDebug() << oldPath;
    qDebug() << newPath;
    qDebug() << QFile::copy(oldPath, newPath);
}

void MainWindow::penColor()
 {
     QColor newColor = QColorDialog::getColor(whiteboard->penColor());
     if (newColor.isValid())
         whiteboard->setPenColor(newColor);
 }
