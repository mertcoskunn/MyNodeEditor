#include "NodeEditorScene.h"
#include <QDebug>


NodeEditorScene::NodeEditorScene(QObject* parent)
    : QGraphicsScene(parent)
{
    setSceneRect(-5000, -5000, 10000, 10000);
}


void NodeEditorScene::contextMenuEvent(QGraphicsSceneContextMenuEvent* event)
{
    Q_UNUSED(event);

    if(!itemAt(event->scenePos(), QTransform()))
    {
        QMenu menu;
        QAction *addNode = menu.addAction("Add New Node");

        QAction *selected = menu.exec(event->screenPos());

        if(selected == addNode)
        {
            qDebug() << "New node added"; 
        }

    }

}