#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QList>
#include <QMainWindow>

class WhiteBoard;
class BlackBoard;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();
public slots:
    void saveSvg();
    void penColor();
protected:

private slots:

private:
    QString path;
    WhiteBoard *whiteboard;
    BlackBoard *blackboard;
    QAction *penColorAct;
    //WhiteBoard *whiteboardsvg;

};

#endif
