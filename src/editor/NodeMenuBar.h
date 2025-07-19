#pragma once

#include <QMenuBar>
#include <QMenu>
#include <QAction>

class NodeMenuBar : public QMenuBar
{
    Q_OBJECT

public:
    explicit NodeMenuBar(QWidget* parent = nullptr);

    QAction* actionOpen;
    QAction* actionSave;

signals:
    void saveRequested();
    void openRequested();
    
};
