#include "DataPin.h"
#include "../ConnectionLine.h"
#include "../Node.h"

DataPin::DataPin(QString name, DataType type, VariantType defaultVal, Pin::Direction direction, QGraphicsItem* parent)
    : Pin(name, Pin::PinType::Data, direction, parent)
{
    
    dataType = type; 
    value = defaultVal;

    if(getDirection() == Direction::Input){
        setupInputBox();
        QPointF pos;
        pos.setX(proxy->pos().x() + inputWidget->width() + 3);
        pos.setY(proxy->pos().y() - 5);
        QGraphicsTextItem* label = drawPinName();
        label->setPos(pos);
    }else{
        QGraphicsTextItem* label = drawPinName();
        QPointF pos;
        pos.setX(this->boundingRect().x() -  label->boundingRect().width());
        pos.setY(this->boundingRect().y() - this->boundingRect().height()/2);
        label->setPos(pos);
    }


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
    if (getDataType() == DataType::Boolean)
    {
        QCheckBox* checkBox = new QCheckBox;
        checkBox->setChecked(std::get<bool>(value));
        checkBox->setFixedSize(15, 15);

        proxy = new QGraphicsProxyWidget(this);
        proxy->setWidget(checkBox);
        proxy->setPos(10, -5);
        inputWidget = checkBox;
        QObject::connect(checkBox, &QCheckBox::stateChanged, this, [=](int state){
            setValue(state == Qt::Checked);
            qDebug() << "Yeni bool değer:" << (state == Qt::Checked);
        });
    }else{
    QLineEdit* inputBox = new QLineEdit;
    inputBox->setFixedHeight(15);
    inputBox->setFixedWidth(25);
    inputBox->setPlaceholderText("0.0");
    QFont font = inputBox->font();
    font.setPointSize(8); 
    inputBox->setFont(font);
    inputBox->setText(toQString(value));
    
    inputWidget = inputBox;
    
    
    if(getDataType() == DataType::Float)
    {
        QDoubleValidator* validator = new QDoubleValidator(-999999.0, 999999.0, 4, this);
        validator->setNotation(QDoubleValidator::StandardNotation);
        inputBox->setValidator(validator);
    }

    proxy = new QGraphicsProxyWidget(this);
    proxy->setWidget(inputBox);
    proxy->setPos(10, -5);
    
    QGraphicsTextItem* label = new QGraphicsTextItem(getName(), this);
    label->setFlag(QGraphicsItem::ItemIgnoresTransformations, false);
    label->setDefaultTextColor(Qt::white);
    label->setPos(proxy->pos().x() + inputBox->width() + 3, proxy->pos().y() - 5 );
    
    QObject::connect(inputBox, &QLineEdit::textChanged, [=](const QString& val){
        setValue(val.toFloat()); 
        qDebug() << "Yeni değer:" << val;
    });
}
}



void DataPin::setValue(const VariantType& v){
    value = v;

    if(getDirection() == Direction::Input)
        getOwner()->setDirty(true);
}


void DataPin::setLine(ConnectionLine* line)
{
    Pin::setLine(line);
    
    if(QLineEdit* inputBox = qobject_cast<QLineEdit*>(inputWidget)){
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
        if(!getOwner()->isDirty()){
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
