#include "NodeEditorScene.h"
#include <QDebug>
#include "../nodes/Node.h"  
#include "../nodes/nodetypes/PrintNode.h"
#include "../nodes/nodetypes/StartNode.h"
#include "../nodes/nodetypes/ConstantNode.h"
#include "../nodes/nodetypes/math/SumNode.h"
#include "../nodes/nodetypes/math/DivisionNode.h"
#include "../nodes/nodetypes/math/MultiplyNode.h"
#include "../nodes/nodetypes/math/SubtractionNode.h"
#include "../nodes/ConnectionLine.h"  

NodeEditorScene::NodeEditorScene(QObject* parent)
    : QGraphicsScene(parent)
{
    setSceneRect(-5000, -5000, 10000, 10000);

    //Node* node = new Node();
    //startNode = node; 
    //addItem(node);

    StartNode* node = new StartNode();
    startNode = node; 
    addItem(node);
}


void NodeEditorScene::contextMenuEvent(QGraphicsSceneContextMenuEvent* event)
{
    Q_UNUSED(event);

    if(!itemAt(event->scenePos(), QTransform()))
    {
        QMenu menu;
        QAction *addSumNode = menu.addAction("Add Sum Node");
        QAction *addDivisionNode = menu.addAction("Add Division Node");
        QAction *addSubtractionNode = menu.addAction("Add Subtraction Node");
        QAction *addMultiplicationNode = menu.addAction("Add Multiplication Node");
        QAction *addPrintNode = menu.addAction("Add Print Node");
        QAction *addConstant = menu.addAction("Add Constant");
        QAction *run = menu.addAction("Run");

        QAction *selected = menu.exec(event->screenPos());

        if(selected == addSumNode)
        {
            SumNode* node = new SumNode();
            node->setPos(event->scenePos());
            addItem(node);

            numberOfNode++; 
            qDebug() << "New node added"; 
        }

        if(selected == addDivisionNode)
        {
            DivisionNode* node = new DivisionNode();
            node->setPos(event->scenePos());
            addItem(node);

            numberOfNode++; 
            qDebug() << "New node added"; 
        }

        if(selected == addSubtractionNode)
        {
            SubtractionNode* node = new SubtractionNode();
            node->setPos(event->scenePos());
            addItem(node);

            numberOfNode++; 
            qDebug() << "New node added"; 
        }

        if(selected == addMultiplicationNode)
        {
            MultiplyNode* node = new MultiplyNode();
            node->setPos(event->scenePos());
            addItem(node);

            numberOfNode++; 
            qDebug() << "New node added"; 
        }

        if(selected == addPrintNode)
        {
            PrintNode* node = new PrintNode();
            node->setPos(event->scenePos());
            addItem(node);

            numberOfNode++; 
            qDebug() << "New node added"; 
        }

        if(selected == addConstant)
        {
            ConstantNode* node = new ConstantNode();
            node->setPos(event->scenePos());
            addItem(node);

            numberOfNode++; 
            qDebug() << "New node added"; 
        }

        if(selected == run)
        {
            Node* tempNode = startNode;

            while (tempNode) {

                tempNode->execute();
                
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
                tempNode = nextNode;
                
                }
         }
        }
}