#ifndef GOOMBA_H
#define GOOMBA_H


class Goomba
{
public:
    Goomba();
    getSprite();
    moverR();
    moverL();
    setPosicion();
    getPosicion();
private:
    sprite;
    bool moviendoR;
    bool moviendoL;
    posicionX;
    posicionY;
};

#endif // GOOMBA_H
