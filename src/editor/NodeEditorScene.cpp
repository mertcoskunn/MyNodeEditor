#include "NodeEditorScene.h"
#include <QDebug>
#include "../nodes/Node.h"
#include "../nodes/ConnectionLine.h"  

NodeEditorScene::NodeEditorScene(QObject* parent)
    : QGraphicsScene(parent)
{
    setSceneRect(-5000, -5000, 10000, 10000);

    Node* node = new Node();
    startNode = node; 
    addItem(node);
}


void NodeEditorScene::contextMenuEvent(QGraphicsSceneContextMenuEvent* event)
{
    Q_UNUSED(event);

    if(!itemAt(event->scenePos(), QTransform()))
    {
        QMenu menu;
        QAction *addNode = menu.addAction("Add New Node");
        QAction *run = menu.addAction("Run");

        QAction *selected = menu.exec(event->screenPos());

        if(selected == addNode)
        {
            Node* node = new Node();
            node->setPos(event->scenePos());
            addItem(node);

            numberOfNode++; 
            qDebug() << "New node added"; 
        }

        if(selected == run)
        {
            Node* tempNode = startNode;

            while (tempNode) {
                
                Pin* outPin = tempNode->getOutputExecutionPin();
                if (!outPin) break;
                
                ConnectionLine* line = outPin->getLine();
                if (!line) break;

                Pin* nextPin = line->getNextPin();
                if (!nextPin) break;

                QGraphicsItem* parent = nextPin->parentItem();
                if (!parent) break;

               
                Node* nextNode = dynamic_cast<Node*>(parent);
                if (!nextNode) break;

                tempNode->execute();
                tempNode = nextNode;
                
                }
         }
        }

}