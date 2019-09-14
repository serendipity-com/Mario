#ifndef PERSONAJE_H
#define PERSONAJE_H

#include <QPainter>
#include <QPixmap>

class Personaje
{
public:
    Personaje();

    void setMoviendoR();
    void setMoviendoL();
    void setSaltando();
    void setQuieto();
    void setAtacando();
    void setVidas();

    bool getMoviendoR();
    bool getMoviendoL();
    bool getSaltando();
    bool getQuieto();
    bool getAtacando();
    int getVidas();

private:
    bool moviendoR;
    bool moviendoL;
    bool saltando;
    bool quieto;
    bool atacando;

    QPixmap spriteR;
    QPixmap spriteL;
    QPixmap spriteSaltando;
    QPixmap spriteQuieto;

    int vidas;

    int posicionX;
    int posicionY;
};

#endif // PERSONAJE_H
