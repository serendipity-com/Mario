#include "personaje.h"

//En el constructor, establecemos direccion  a 0, lo que significa que Jugador no se mueve en absoluto.
//Si direccion es 1, Personje se mueve hacia la derecha, y si el valor es -1, se mueve hacia la izquierda.
Personaje::Personaje(int tipo, QGraphicsItem *padre) : QGraphicsItem(padre)
  , estado(quieto)
  , direccion(0)
{
    setFlag(ItemClipsToShape);
    if(tipo == 1)
    {
        spriteCaminando = QPixmap(":Imagenes/mario.png");
        spriteQuieto = QPixmap(":Imagenes/mariostop.png");
        spriteSaltando = QPixmap(":Imagenes/mario_jump.png");
        spriteAtacando = QPixmap(":Imagenes/mariostop.png");
        ancho = 45;
        alto = 73;
    }
    else if(tipo == 2)
    {
        spriteCaminando = QPixmap(":/Imagenes/mario_small.png");
        spriteQuieto = QPixmap(":/Imagenes/smallMarioStop.png");
        spriteSaltando = QPixmap(":/Imagenes/smallMarioStop.png");
        spriteAtacando = QPixmap(":/Imagenes/smallMarioStop.png");
        ancho = 45;
        alto = 45;
    }
    else if(tipo == 3)
    {
        spriteCaminando = QPixmap(":/Imagenes/firemario.png");
        spriteQuieto = QPixmap(":/Imagenes/firemariostop.png");
        spriteSaltando = QPixmap(":/Imagenes/firemariostop.png");
        spriteAtacando = QPixmap(":/Imagenes/firemariostop.png");
        ancho = 45;
        alto = 73;
    }

    sprite = spriteQuieto;
    personaje = new PersonajeFisica(0,720,alto,ancho);
}

Personaje::~Personaje()
{
    delete personaje;
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

//La getDireccion()función es una función getter estándar para direccion devolver su valor.
//La setDirection()función setter además verifica en qué dirección se mueve el Personaje.
//Si se está moviendo hacia la izquierda, debemos voltear su imagen para que Benjamin mire
//hacia la izquierda, la dirección en la que se está moviendo. Si se mueve hacia la derecha,
//restauramos el estado normal al asignar un QTransformobjeto vacío , que es una matriz de identidad.
int Personaje::getDireccion()
{
    return direccion;
}

void Personaje::setDireccion(int inDireccion)
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

//paint()función, que realiza la pintura del elemento actual, y la
//boundingRect()función, que debe devolver el límite del área sobre la paint()que pinta la  función
QRectF Personaje::boundingRect() const
{
    return QRectF(0,0,ancho,alto);
}

void Personaje::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(0,0, sprite, posSprite, 0,ancho, alto);
    setTransformOriginPoint(boundingRect().center());
    Q_UNUSED(widget)
    Q_UNUSED(option)
}

bool Personaje::estarTocandoL(QGraphicsItem *item)
{
    QRectF rect(pos().x(), pos().y(), boundingRect().width(), boundingRect().height());
    QRectF otherRect(item->pos().x(), item->pos().y() , 10, item->boundingRect().height());
    return rect.intersects(otherRect);
}

bool Personaje::estarTocandoR(QGraphicsItem *item)
{
    QRectF rect(pos().x(), pos().y(), boundingRect().width(), boundingRect().height());
    QRectF otherRect(item->pos().x() + item->boundingRect().width() -10 , item->pos().y() , 10 , item->boundingRect().height());
    return rect.intersects(otherRect);
}

bool Personaje::estarTocandoCabeza(QGraphicsItem *item)
{
    QRectF rect(pos().x(), pos().y(), boundingRect().width(), 10);
    QRectF otherRect(item->pos().x(), (item->pos().y() +item->boundingRect().height() -10), item->boundingRect().width(), 10);
    return rect.intersects(otherRect);
}

bool Personaje::estarTocandoPies(QGraphicsItem *item)
{
    QRectF rect(pos().x(), (pos().y() + boundingRect().height()) -10, boundingRect().width(), 10);
    QRectF otherRect(item->pos().x(), item->pos().y(), item->boundingRect().width(), 10);
    return rect.intersects(otherRect);
}

bool Personaje::estarTocandoPlataforma(QGraphicsItem *item)
{
    QRectF rect(pos().x(), (pos().y() + boundingRect().height()) - 10, boundingRect().width(), 10);
    QRectF otherRect(item->pos().x(), item->pos().y(), item->boundingRect().width(), 10);
    return rect.intersects(otherRect);
}

void Personaje::actualizar(int lim)
{
    personaje->actualizar();
    //qDebug() << lim - personaje->getPosY();
    setPos(personaje->getPosX(), lim - personaje->getPosY());
}

PersonajeFisica *Personaje::getFisica()
{
    return personaje;
}
