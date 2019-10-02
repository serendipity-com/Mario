#include "goomba.h"

Goomba::Goomba(QGraphicsItem *parent) : QGraphicsItem(parent)
{
    direccion = 1;
    setFlag(ItemClipsToShape);
    sprite = QPixmap(":/Imagenes/goombas.png");
}

int Goomba::getDireccion()
{
    return direccion;
}

void Goomba::setDireccion(int inDireccion)
{
    if(direccion != inDireccion)
    {
        direccion = inDireccion;
        if(direccion != 0)
        {
            QTransform transforma;
            if(direccion == -1)
            {
                transforma.scale(-1,1);
            }
            setTransform(transforma);
        }
    }
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

    return QRectF(0,0,53,50);
}

void Goomba::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(0,0, sprite, posSprite, 0,53, 50);
    setTransformOriginPoint(boundingRect().center());
    Q_UNUSED(widget)
    Q_UNUSED(option)
}

int Goomba::type() const
{
    return Type;
}



