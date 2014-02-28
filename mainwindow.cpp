#include <QtWidgets>

#include "mainwindow.h"
#include "whiteboard.h"

//! [0]
MainWindow::MainWindow()
{
    whiteboard = new WhiteBoard;
    setCentralWidget(whiteboard);

    setWindowTitle(tr("VectorDraw"));
    resize(500, 500);
}
