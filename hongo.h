#ifndef HONGO_H
#define HONGO_H

#include <QGraphicsItem>
#include <QPixmap>
#include <QPainter>
#include <QObject>
#include <QtMath>
#include <QDebug>

class Hongo: public QObject, public QGraphicsItem
{
    Q_OBJECT
public:

    Hongo(QGraphicsItem *padre = nullptr);
    ~Hongo();

    void actualizar(qreal lim);
    void setVel(qreal _velX, qreal _velY, qreal _posX, qreal _posY);

    qreal getPosX();
    qreal getPosY();
    qreal getVelX();
    qreal getVelY();

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    QPixmap sprite;

    qreal posX;
    qreal posY;
    qreal velX;
    qreal velY;
    qreal aX;
    qreal aY;
    qreal dt;
    qreal a;
    qreal cd;
    qreal vel;
    qreal g;
    qreal m;
    qreal angulo;
};

#endif // HONGO_H


