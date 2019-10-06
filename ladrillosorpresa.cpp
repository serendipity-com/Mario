#include "ladrillosorpresa.h"

LadrilloSorpresa::LadrilloSorpresa(QGraphicsItem *padre) : QGraphicsItem(padre)
{
    setFlag(ItemClipsToShape);
    sprite = QPixmap(":/Imagenes/sorpresa.png");
}

void LadrilloSorpresa::setRegalo(int in)
{
    switch (in)
    {
        case 1: regalo = flor;
            break;
        case 2: regalo = moneda;
            break;
        case 3: regalo = hongo;
            break;
    }
}

int LadrilloSorpresa::getRegalo()
{
    return regalo;
}

void LadrilloSorpresa::siguienteSprite()
{
    //Manejo de Sprites
    //Distancia en caada sprite
    posSprite += 50;
    //Condicion volver al primer sprite, si sobre pasa la dimension la imagen plana
    if(posSprite >= 800)
    {
        posSprite = 0;
    }
}

QRectF LadrilloSorpresa::boundingRect() const
{
    return QRectF(0,0,50,50);
}

void LadrilloSorpresa::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(0,0, sprite, posSprite, 0,50, 50);
    setTransformOriginPoint(boundingRect().center());
    Q_UNUSED(widget)
    Q_UNUSED(option)
}

int LadrilloSorpresa::type() const
{
    return Type;
}
