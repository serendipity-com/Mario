#ifndef CASTILLO_H
#define CASTILLO_H

#include <QGraphicsItem>
#include <QPixmap>
#include <QPainter>

class Castillo : public QGraphicsItem
{
public:
    enum{ Type = UserType + 11};
    Castillo(QGraphicsItem *padre = nullptr);
    ~Castillo();

    bool estarTocandoPuerta(QGraphicsItem *item);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    int type() const;
private:
    QPixmap sprite;
};

#endif // CASTILLO_H
