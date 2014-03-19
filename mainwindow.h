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
public slots:
    void saveSvg();
protected:

private slots:

private:
    //QString path;
    WhiteBoard *whiteboard;
    //WhiteBoard *whiteboardsvg;
};

#endif
