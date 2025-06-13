#include "MainWindow.h"
#include "../editor/NodeEditorView.h"
#include <QGraphicsScene>
#include <QDockWidget>
#include <QListWidget>
#include <QHBoxLayout> 



MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    QGraphicsScene* scene =  new QGraphicsScene(this);
    scene->setSceneRect(-5000, -5000, 10000, 10000);

    NodeEditorView* view = new NodeEditorView;
    view->setScene(scene); 

    setCentralWidget(view); 
}
