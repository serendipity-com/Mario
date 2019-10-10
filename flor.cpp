#include "flor.h"

Flor::Flor(QGraphicsItem *padre)
    : QGraphicsItem(padre)
{
    setFlag(ItemClipsToShape);
    sprite = QPixmap(":/Imagenes/florCar.png");
    posSprite = 0;
}

Flor::~Flor()
{

}

void Flor::siguienteSprite()
{
    //Manejo de Sprites
    //Distancia en caada sprite
    posSprite += 387;
    //Condicion volver al primer sprite, si sobre pasa la dimension la imagen plana
    if(posSprite >= 9286)
    {
        posSprite = 0;
    }
}

QRectF Flor::boundingRect() const
{
    return QRectF(0,0,130,163);
}

void Flor::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(0,0, sprite, posSprite, 0,130, 163);
    setTransformOriginPoint(boundingRect().center());
    Q_UNUSED(widget)
    Q_UNUSED(option)
}

int Flor::type() const
{
    return Type;
}
