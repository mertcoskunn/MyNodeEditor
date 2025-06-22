#include "NodeEditorView.h"



NodeEditorView::NodeEditorView(QWidget* parent)
    :QGraphicsView(parent)
{
    setRenderHint(QPainter::Antialiasing);
    setDragMode(QGraphicsView::ScrollHandDrag);
    setTransformationAnchor(AnchorUnderMouse); 
}



void NodeEditorView::wheelEvent(QWheelEvent* event)
{
    if(event->angleDelta().y()>0)
        scale(zoomFactor, zoomFactor);
    else
        scale(1/zoomFactor, 1/zoomFactor); 
}