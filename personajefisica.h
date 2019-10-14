#ifndef PERSONAJEFISICA_H
#define PERSONAJEFISICA_H

#include <QtMath>
#include <QDebug>

class PersonajeFisica
{
public:
    PersonajeFisica(qreal _posX, qreal _posY, qreal _alto, qreal _ancho);

    void actualizar();

    qreal getAlto();
    qreal getAncho();
    qreal getPosX();
    qreal getPosY();
    qreal getVelX();
    qreal getVelY();
    qreal getVel();

    void setVel(qreal _velX, qreal _velY, qreal _posX, qreal _posY);
    void setCd(qreal _cd);

private:
    qreal alto;
    qreal ancho;
    qreal posX;
    qreal posY;
    qreal velX;
    qreal velY;
    qreal vel;
    qreal aX;
    qreal aY;
    qreal angulo;
    qreal cd;
    qreal a;
    qreal g;
    qreal m;
    qreal dt;
};

#endif // PERSONAJEFISICA_H
