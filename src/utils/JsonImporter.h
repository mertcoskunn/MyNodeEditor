#pragma once

#include <QJsonArray>
#include <QJsonObject>
#include <QVariantMap>
#include <QList>

class JsonImporter {
public:
    static QList<QVariantMap> deserializeNodeList(const QJsonArray& array);

    static QVariantMap parseNodeJson(const QJsonObject& obj);
};
