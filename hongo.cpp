#include "hongo.h"


Hongo::Hongo(QGraphicsItem *parent): QGraphicsItem(parent)
{
    setFlag(ItemClipsToShape);
    sprite = QPixmap(":images/m40.png");
}

Hongo::~Hongo()
{

}

void Hongo::siguienteSprite()
{

}

QRectF Hongo::boundingRect() const {
    return QRectF(0,0,70,50);

}

void Hongo::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->drawPixmap(0,0, sprite, posSprite, 0,70, 50);
    setTransformOriginPoint(boundingRect().center());
    Q_UNUSED(widget)
    Q_UNUSED(option)

}

