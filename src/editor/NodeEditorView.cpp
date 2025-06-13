#include "NodeEditorView.h"


NodeEditorView::NodeEditorView(QWidget* parent)
    : QGraphicsView(parent)
{
    setRenderHint(QPainter::Antialiasing); 
    setDragMode(QGraphicsView::ScrollHandDrag);
    setTransformationAnchor(AnchorUnderMouse);
}


void NodeEditorView::wheelEvent(QWheelEvent* event)
{
    const double zoomFactor = 1.5f; 

    if(event->angleDelta().y()>0)
        scale(zoomFactor, zoomFactor); 
    else
        scale(1/scaleFactor, 1/scaleFactor); 
}
