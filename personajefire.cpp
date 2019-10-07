#include "personajefire.h"

PersonajeFire::PersonajeFire(QGraphicsItem *padre) : QGraphicsItem(padre)
  , estado(quieto)
  , direccion(0)
{
    setFlag(ItemClipsToShape);
    spriteCaminando = QPixmap(":/Imagenes/firemario.png");
    spriteQuieto = QPixmap("::/Imagenes/firemariostop.png");
    spriteSaltando = QPixmap(":/Imagenes/firemariostop.png");
    spriteAtacando = QPixmap(":/Imagenes/firemariostop.png");
    sprite = spriteQuieto;

    personaje = new PersonajeFisica(0,720,73,45);
}

PersonajeFire::~PersonajeFire()
{
    delete personaje;
}

void PersonajeFire::caminar()
{
    if (estado != caminando)
    {
        sprite = spriteCaminando;
        posSprite = 0;
        estado = caminando;
    }
}

void PersonajeFire::saltar()
{
    estado = saltando;
}

void PersonajeFire::estarQuieto()
{
    sprite = spriteQuieto;
    estado = quieto;
    posSprite = 0;
}

void PersonajeFire::atacar()
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
int PersonajeFire::getDireccion()
{
    return direccion;
}

void PersonajeFire::setDireccion(int inDireccion)
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

void PersonajeFire::siguienteSprite()
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

//paint()función, que realiza la pintura del elemento actual, y la
//boundingRect()función, que debe devolver el límite del área sobre la paint()que pinta la  función
QRectF PersonajeFire::boundingRect() const
{
    return QRectF(0,0,45,73);
}

void PersonajeFire::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(0,0, sprite, posSprite, 0,45, 73);
    setTransformOriginPoint(boundingRect().center());
    Q_UNUSED(widget)
    Q_UNUSED(option)
}

bool PersonajeFire::estarTocandoCabeza(QGraphicsItem *item)
{
    QRectF rect(pos().x(), pos().y(), boundingRect().width(), 10);
    QRectF otherRect(item->pos().x(), (item->pos().y() +item->boundingRect().height() -10), item->boundingRect().width(), 10);
    return rect.intersects(otherRect);
}

bool PersonajeFire::estarTocandoPies(QGraphicsItem *item)
{
    QRectF rect(pos().x(), (pos().y() + boundingRect().height()) - 10, boundingRect().width(), 10);
    QRectF otherRect(item->pos().x(), item->pos().y(), item->boundingRect().width(), 10);
    return rect.intersects(otherRect);
}

bool PersonajeFire::estarTocandoPlataforma(QGraphicsItem *item)
{
    QRectF rect(pos().x(), (pos().y() + boundingRect().height()) - 10, boundingRect().width(), 10);
    QRectF otherRect(item->pos().x(), item->pos().y(), item->boundingRect().width(), 10);
    return rect.intersects(otherRect);
}

void PersonajeFire::actualizar(int lim)
{
    personaje->actualizar();
    //qDebug() << lim - personaje->getPosY();
    setPos(personaje->getPosX(), lim - personaje->getPosY());
}

PersonajeFisica *PersonajeFire::getFisica()
{
    return personaje;
}
