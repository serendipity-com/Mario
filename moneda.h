#ifndef MONEDA_H
#define MONEDA_H

#include <QGraphicsItem>
#include <QPixmap>
#include <QPainter>

class Moneda : public QGraphicsItem
{
public:
    enum{ Type = UserType + 3};
    Moneda(QGraphicsItem *padre = nullptr);
    ~Moneda();

    void siguienteSprite();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    int type() const;
private:
    QPixmap sprite;
    int posSprite;
};

#endif // MONEDA_H
