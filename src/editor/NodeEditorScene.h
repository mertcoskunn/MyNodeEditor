#pragma once

#include <QGraphicsScene>
#include <QGraphicsSceneContextMenuEvent>
#include <QMenu>

class Node; 
class StartNode;


class NodeEditorScene : public QGraphicsScene
{
    Q_OBJECT

public:
    NodeEditorScene(QObject* parent = nullptr);
    std::vector<Node*> getNodeList(){ return nodeList; };
    void clearNodeList(); 
    StartNode* getStartNode(){return startNode;} ; 
    void setStartNode(StartNode* node){startNode = node;} ;
    std::vector<Node*> nodeList; 

protected:
    void contextMenuEvent(QGraphicsSceneContextMenuEvent* event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;

private:
    int numberOfNode;
    StartNode* startNode;
    
};