#include "fantasma.h"

Fantasma::Fantasma(QGraphicsItem *padre) : QGraphicsItem(padre)
{
    setFlag(ItemClipsToShape);
    sprite = QPixmap(":/Imagenes/fantasma.png");
    posSprite = 0;
}

Fantasma::~Fantasma()
{

}

bool Fantasma::estarTocandoFantasma(QGraphicsItem *item)
{
    QRectF rect(pos().x(), pos().y(), boundingRect().width(), altura);
    QRectF otherRect(item->pos().x(), item->pos().y(), item->boundingRect().width(), item->boundingRect().height());
    return rect.intersects(otherRect);
}

void Fantasma::siguienteSprite()
{
    //Manejo de Sprites
    //Distancia en caada sprite
    posSprite += 141;
    //Condicion volver al primer sprite, si sobre pasa la dimension la imagen plana
    if(posSprite >= 8180)
    {
        posSprite = 0;
    }

    altura += 6;
    if(altura >= 112)
    {
        altura = 0;
    }
}

QRectF Fantasma::boundingRect() const
{
    return QRectF(0,0,135,112);
}

void Fantasma::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(0,0, sprite, posSprite, 0,135, 112);
    setTransformOriginPoint(boundingRect().center());
    Q_UNUSED(widget)
    Q_UNUSED(option)
}

int Fantasma::type() const
{
    return Type;
}
