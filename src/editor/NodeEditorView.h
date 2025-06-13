#pragma once

#include <QGraphicsView> 
#include <QWheelEvent> 



class NodeEditorView : public QGraphicsView {
    Q_OBJECT

public: 
    NodeEditorView(QWidget* parent = nullptr);
    void wheelEvent(QWheelEvent* event) override; 

private:
    double scaleFactor = 1.0; 
};


