#include <QtWidgets>
#include <QFileDialog>
#include <QPainter>
#include <QtSvg>
#include <QFile>
#include "mainwindow.h"
#include "whiteboard.h"
#include "premadeforms.h"

MainWindow::MainWindow()
{

    QMenu *fileMenu = new QMenu(tr("&File"), this);
    QAction *saveAction = fileMenu->addAction(tr("&Save and Exit"));
    saveAction->setShortcut(QKeySequence(tr("Ctrl+S")));
    QAction *penColorAct = fileMenu->addAction(tr("Change Color"));
    QAction *backColorAct = fileMenu->addAction(tr("Change Background Color"));
    //QAction *openAction = fileMenu->addAction(tr("&Open..."));
    //openAction->setShortcut(QKeySequence(tr("Ctrl+O")));
    QAction *quitAction = fileMenu->addAction(tr("E&xit"));
    quitAction->setShortcuts(QKeySequence::Quit);

    QMenu *shapeMenu = new QMenu(tr("&Add Shape"), this);
    QAction *addFreeAction = shapeMenu->addAction(tr("&Free Hand"));
    QAction *addEllipseAction = shapeMenu->addAction(tr("&Ellipse"));
    QAction *addRectangleAction = shapeMenu->addAction(tr("&Rectangle"));
    QAction *addLineAction = shapeMenu->addAction(tr("&Straigth line"));
    QAction *addTriangleAction = shapeMenu->addAction(tr("&Triangle"));

    menuBar()->addMenu(fileMenu);
    menuBar()->addMenu(shapeMenu);

    connect(saveAction, SIGNAL(triggered()), this, SLOT(saveSvg()));
    //connect(openAction, SIGNAL(triggered()), this, SLOT(openSvg()));
    connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
    connect(penColorAct, SIGNAL(triggered()), this, SLOT(penColor()));
    connect(backColorAct, SIGNAL(triggered()), this, SLOT(backColor()));
    connect(addFreeAction, SIGNAL(triggered()), this, SLOT(free()));
    connect(addEllipseAction, SIGNAL(triggered()), this, SLOT(Ellipse()));
    connect(addRectangleAction, SIGNAL(triggered()), this, SLOT(Rectangle()));
    connect(addLineAction, SIGNAL(triggered()), this, SLOT(StraightLine()));
    connect(addTriangleAction, SIGNAL(triggered()), this, SLOT(Triangle()));


    whiteboard = new WhiteBoard;
    //blackboard = new BlackBoard;
    //setCentralWidget(blackboard);
    setCentralWidget(whiteboard);

    setWindowTitle(tr("VectorDraw"));
    resize(500, 525);
    whiteboard->mode = 0; // 0 = desenho livre, 1 = circulo, 2 = retangulo, 3 = linha reta, 4 = triangulo

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
    qApp->quit();
}

void MainWindow::penColor()
 {
     QColor newColor = QColorDialog::getColor(whiteboard->penColor());
     if (newColor.isValid())
         whiteboard->setPenColor(newColor);
 }

void MainWindow::backColor()
 {
     QColor newColor = QColorDialog::getColor(whiteboard->backColor());
     if (newColor.isValid())
         whiteboard->setBackColor(newColor);
 }

void MainWindow::free(){
    whiteboard->mode = 0;
    qDebug()<<whiteboard->mode;
}
void MainWindow::Ellipse(){
    //PreMadeForms *forms = new PreMadeForms;
    whiteboard->mode = 1;
    qDebug()<<whiteboard->mode;
}
void MainWindow::Rectangle(){
    //PreMadeForms *forms = new PreMadeForms;
    whiteboard->mode = 2;
    qDebug()<<whiteboard->mode;
}
void MainWindow::StraightLine(){
    //PreMadeForms *forms = new PreMadeForms;
    whiteboard->mode = 3;
    qDebug()<<whiteboard->mode;
}
void MainWindow::Triangle(){
    //PreMadeForms *forms = new PreMadeForms;
    whiteboard->mode = 4;
    qDebug()<<whiteboard->mode;
}
