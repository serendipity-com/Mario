#include "niveluno.h"

NivelUno::NivelUno(QObject *padre):
    QGraphicsScene(padre)
  , velocidad(5)
{
    //animacion de salto
    animacionSaltar = new QPropertyAnimation(this);
    animacionSaltar->setTargetObject(this);
    animacionSaltar->setPropertyName("factorSalto");
    animacionSaltar->setStartValue(0);
    animacionSaltar->setKeyValueAt(0.5, 1);
    animacionSaltar->setEndValue(0);
    animacionSaltar->setDuration(800);
    animacionSaltar->setEasingCurve(QEasingCurve::OutInQuint);

    personaje = new Personaje();
    minX = 20;
    maxX = 700;
    nivelTierra = 20;
    timer.setInterval(30);
    connect(&timer, &QTimer::timeout, this, &NivelUno::moverJugador);
}

NivelUno::~NivelUno()
{
    delete personaje;
}

void NivelUno::agregarEntradaHorizontal(int entrada)
{
    entradaHorizontal += entrada;
    personaje->setDireccion(qBound(-1, entradaHorizontal, 1));
    checkTimer();
}
/*Esta función primero verifica si el jugador se mueve.
 *  Si no, el temporizador se detiene, porque nada tiene
 *  que actualizarse cuando nuestro personaje se detiene.
 *  De lo contrario, el temporizador se inicia, pero solo
 *  si aún no se está ejecutando. Verificamos esto llamando
 *  isActive()al temporizador.*/
void NivelUno::checkTimer()
{
    if(personaje->getDireccion() == 0)
    {
        timer.stop();
    }
    else if(!timer.isActive())
    {
        timer.start();
    }
}

void NivelUno::verificarColisiones()
{
    for(QGraphicsItem *item : collidingItems(personaje))
    {
        if(Moneda *m = qgraphicsitem_cast<Moneda>(item))
        {
            delete this;
        }
    }
}

void NivelUno::aplicarParalelismo(qreal propocion, QGraphicsItem *item)
{
    item->setX((item->boundingRect().width() - width()) * -propocion);
}

void NivelUno::saltar()
{
    if(QAbstractAnimation::Stopped == animacionSaltar->state())
    {
        animacionSaltar->start();
    }
}

qreal NivelUno::getFactorSalto() const
{
    return factorSalto;
}

void NivelUno::setFactorSalto(const qreal &pos)
{
    if (pos != factorSalto)
    {
        factorSalto =pos;
        emit cambiarFactorSalto(factorSalto);
    }
    qreal tierraY = (nivelTierra - personaje->boundingRect().width());
    qreal y = tierraY - animacionSaltar->currentValue().toReal() * alturaSalto;
    personaje->setY(y);
}

void NivelUno::moverJugador()
{
    /*A continuación, calculamos el turno que debe obtener el elemento del jugador y
     *  lo almacenamos dx. La distancia que el jugador debe moverse cada 30 milisegundos
     *  está definida por la velocidad variable miembro, expresada en píxeles. */
    const int direccion = personaje->getDireccion();
    if(direccion != 0)
    {
        const int dx = direccion * velocidad;
        qreal newX = qBound(minX, posicionX + dx, maxX);
        if (newX == posicionX)
        {
            return;
        }
        posicionX = newX;
    }

    const int longituCambio = 100;
    const int derechaLongitudCambio = width() - longituCambio;

    const int posicionVisibleJugador = posicionX - desplazamientoMundo;
    const int newMundoDerecha = posicionVisibleJugador - derechaLongitudCambio;

    if (newMundoDerecha > 0)
    {
        desplazamientoMundo += newMundoDerecha;
    }

    const int maxDesplazamientoMundo = anchoEscena - qRound(width());
    desplazamientoMundo = qBound(0, desplazamientoMundo, maxDesplazamientoMundo);
    personaje->setX(posicionX - desplazamientoMundo);

    const qreal proporcion = qreal(desplazamientoMundo) / maxDesplazamientoMundo;
    aplicarParalelismo(proporcion, cielo);
    aplicarParalelismo(proporcion, tierra);
    aplicarParalelismo(proporcion, bloques);
}

void NivelUno::keyPressEvent(QKeyEvent *event)
{
    if (event->isAutoRepeat())
    {
        return;
    }
    switch (event->key())
    {
    case Qt::Key_Right:
        agregarEntradaHorizontal(1);
        break;
    case Qt::Key_Left:
        agregarEntradaHorizontal(1);
        break;
    case Qt::Key_Space:
        saltar();
        break;

    }
}
