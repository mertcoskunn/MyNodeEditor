#pragma once

#include <QMainWindow>
#include <QString> 

class NodeEditorScene;
class NodeEditorView; 

class MainWindow : public QMainWindow {
    Q_OBJECT


public:
        MainWindow(QWidget* parent = nullptr);

private slots:
    void saveFile();
    void openFile();

private: 
    QString currentFilePath;
    NodeEditorScene* scene;
    NodeEditorView* view;
};