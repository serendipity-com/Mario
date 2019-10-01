#ifndef FLOR_H
#define FLOR_H

#include <QGraphicsItem>
#include <QPixmap>
#include <QPainter>

class Flor: public  QGraphicsItem
{
public:
    enum{ Type = UserType + 7};
    Flor(QGraphicsItem *padre = nullptr);
    ~Flor();
    void siguienteSprite();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    int type() const;
private:
    QPixmap sprite;
    int posSprite;

};

#endif // FLOR_H
