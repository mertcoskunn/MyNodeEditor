#pragma once 
#include "../Pin.h"
#include "../../core/DataType.h"
#include <QGraphicsItem>
#include <QPainter>
#include <QRectF>
#include <QStyleOptionGraphicsItem>
#include <variant>
#include <QLineEdit>
#include <QCheckBox>
#include <QGraphicsProxyWidget>

class DataPin : public Pin
{
public :
    using VariantType = std::variant<int, float, bool, QString>;
    
    DataPin(QString name, DataType type, VariantType defaultVal, Pin::Direction direction, QGraphicsItem* parent = nullptr);
    
    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*) override; 
    VariantType getValue();
    DataType getDataType(){ return dataType; };
    QColor getPinColorForType(DataType type) const;
    void setValue(const VariantType& v);
    void setLine(ConnectionLine* line) override;
     
private:
    DataType dataType;
    VariantType value;
    void setupInputBox();
    QString toQString(const VariantType& value);
    QWidget* inputWidget = nullptr;
    QGraphicsProxyWidget* proxy = nullptr;
    
    
};