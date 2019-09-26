#ifndef LADRILLOSORPRESA_H
#define LADRILLOSORPRESA_H

#include <QGraphicsItem>
#include <QPixmap>
#include <QPainter>

class LadrilloSorpresa : public QGraphicsItem
{
public:

    enum{ Type = UserType + 4};
    LadrilloSorpresa(QGraphicsItem *padre = nullptr);

    void siguienteSprite();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    int type() const;
private:
    QPixmap sprite;
    int posSprite;
};

#endif // LADRILLOSORPRESA_H
