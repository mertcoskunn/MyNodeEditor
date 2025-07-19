#include "NodeEditorScene.h"
#include <QDebug>
#include "NodeEditorView.h"
#include "../nodes/Node.h"  
#include "../nodes/nodetypes/PrintNode.h"
#include "../nodes/nodetypes/StartNode.h"
#include "../nodes/nodetypes/ConstantNode.h"
#include "../nodes/nodetypes/BranchNode.h"
#include "../nodes/nodetypes/math/SumNode.h"
#include "../nodes/nodetypes/math/DivisionNode.h"
#include "../nodes/nodetypes/math/MultiplyNode.h"
#include "../nodes/nodetypes/math/SubtractionNode.h"
#include "../nodes/ConnectionLine.h"
#include "../utils/JsonExporter.h"
#include "../utils/JsonImporter.h"

#include <QFileInfo>
#include <QDir>

NodeEditorScene::NodeEditorScene(QObject* parent)
    : QGraphicsScene(parent)
{
    setSceneRect(-5000, -5000, 10000, 10000);

    StartNode* node = new StartNode();
    startNode = node; 
    addItem(node);
    nodeList.push_back(node);
}


void NodeEditorScene::clearNodeList()
{
    nodeList.clear();
    this->clear();
}
void NodeEditorScene::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    if ((event->modifiers() & Qt::ControlModifier) && event->button() == Qt::LeftButton) {
        QList<QGraphicsItem*> itemsAtClick = items(event->scenePos());

        for (QGraphicsItem* item : itemsAtClick) {
            if (dynamic_cast<ConnectionLine*>(item)) {
                ConnectionLine* line = dynamic_cast<ConnectionLine*>(item);
                removeItem(line);
                delete line;
                return; 
            }

            if(dynamic_cast<Node*>(item)){
                Node* node = dynamic_cast<Node*>(item);
                for(Pin* pin : node->getAllPins())
                {
                    ConnectionLine* line = pin->getLine();
                    if(line){
                        removeItem(line);
                        delete line;
                    }
                }

                if(dynamic_cast<StartNode*>(node))
                    startNode = nullptr;

                nodeList.erase(std::remove(nodeList.begin(), nodeList.end(), node), nodeList.end());
                removeItem(item);
                delete item;
                numberOfNode --; 
                return; 
            }
        }
    }

    QGraphicsScene::mousePressEvent(event);
}
void NodeEditorScene::contextMenuEvent(QGraphicsSceneContextMenuEvent* event)
{
    Q_UNUSED(event);

    if(!itemAt(event->scenePos(), QTransform()))
    {
        QMenu menu;
        QAction *addStartNode = menu.addAction("Add Start Node");
        QAction *addSumNode = menu.addAction("Add Sum Node");
        QAction *addDivisionNode = menu.addAction("Add Division Node");
        QAction *addSubtractionNode = menu.addAction("Add Subtraction Node");
        QAction *addMultiplicationNode = menu.addAction("Add Multiplication Node");
        QAction *addBranchNode = menu.addAction("Add Branch Node");
        QAction *addPrintNode = menu.addAction("Add Print Node");
        QAction *addConstant = menu.addAction("Add Constant");
        QAction *run = menu.addAction("Run");

        QAction *selected = menu.exec(event->screenPos());


        if(selected == addStartNode)
        {
            if(startNode){
                QGraphicsView* view = this->views().first();
                view->centerOn(startNode);
                return; 
            }
            StartNode* node = new StartNode();
            node->setPos(event->scenePos());
            addItem(node);
            startNode = node;
            nodeList.push_back(node); 
        }

        if(selected == addSumNode)
        {
            SumNode* node = new SumNode();
            node->setPos(event->scenePos());
            addItem(node);

            numberOfNode++; 
            nodeList.push_back(node); 
            qDebug() << "New node added"; 
        }

        if(selected == addDivisionNode)
        {
            DivisionNode* node = new DivisionNode();
            node->setPos(event->scenePos());
            addItem(node);

            numberOfNode++;
            nodeList.push_back(node);
            qDebug() << "New node added"; 
        }

        if(selected == addSubtractionNode)
        {
            SubtractionNode* node = new SubtractionNode();
            node->setPos(event->scenePos());
            addItem(node);

            numberOfNode++;
            nodeList.push_back(node);
            qDebug() << "New node added"; 
        }

        if(selected == addMultiplicationNode)
        {
            MultiplyNode* node = new MultiplyNode();
            node->setPos(event->scenePos());
            addItem(node);

            numberOfNode++;
            nodeList.push_back(node); 
            qDebug() << "New node added"; 
        }

        if(selected == addBranchNode)
        {
            BranchNode* node = new BranchNode();
            node->setPos(event->scenePos());
            addItem(node);

            numberOfNode++;
            nodeList.push_back(node);
            qDebug() << "New node added"; 
        }

        if(selected == addPrintNode)
        {
            PrintNode* node = new PrintNode();
            node->setPos(event->scenePos());
            addItem(node);

            numberOfNode++;
            nodeList.push_back(node); 
            qDebug() << "New node added"; 
        }

        if(selected == addConstant)
        {
            ConstantNode* node = new ConstantNode();
            node->setPos(event->scenePos());
            addItem(node);

            numberOfNode++;
            nodeList.push_back(node); 
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