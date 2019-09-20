#ifndef GOOMBA_H
#define GOOMBA_H

#include <QGraphicsItem>
#include <QPixmap>
#include <QPainter>

class Goomba: public QGraphicsItem
{
public:
    Goomba(QGraphicsItem *padre);
    void siguienteSprite();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    QPixmap sprite;
    int posSprite;
};

#endif // GOOMBA_H
