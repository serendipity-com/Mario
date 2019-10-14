#include "bandera.h"

Bandera::Bandera(QGraphicsItem *padre) : QGraphicsItem(padre)
{
    setFlag(ItemClipsToShape);
    sprite = QPixmap(":/Imagenes/bandera.png");
    posSprite = 0;
}

Bandera::~Bandera()
{

}

void Bandera::siguienteSprite()
{
    //Manejo de Sprites
    //Distancia en caada sprite
    posSprite += 322;
    //Condicion volver al primer sprite, si sobre pasa la dimension la imagen plana
    if(posSprite >= 5439)
    {
        posSprite = 0;
    }
}

QRectF Bandera::boundingRect() const
{
    return QRectF(0,0,115,84);
}

void Bandera::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(0,0, sprite, posSprite, 0,115, 84);
    setTransformOriginPoint(boundingRect().center());
    Q_UNUSED(widget)
    Q_UNUSED(option)
}

int Bandera::type() const
{
    return Type;
}
