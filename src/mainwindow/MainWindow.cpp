#include "MainWindow.h"
#include "../editor/NodeEditorScene.h"
#include <QGraphicsView> 



MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    NodeEditorScene* scene = new NodeEditorScene();
    QGraphicsView* view = new QGraphicsView;

    view->setScene(scene);
    setCentralWidget(view);
}