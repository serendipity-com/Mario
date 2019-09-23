#include "moneda.h"

Moneda::Moneda(QGraphicsItem *padre)
    : QGraphicsItem(padre)
{
    setFlag(ItemClipsToShape);
    sprite = QPixmap(":images/coin.png");
}


void Moneda::siguienteSprite()
{
    //Manejo de Sprites
    //Distancia en caada sprite
    posSprite += 38;
    //Condicion volver al primer sprite, si sobre pasa la dimension la imagen plana
    if(posSprite >= 300)
    {
        posSprite = 0;
    }
}

QRectF Moneda::boundingRect() const
{
    return QRectF(0,0,39,41);
}

void Moneda::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(0,0, sprite, posSprite, 0,39, 41);
    setTransformOriginPoint(boundingRect().center());
    Q_UNUSED(widget)
    Q_UNUSED(option)
}

