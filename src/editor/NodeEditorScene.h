#pragma once

#include <QGraphicsScene>
#include <QGraphicsSceneContextMenuEvent>
#include <QMenu>

class Node; 

class NodeEditorScene : public QGraphicsScene
{
    Q_OBJECT

public:
    NodeEditorScene(QObject* parent = nullptr);
 

protected:
    void contextMenuEvent(QGraphicsSceneContextMenuEvent* event) override;

private:
    int numberOfNode;
    Node* startNode; 
};