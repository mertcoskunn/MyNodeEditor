#include "DataPin.h"
#include "../ConnectionLine.h"
#include "../Node.h"

DataPin::DataPin(const QString& name, DataType type, VariantType defaultVal, Pin::Direction direction, QGraphicsItem* parent)
    : Pin(Pin::PinType::Data, direction, parent)
{
    pinName = name;
    dataType = type; 
    value = defaultVal;

    if(getDirection() == Direction::Input)
        setupInputBox(); 
}

void DataPin::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*)
{
        painter->setBrush(getPinColorForType(dataType));
        painter->drawEllipse(QPointF(0, 0), 5, 5);
}

QRectF DataPin::boundingRect() const 
{ 
    return QRectF(-5, -5, 10, 10); 
}

QColor DataPin::getPinColorForType(DataType type) const
{
    switch(type)
    {
        case DataType::Integer: return QColor("#e67e22"); 
        case DataType::Float:   return QColor("#2980b9"); 
        case DataType::Boolean: return QColor("#27ae60"); 
        case DataType::String:  return QColor("#8e44ad"); 
    }
    return QColor(Qt::black);
}

void DataPin::setupInputBox()
{
    inputBox = new QLineEdit;
    inputBox->setFixedHeight(15);
    inputBox->setFixedWidth(25);
    inputBox->setPlaceholderText("0.0");
    QFont font = inputBox->font();
    font.setPointSize(8); 
    inputBox->setFont(font);
    inputBox->setText(toQString(value)); 
    
    if(getDataType() == DataType::Float)
    {
        QDoubleValidator* validator = new QDoubleValidator(-999999.0, 999999.0, 4, this);
        validator->setNotation(QDoubleValidator::StandardNotation);
        inputBox->setValidator(validator);
    }
    

    proxy = new QGraphicsProxyWidget(this);
    proxy->setWidget(inputBox);
    proxy->setPos(10, -5); 

    QObject::connect(inputBox, &QLineEdit::textChanged, [=](const QString& val){
        setValue(val.toFloat()); 
        qDebug() << "Yeni değer:" << val;
    });
}

void DataPin::setValue(const VariantType& v){
    qDebug() << "set Value fonksiyonu çalıştı"; 
    isSet = true; 
    value = v;
}


void DataPin::setLine(ConnectionLine* line)
{
    Pin::setLine(line);
    
    if(inputBox){
        if(line == nullptr)
        {
            inputBox->show();
            setValue(inputBox->text().toFloat());  
        }
        else
        {
            inputBox->hide();
        }
    }
        
}


QString DataPin::toQString(const VariantType& value) {
    return std::visit([](auto&& arg) -> QString {
        using T = std::decay_t<decltype(arg)>;

        if constexpr (std::is_same_v<T, QString>) {
            return arg;
        } else if constexpr (std::is_same_v<T, bool>) {
            return arg ? "true" : "false";
        } else {
            return QString::number(arg);  
        }
    }, value);
}

DataPin::VariantType DataPin::getValue(){
   
    qDebug() <<"get Value çalıştı";
    if(!getLine()){
        qDebug() << "line set değil"; 
        return value;
        }
    if(getDirection() == Direction::Output){
        if(isSet){
            qDebug()<<"is set true";
            return value;
        }
        qDebug()<<"direction output";
        getOwner()->execute();
        return value; 
    }
    qDebug()<<"direction input";
    
    
    return dynamic_cast<DataPin*>(getLine()->getStartPin())->getValue();  
}
