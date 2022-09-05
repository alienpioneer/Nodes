#include "MainWindow.h"
#include "Canvas.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setGeometry(QRect(0, 0, 600, 400));

    Canvas* frameWidget = new Canvas(QRect(25, 25, 550, 350), this);
    frameWidget->setStyleSheet("border:2px solid black;");
}

MainWindow::~MainWindow()
{
}

