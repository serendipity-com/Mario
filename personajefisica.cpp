#include "personajefisica.h"

PersonajeFisica::PersonajeFisica(qreal _posX, qreal _posY)
{
    posX = _posX;
    posY = _posY;

    a = 45*73;
    cd = 0.001;
    vel = 0;
    velX = 0;
    velY = 0;
    aX = 0;
    aY = 0;
    g = 10;
    m = 0;
    dt = 0.1;
}

void PersonajeFisica::actualizar()
{
    vel = qPow(qPow(velX,2) + qPow(velY,2), 1/2);
    angulo = qAtan2(velY ,velX);
    aX = -(qPow(vel, 2)*cd*a*qCos(angulo)) /(2*m);
    aY = -(qPow(vel, 2)*cd*a*qSin(angulo)) /(2*m) - g;
    velX = velX + aX*dt;
    velY = velY + aY*dt;
    posX = posX + (velX*dt) +((aX*dt*dt)/2);
    posY = posY + (velY*dt) +((aY*dt*dt)/2);
    qDebug() << vel << " " << posX << "" << posY << " " << velX <<" " << velY;
}

qreal PersonajeFisica::getPosX()
{
    return posX;
}

qreal PersonajeFisica::getPosY()
{
    return posY;
}

qreal PersonajeFisica::getVelX()
{
    return velX;
}

qreal PersonajeFisica::getVelY()
{
    return velY;
}

void PersonajeFisica::setVel(qreal _velX, qreal _velY, qreal _posX, qreal _posY)
{
    velX = _velX;
    velY = _velY;
    posX = _posX;
    posY = _posY;
}
