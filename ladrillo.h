#ifndef LADRILLO_H
#define LADRILLO_H

#include <QGraphicsItem>
#include <QPainter>
#include <QPixmap>

class Ladrillo : public QGraphicsItem
{
public:
    enum{ Type = UserType + 5};
    Ladrillo(QGraphicsItem *padre = nullptr);
    ~Ladrillo();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    int type() const;
private:
    QPixmap sprite;
    int posSprite;
};

#endif // LADRILLO_H
