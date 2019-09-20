#ifndef MONEDA_H
#define MONEDA_H

#include <QGraphicsItem>
#include <QPixmap>
#include <QPainter>

class Moneda : public QGraphicsItem
{
public:
    Moneda(QGraphicsItem *padre = nullptr);
    void siguienteSprite();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    QPixmap sprite;
    int posSprite;
};

#endif // MONEDA_H
