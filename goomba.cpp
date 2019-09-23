#include "goomba.h"

Goomba::Goomba(QGraphicsItem *parent) : QGraphicsItem(parent)
{
    setFlag(ItemClipsToShape);
    sprite = QPixmap(":images/goombas.png");
}

void Goomba::siguienteSprite()
{
    //Manejo de Sprites
    //Distancia en caada sprite
    posSprite += 54;
    //Condicion volver al primer sprite, si sobre pasa la dimension la imagen plana
    if(posSprite >= 862)
    {
        posSprite = 0;
    }
}


QRectF Goomba::boundingRect() const {

    return QRectF(0,0,52,50);
}

void Goomba::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(0,0, sprite, posSprite, 0,52, 50);
    setTransformOriginPoint(boundingRect().center());
    Q_UNUSED(widget)
    Q_UNUSED(option)
}



