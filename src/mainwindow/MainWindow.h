#pragma once

#include <QMainWindow> 

class NodeEditorView;
class QGraphicsScene; 


class MainWindow : public QMainWindow {
    Q_OBJECT

    public: 
        MainWindow(QWidget* parent = nullptr); 
};