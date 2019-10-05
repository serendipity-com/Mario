#include "ladrillo.h"

Ladrillo::Ladrillo(int _longitud, QGraphicsItem *padre) : QGraphicsItem(padre)
  , longitud(_longitud)
{
    setFlag(ItemClipsToShape);
    sprite = QPixmap(":/Imagenes/ladrillo.png");
    posSprite = 0;
}

Ladrillo::~Ladrillo()
{

}

QRectF Ladrillo::boundingRect() const
{
    return QRectF(0,0,50*longitud,50);
}

void Ladrillo::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    for(int i = 0; i < 50*longitud; i++)
    {
        painter->drawPixmap(i*50,0, sprite, posSprite, 0,50, 50);
    }
    setTransformOriginPoint(boundingRect().center());
    Q_UNUSED(widget)
    Q_UNUSED(option)
}

int Ladrillo::type() const
{
    return Type;
}

