#include "personaje.h"

Personaje::Personaje(QGraphicsItem *padre) : QGraphicsItem(padre)
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
        posSprite = 0;
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
    posSprite = 0;
}

void Personaje::atacar()
{
    sprite = spriteAtacando;
    estado = atacando;
    posSprite = 0;
}

void Personaje::siguienteSprite()
{
    //Manejo de Sprites
    //Distancia en caada sprite
    posSprite += 57;
    //Condicion volver al primer sprite, si sobre pasa la dimension la imagen plana
    if(posSprite >= 1191)
    {
        posSprite = 0;
    }
}

QRectF Personaje::boundingRect() const
{
    return QRectF(0,0,45,73);
}

void Personaje::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(0,0, sprite, posSprite, 0,45, 73);
    setTransformOriginPoint(boundingRect().center());
    Q_UNUSED(widget)
    Q_UNUSED(option)
}
