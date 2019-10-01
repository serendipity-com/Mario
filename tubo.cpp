#include "tubo.h"

Tubo::Tubo(QGraphicsItem *padre) : QGraphicsItem(padre)
{
    setFlag(ItemClipsToShape);
    sprite = QPixmap(":/Imagenes/tubo.png");
    posSprite = 0;
}

Tubo::~Tubo()
{

}

QRectF Tubo::boundingRect() const
{
    return QRectF(0,0,70,100);
}

void Tubo::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(0,0, sprite, posSprite, 0,70, 100);
    setTransformOriginPoint(boundingRect().center());
    Q_UNUSED(widget)
    Q_UNUSED(option)
}

int Tubo::type() const
{
    return Type;
}
