#ifndef HONGO_H
#define HONGO_H

#include <QGraphicsItem>
#include <QPixmap>
#include <QPainter>
#include <QObject>

class Hongo: public QObject, public QGraphicsItem
{
    Q_OBJECT
public:

    Hongo(QGraphicsItem *padre = nullptr);
    ~Hongo();

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void siguienteSprite();

private:
    QPixmap sprite;
    int posSprite;
};

#endif // HONGO_H


