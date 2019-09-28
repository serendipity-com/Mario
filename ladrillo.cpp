#include "ladrillo.h"

Ladrillo::Ladrillo(QGraphicsItem *padre) : QGraphicsItem(padre)
{
    setFlag(ItemClipsToShape);
    sprite = QPixmap(":/Imagenes/ladrillo.png");
    posSprite = 0;
}

QRectF Ladrillo::boundingRect() const
{
    return QRectF(0,0,48,50);
}

void Ladrillo::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(0,0, sprite, posSprite, 0,50, 50);
    setTransformOriginPoint(boundingRect().center());
    Q_UNUSED(widget)
    Q_UNUSED(option)
}

int Ladrillo::type() const
{
    return Type;
}

