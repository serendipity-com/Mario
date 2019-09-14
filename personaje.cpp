#include "personaje.h"

Personaje::Personaje(QGraphicsItem *padre)
{
    estado = quieto;
    setFlag(ItemClipsToShape);
    spriteCaminando = QPixmap(":images/mario.png");
    spriteQuieto = QPixmap(":images/mariostop.png");
    spriteSaltando = QPixmap(":images/mario_jump.png");
    spriteAtacando = QPixmap(":images/mariostop.png");
    sprite = spriteQuieto;

    vidas = 5;
}

Personaje::~Personaje()
{

}

void Personaje::caminar()
{
    if (estado != caminando)
    {
        sprite = spriteCaminando;
        estado = caminando;
    }
}

void Personaje::saltar()
{
    estado = saltando;
}

void Personaje::estarQuieto()
{
    sprite = spriteQuieto;
    estado = quieto;
}

void Personaje::atacar()
{
    sprite = spriteAtacando;
    estado = atacando;
}

QRectF Personaje::boundingRect() const
{
    return QRectF(0,0,45,73);
}

void Personaje::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(0,0, sprite, 0, 0,45, 73);
    setTransformOriginPoint(boundingRect().center());
    Q_UNUSED(widget)
    Q_UNUSED(option)
}
