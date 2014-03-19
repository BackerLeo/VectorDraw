#include <QtWidgets>
#include <QFileDialog>
#include <QPainter>
#include <QtSvg>
#include "mainwindow.h"
#include "whiteboard.h"

//! [0]
MainWindow::MainWindow()
{
    QMenu *fileMenu = new QMenu(tr("&File"), this);
    QAction *saveAction = fileMenu->addAction(tr("&Save and Exit"));
    saveAction->setShortcut(QKeySequence(tr("Ctrl+S")));
    //QAction *openAction = fileMenu->addAction(tr("&Open..."));
    //openAction->setShortcut(QKeySequence(tr("Ctrl+O")));
    QAction *quitAction = fileMenu->addAction(tr("E&xit"));
    quitAction->setShortcuts(QKeySequence::Quit);

    menuBar()->addMenu(fileMenu);

    connect(saveAction, SIGNAL(triggered()), this, SLOT(saveSvg()));
    //connect(openAction, SIGNAL(triggered()), this, SLOT(openSvg()));
    connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));

    whiteboard = new WhiteBoard;
    setCentralWidget(whiteboard);

    setWindowTitle(tr("VectorDraw"));
    resize(500, 500);


}


//! [save SVG]
void MainWindow::saveSvg()
{
    whiteboard->svgSaver();
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
}

