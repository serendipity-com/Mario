#include "personajefisica.h"

PersonajeFisica::PersonajeFisica(qreal _posX, qreal _posY, qreal _alto, qreal _ancho)
{
    posX = _posX;
    posY = _posY;
    alto = _alto;
    ancho = _ancho;

    a = ancho*alto;
    cd = 5;
    vel = 0;
    velX = 0;
    velY = 0;
    aX = 0;
    aY = 0;
    g = 100;
    m = 500;
    dt = 0.1;
}

void PersonajeFisica::actualizar()
{
    //qDebug() << vel << " " << posX << "" << posY << " " << velX <<" " << velY;
    vel = qPow(qPow(velX,2) + qPow(velY,2), 1/2);
    angulo = qAtan2(velY ,velX);
    aX = -(qPow(vel, 2)*cd*a*qCos(angulo)*(2)) /(2*m);
    aY = -(qPow(vel, 2)*cd*a*qSin(angulo)*(2)) /(2*m) - g;
    posX = posX + (velX*dt) +((aX*dt*dt)/2);
    posY = posY + (velY*dt) +((aY*dt*dt)/2);
    velX = velX + aX*dt;
    velY = velY + aY*dt;
    //qDebug() << vel << " " << posX << "" << posY << " " << velX <<" " << velY;
}

qreal PersonajeFisica::getAlto()
{
    return alto;
}

qreal PersonajeFisica::getAncho()
{
    return ancho;
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
