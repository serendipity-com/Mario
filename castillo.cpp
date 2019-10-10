#include "castillo.h"

Castillo::Castillo(QGraphicsItem *padre) : QGraphicsItem(padre)
{
    setFlag(ItemClipsToShape);
    sprite = QPixmap(":/Imagenes/castillo.png");
}

Castillo::~Castillo()
{

}

QRectF Castillo::boundingRect() const
{
    return QRectF(0,0,40,40);
}

void Castillo::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(0,0, sprite, 0, 0,50, 50);
    setTransformOriginPoint(boundingRect().center());
    Q_UNUSED(widget)
    Q_UNUSED(option)
}

int Castillo::type() const
{
    return Type;
}
