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

    void setRegalo(int in);
    int getRegalo();

    void siguienteSprite();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    int type() const;

private:
    enum Regalo
    {
        flor = 1,
        moneda = 2,
        hongo = 3
    };

    Regalo regalo;
    QPixmap sprite;
    int posSprite;
};

#endif // LADRILLOSORPRESA_H
