#include "castillo.h"

Castillo::Castillo(QGraphicsItem *padre) : QGraphicsItem(padre)
{
    setFlag(ItemClipsToShape);
    sprite = QPixmap(":/Imagenes/castillo.png");
}

Castillo::~Castillo()
{

}

bool Castillo::estarTocandoPuerta(QGraphicsItem *item)
{
    QRectF rect(pos().x() + 84, pos().y() + 204, 114, 190);
    QRectF otherRect(item->pos().x(), item->pos().y(), item->boundingRect().width(),item->boundingRect().height());
    return rect.intersects(otherRect);
}

QRectF Castillo::boundingRect() const
{
    return QRectF(0,0,365,396);
}

void Castillo::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(0,0, sprite, 0, 0,365, 396);
    setTransformOriginPoint(boundingRect().center());
    Q_UNUSED(widget)
    Q_UNUSED(option)
}

int Castillo::type() const
{
    return Type;
}
