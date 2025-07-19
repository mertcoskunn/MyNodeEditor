#include "JsonImporter.h"

QList<QVariantMap> JsonImporter::deserializeNodeList(const QJsonArray& array) {
    QList<QVariantMap> nodeList;
    for (const QJsonValue& val : array) {
        if (!val.isObject())
            continue;
        QVariantMap nodeData = parseNodeJson(val.toObject());
        nodeList.append(nodeData);
    }
    return nodeList;
}

QVariantMap JsonImporter::parseNodeJson(const QJsonObject& obj) {
    QVariantMap nodeData;

    if (obj.contains("name"))
        nodeData["name"] = obj["name"].toString();

    if (obj.contains("id"))
        nodeData["id"] = obj["id"].toString();

    if (obj.contains("position")) {
        QJsonObject posObj = obj["position"].toObject();
        QVariantMap posMap;
        posMap["x"] = posObj["x"].toDouble();
        posMap["y"] = posObj["y"].toDouble();
        nodeData["position"] = posMap;
    }

    if (obj.contains("pins")) {
        QJsonArray pinsArray = obj["pins"].toArray();
        QVariantList pinsList;
        for (const QJsonValue& pinVal : pinsArray) {
            pinsList.append(pinVal.toString());
        }
        nodeData["pins"] = pinsList;
    }

    if (obj.contains("connections")) {
        QJsonArray connArray = obj["connections"].toArray();
        QVariantList connList;
        for (const QJsonValue& connVal : connArray) {
            connList.append(connVal.toString());
        }
        nodeData["connections"] = connList;
    }

    return nodeData;
}
