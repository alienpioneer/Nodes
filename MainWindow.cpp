#include "MainWindow.h"
#include "Canvas.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setGeometry(QRect(0, 0, 600, 400));

    Canvas* frameWidget = new Canvas(QRect(10, 10, 580, 380), this);
}

MainWindow::~MainWindow()
{
}

