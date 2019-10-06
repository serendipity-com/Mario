#include "personajesmall.h"

PersonajeSmall::PersonajeSmall(QGraphicsItem *padre) : QGraphicsItem(padre)
  , estado(quieto)
  , direccion(0)
{
    setFlag(ItemClipsToShape);
    spriteCaminando = QPixmap(":/Imagenes/mario_small.png");
    spriteQuieto = QPixmap(":/Imagenes/smallMarioStop.png");
    spriteSaltando = QPixmap(":/Imagenes/smallMarioStop.png");
    spriteAtacando = QPixmap(":/Imagenes/smallMarioStop.png");
    sprite = spriteQuieto;

    personaje = new PersonajeFisica(0,720, 45,45);
}

PersonajeSmall::~PersonajeSmall()
{
    delete personaje;
}

void PersonajeSmall::caminar()
{
    if (estado != caminando)
    {
        sprite = spriteCaminando;
        posSprite = 0;
        estado = caminando;
    }
}

void PersonajeSmall::saltar()
{
    estado = saltando;
}

void PersonajeSmall::estarQuieto()
{
    sprite = spriteQuieto;
    estado = quieto;
    posSprite = 0;
}

void PersonajeSmall::atacar()
{
    sprite = spriteAtacando;
    estado = atacando;
    posSprite = 0;
}

//La getDireccion()función es una función getter estándar para direccion devolver su valor.
//La setDirection()función setter además verifica en qué dirección se mueve el Personaje.
//Si se está moviendo hacia la izquierda, debemos voltear su imagen para que Benjamin mire
//hacia la izquierda, la dirección en la que se está moviendo. Si se mueve hacia la derecha,
//restauramos el estado normal al asignar un QTransformobjeto vacío , que es una matriz de identidad.
int PersonajeSmall::getDireccion()
{
    return direccion;
}

void PersonajeSmall::setDireccion(int inDireccion)
{
    if(direccion != inDireccion)
    {
        direccion = inDireccion;
        if(direccion != 0)
        {
            QTransform transforma;
            if(direccion == -1)
            {
                transforma.scale(-1,1);
            }
            setTransform(transforma);
        }
    }
}

void PersonajeSmall::siguienteSprite()
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

QRectF PersonajeSmall::boundingRect() const
{
    return QRectF(0,0,45,45);
}

void PersonajeSmall::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(0,0, sprite, posSprite, 0,45, 45);
    setTransformOriginPoint(boundingRect().center());
    Q_UNUSED(widget)
    Q_UNUSED(option)
}

bool PersonajeSmall::estarTocandoCabeza(QGraphicsItem *item)
{
    QRectF rect(pos().x(), pos().y(), boundingRect().width(), 10);
    QRectF otherRect(item->pos().x(), (item->pos().y() +item->boundingRect().height() -10), item->boundingRect().width(), 10);
    return rect.intersects(otherRect);
}

bool PersonajeSmall::estarTocandoPies(QGraphicsItem *item)
{
    QRectF rect(pos().x(), (pos().y() + boundingRect().height()) -10, boundingRect().width(), 10);
    QRectF otherRect(item->pos().x(), item->pos().y(), item->boundingRect().width(), 10);
    return rect.intersects(otherRect);
}

bool PersonajeSmall::estarTocandoPlataforma(QGraphicsItem *item)
{
    QRectF rect(pos().x(), (pos().y() + boundingRect().height()) - 10, boundingRect().width(), 10);
    QRectF otherRect(item->pos().x(), item->pos().y(), item->boundingRect().width(), 10);
    return rect.intersects(otherRect);
}

void PersonajeSmall::actualizar(int lim)
{
    personaje->actualizar();
    //qDebug() << lim - personaje->getPosY();
    setPos(personaje->getPosX(), lim - personaje->getPosY());
}

PersonajeFisica *PersonajeSmall::getFisica()
{
    return personaje;
}
