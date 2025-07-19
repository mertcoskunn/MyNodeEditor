#include "NodeMenuBar.h"

NodeMenuBar::NodeMenuBar(QWidget* parent)
    : QMenuBar(parent)
{
    QMenu* fileMenu = this->addMenu("File");
    actionOpen = new QAction("Open", this);
    actionSave = new QAction("Save", this);
    fileMenu->addAction(actionOpen);
    fileMenu->addSeparator();
    fileMenu->addAction(actionSave);


    connect(actionSave, &QAction::triggered, this, &NodeMenuBar::saveRequested);
    connect(actionOpen, &QAction::triggered, this, &NodeMenuBar::openRequested); 
}
