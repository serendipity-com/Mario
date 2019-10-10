#ifndef BANDERA_H
#define BANDERA_H

#include <QGraphicsItem>
#include <QPixmap>
#include <QPainter>

class Bandera : public QGraphicsItem
{
public:
    enum{ Type = UserType + 10};
    Bandera(QGraphicsItem *padre = nullptr);
    ~Bandera();

    void siguienteSprite();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    int type() const;
private:
    QPixmap sprite;
    int posSprite;
};

#endif // BANDERA_H
