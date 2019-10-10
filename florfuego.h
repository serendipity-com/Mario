#ifndef FLORFUEGO_H
#define FLORFUEGO_H

#include <QGraphicsItem>
#include <QPainter>
#include <QPixmap>

class FlorFuego : public QGraphicsItem
{
public:
    enum{ Type = UserType + 9};
    FlorFuego(QGraphicsItem *padre = nullptr);
    ~FlorFuego();

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    int type() const;

private:
    QPixmap sprite;
    int posSprite;
    int longitud;
};

#endif // FLORFUEGO_H
