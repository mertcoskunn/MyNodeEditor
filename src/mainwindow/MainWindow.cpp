#include "MainWindow.h"
#include "../editor/NodeEditorScene.h"
#include "../editor/NodeEditorView.h"


MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    NodeEditorScene* scene = new NodeEditorScene();
    NodeEditorView* view = new NodeEditorView;

    view->setScene(scene);
    setCentralWidget(view);
}