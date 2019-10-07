#include "hongo.h"


Hongo::Hongo(QGraphicsItem *parent): QGraphicsItem(parent)
{
    setFlag(ItemClipsToShape);
    sprite = QPixmap(":/Imagenes/hongo.png");

    posX = 0;
    posY = 0;
    a = 40*40;
    cd = 5;
    vel = 0;
    velX = 0;
    velY = 0;
    aX = 0;
    aY = 0;
    g = 100;
    m = 100;
    dt = 0.1;
}

Hongo::~Hongo()
{

}

void Hongo::actualizar(qreal lim)
{
    vel = qPow(qPow(velX,2) + qPow(velY,2), 1/2);
    angulo = qAtan2(velY ,velX);
    aX = -(qPow(vel, 2)*cd*a*qCos(angulo)*(2)) /(2*m);
    aY = -(qPow(vel, 2)*cd*a*qSin(angulo)*(2)) /(2*m) - g;
    posX = posX + (velX*dt) +((aX*dt*dt)/2);
    posY = posY + (velY*dt) +((aY*dt*dt)/2);
    velX = velX + aX*dt;
    velY = velY + aY*dt;
    qDebug() << posX << posY;
    setPos(posX, lim - posY);
}

void Hongo::setVel(qreal _velX, qreal _velY, qreal _posX, qreal _posY)
{
    velX = _velX;
    velY = _velY;
    posX = _posX;
    posY = _posY;
}

qreal Hongo::getPosX()
{
    return posX;
}

qreal Hongo::getPosY()
{
    return posY;
}

qreal Hongo::getVelX()
{
    return velX;
}

qreal Hongo::getVelY()
{
    return velY;
}


QRectF Hongo::boundingRect() const {
    return QRectF(0,0,40,40);

}

void Hongo::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->drawPixmap(0,0, sprite, 0, 0, 40, 40);
    setTransformOriginPoint(boundingRect().center());
    Q_UNUSED(widget)
    Q_UNUSED(option)

}

