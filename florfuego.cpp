#include "florfuego.h"

FlorFuego::FlorFuego(QGraphicsItem *padre) : QGraphicsItem(padre)
{
    setFlag(ItemClipsToShape);
    sprite = QPixmap(":/Imagenes/flor.png");
    posSprite = 0;
}

FlorFuego::~FlorFuego()
{

}

QRectF FlorFuego::boundingRect() const
{
    return QRectF(0,0,40,40);
}

void FlorFuego::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(0,0, sprite, posSprite, 0,50, 50);
    setTransformOriginPoint(boundingRect().center());
    Q_UNUSED(widget)
    Q_UNUSED(option)
}

int FlorFuego::type() const
{
    return Type;
}
