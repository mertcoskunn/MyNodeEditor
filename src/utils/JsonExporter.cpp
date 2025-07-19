#include "JsonExporter.h"
#include "../nodes/Node.h"
#include "../nodes/Pin.h"
#include "../nodes/ConnectionLine.h"
#include <QJsonDocument>
#include <QFile>
#include <QTextStream>
#include <QDebug>

QJsonObject JsonExporter::serializeNode(Node* node) {
    QJsonObject nodeObject;
    nodeObject["name"] = node->getNodeName();
    nodeObject["id"] = node->getId();

    QPointF pos = node->getPosition();
    QJsonObject position;
    position["x"] = pos.x();
    position["y"] = pos.y();
    nodeObject["position"] = position;

    QJsonArray pinIds;
    for (Pin* pin : node->getAllPins()) {
        pinIds.append(pin->getId());
    }
    nodeObject["pins"] = pinIds;
    
    QJsonArray pinConnections;
    for (Pin* pin : node->getOutputPins()) {
        if(pin->getLine())
        {
            QString inputPinId = pin->getId();
            QStringList inputParts = inputPinId.split('_');
            QString inputPinNumber = inputParts.last();

            QString outputPinId = pin->getLine()->getNextPin()->getId();
            QStringList outputParts = outputPinId.split('_');
            QString outputPinNumber = outputParts.last();

            QString connection = QString("%1_%2_%3_%4").arg(node->getId()).arg(inputPinNumber).arg(pin->getLine()->getNextPin()->getOwner()->getId()).arg(outputPinNumber);
            pinConnections.append(connection);
        }
    }
    nodeObject["connections"] = pinConnections; 

    return nodeObject;
}

QJsonArray JsonExporter::serializeNodeList(const std::vector<Node*>& nodeList) {
    QJsonArray array;
    for (Node* node : nodeList) {
        array.append(serializeNode(node));
    }
    return array;
}

bool JsonExporter::saveToFile(const QString& filePath, const QJsonDocument& doc) {
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qWarning() << "JSON dosyası açılamadı:" << file.errorString();
        return false;
    }

    QTextStream out(&file);
    out << doc.toJson(QJsonDocument::Indented);
    file.close();
    return true;
}