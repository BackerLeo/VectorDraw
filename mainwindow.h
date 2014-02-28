#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QList>
#include <QMainWindow>

class WhiteBoard;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();

protected:

private slots:

private:

    WhiteBoard *whiteboard;
};

#endif
