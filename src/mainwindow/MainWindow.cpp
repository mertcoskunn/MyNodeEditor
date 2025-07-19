#include "MainWindow.h"
#include "../editor/NodeEditorScene.h"
#include "../editor/NodeEditorView.h"
#include "../editor/NodeMenuBar.h"
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>
#include "../utils/JsonExporter.h"
#include "../utils/JsonImporter.h"
#include "../nodes/Node.h"  
#include "../nodes/nodetypes/PrintNode.h"
#include "../nodes/nodetypes/StartNode.h"
#include "../nodes/nodetypes/ConstantNode.h"
#include "../nodes/nodetypes/BranchNode.h"
#include "../nodes/nodetypes/math/SumNode.h"
#include "../nodes/nodetypes/math/DivisionNode.h"
#include "../nodes/nodetypes/math/MultiplyNode.h"
#include "../nodes/nodetypes/math/SubtractionNode.h"
#include "../nodes/ConnectionLine.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    NodeMenuBar* menu = new NodeMenuBar();
    setMenuBar(menu); 
    scene = new NodeEditorScene();
    view = new NodeEditorView;

    view->setScene(scene);
    setCentralWidget(view);

    connect(menu, &NodeMenuBar::saveRequested, this, &MainWindow::saveFile);
    connect(menu, &NodeMenuBar::openRequested, this, &MainWindow::openFile);

}


void MainWindow::saveFile() {

    if (currentFilePath.isEmpty()) {
        currentFilePath = QFileDialog::getSaveFileName(this, "Save File", "", "JSON Files (*.json)");
        if (currentFilePath.isEmpty()) {
            return; 
        }
    }

    QFile file(currentFilePath);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        
        QJsonArray nodeArray = JsonExporter::serializeNodeList(scene->getNodeList());

        QJsonDocument doc(nodeArray);

        QFileInfo fileInfo(currentFilePath);
        QDir().mkpath(fileInfo.absolutePath());

        if (JsonExporter::saveToFile(currentFilePath, doc)) {
            qDebug() << "Saved!!!!!!!!" << currentFilePath;
        } else {
            qDebug() << "Not Saved!!!!!!!!";
        }

        file.close();
    } else {
        QMessageBox::warning(this, "Save Error", "Sve Error");
    }
}

void MainWindow::openFile() {

     QString filePath = QFileDialog::getOpenFileName(this, "Open File", "", "JSON Files (*.json)");

    if (filePath.isEmpty()) {
        return; 
    }

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Open Error", "Open Error!");
        return;
    }

    
    if (scene) {
        
            scene->clearNodeList();

            QByteArray data = file.readAll();
            file.close();

            QJsonDocument doc = QJsonDocument::fromJson(data);
            if (!doc.isArray()) {
                qWarning() << "Not JSON File";
                return;
            }

            QList<QVariantMap> nodes = JsonImporter::deserializeNodeList(doc.array());
            for (const QVariantMap& node : nodes) {
                QVariantMap pos = node["position"].toMap();
                if(node["name"].toString() == "Start"){
                    StartNode* node = new StartNode();
                    node->setPos(QPointF(pos["x"].toDouble(), pos["y"].toDouble())); 
                    scene->setStartNode(node); 
                    scene->addItem(node);
                    scene->nodeList.push_back(node);

                }

                if(node["name"].toString() == "Division"){
                    DivisionNode* node = new DivisionNode();
                    node->setPos(QPointF(pos["x"].toDouble(), pos["y"].toDouble())); 
                    scene->addItem(node);
                    scene->nodeList.push_back(node);

                }

                if(node["name"].toString() == "Multiply"){
                    MultiplyNode* node = new MultiplyNode();
                    node->setPos(QPointF(pos["x"].toDouble(), pos["y"].toDouble())); 
                    scene->addItem(node);
                    scene->nodeList.push_back(node);
                    
                }

                if(node["name"].toString() == "Branch"){
                    BranchNode* node = new BranchNode();
                    node->setPos(QPointF(pos["x"].toDouble(), pos["y"].toDouble())); 
                    scene->addItem(node);
                    scene->nodeList.push_back(node);
                    
                }

            }
            qDebug() << scene->nodeList.size();
            
            for (const QVariantMap& node : nodes) {
                QVariantList   connectionArray = node["connections"].toList();
                for (const QVariant& val : connectionArray) {
                   QString connectionString = val.toString();
                   QStringList connectionParts = connectionString.split('_');
                   int startNodeId = connectionParts[0].toInt();
                   int starPinNumber = connectionParts[1].toInt();
                   int endNodeId = connectionParts[2].toInt();
                   int endPinNumber = connectionParts[3].toInt();

                   if(scene->getNodeList()[startNodeId]->getOutputPins()[starPinNumber])
                        

                    if(scene->getNodeList()[endNodeId]->getOutputPins()[endPinNumber])
                        
                    qDebug() << scene->getNodeList().size();
                    qDebug() << scene->getNodeList()[startNodeId]->getOutputPins().size();

                   ConnectionLine* line = new ConnectionLine(scene->getNodeList()[startNodeId]->getOutputPins()[starPinNumber], scene->getNodeList()[endNodeId]->getInputPins()[endPinNumber]);
                   scene->getNodeList()[startNodeId]->getOutputPins()[starPinNumber]->setLine(line);
                   scene->getNodeList()[endNodeId]->getInputPins()[endPinNumber]->setLine(line);
                   scene->addItem(line);
                }  
            }
        
        
        
    }
    

    
    currentFilePath = filePath;


}
