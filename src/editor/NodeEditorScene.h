#pragma once

#include <QGraphicsScene>
#include <QGraphicsSceneContextMenuEvent>
#include <QMenu>

class NodeEditorScene : public QGraphicsScene
{
    Q_OBJECT

public:
    NodeEditorScene(QObject* parent = nullptr);
 

protected:
    void contextMenuEvent(QGraphicsSceneContextMenuEvent* event) override;

private:
    int numberOfNode; 
};