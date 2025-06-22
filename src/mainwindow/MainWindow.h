#pragma once

#include <QMainWindow>

class QGraphicsScene;
class QGraphicsView; 

class MainWindow : public QMainWindow {
    Q_OBJECT


    public:
        MainWindow(QWidget* parent = nullptr);
};