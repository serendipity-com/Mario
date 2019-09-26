#include "hongo.h"


Hongo::Hongo(QGraphicsItem *parent): QGraphicsItem(parent)
{
    setFlag(ItemClipsToShape);
    sprite = QPixmap(":images/m40.png");
}

Hongo::~Hongo()
{

}


QRectF Hongo::boundingRect() const {
    return QRectF(0,0,40,40);

}

void Hongo::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->drawPixmap(0,0, sprite, 0, 0, 40, 40);
    setTransformOriginPoint(boundingRect().center());
    Q_UNUSED(widget)
    Q_UNUSED(option)

}

