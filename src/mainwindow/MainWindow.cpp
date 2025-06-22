#include "MainWindow.h"
#include <QGraphicsScene>
#include <QGraphicsView> 



MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    QGraphicsScene* scene = new QGraphicsScene();
    QGraphicsView* view = new QGraphicsView;

    view->setScene(scene);
    setCentralWidget(view);
}