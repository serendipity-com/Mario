#ifndef TUBO_H
#define TUBO_H

#include <QGraphicsItem>
#include <QPixmap>
#include <QPainter>

class Tubo : public QGraphicsItem
{
public:
    enum{ Type = UserType + 6};
    Tubo(QGraphicsItem *padre = nullptr);
    ~Tubo();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    int type() const;
private:
    QPixmap sprite;
    int posSprite;
};

#endif // TUBO_H
