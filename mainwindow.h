#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QList>
#include <QMainWindow>
#include "premadeforms.h"

class WhiteBoard;
class BlackBoard;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();
    WhiteBoard *whiteboard;
public slots:
    void saveSvg();
    void penColor();
    void backColor();
    void free();
    void Ellipse();
    void Rectangle();
    void StraightLine();
    void Triangle();

protected:

private slots:

private:
    QString path;

    //BlackBoard *blackboard;
    QAction *penColorAct;
    QAction *backColorAct;
    PreMadeForms *forms;
    //WhiteBoard *whiteboardsvg;
};

#endif
