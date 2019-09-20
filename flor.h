#ifndef FLOR_H
#define FLOR_H

#include <QGraphicsItem>
#include <QPixmap>
#include <QPainter>

class Flor: public  QGraphicsItem
{
public:
    Flor(QGraphicsItem *padre = nullptr);

    void siguienteSprite();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    QPixmap sprite;
    int posSprite;

};

#endif // FLOR_H
