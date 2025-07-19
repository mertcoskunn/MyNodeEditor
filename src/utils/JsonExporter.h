#pragma once

#include <QJsonObject>
#include <QJsonArray>
#include <QPointF>
#include <QString>
#include <QFile>
#include <QJsonDocument>

class Node;

class JsonExporter {
public:
    static QJsonObject serializeNode(Node* node);
    static QJsonArray serializeNodeList(const std::vector<Node*>& nodeList);
    static bool saveToFile(const QString& path, const QJsonDocument& doc);

};
