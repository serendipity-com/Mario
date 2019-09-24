#include "niveluno.h"

NivelUno::NivelUno(QObject *padre):
    QGraphicsScene(0,0,8000,720,padre)
  , anchoEscena(8000)
  , personaje(nullptr)
  , cielo(nullptr)
  , tierra(nullptr)
  , nivelTierra(660)
  , alturaSalto(200)
  , animacionSaltar(new QPropertyAnimation(this))
  , velocidad(7)
  , entradaHorizontal(0)
  , moneda(nullptr)
{
    iniciarEscena();

    timer.setInterval(20);
    connect(&timer, &QTimer::timeout, this, &NivelUno::moverJugador);

    //animacion de salto
    animacionSaltar = new QPropertyAnimation(this);
    animacionSaltar->setTargetObject(this);
    animacionSaltar->setPropertyName("getFactorSalto");
    animacionSaltar->setStartValue(0);
    animacionSaltar->setKeyValueAt(0.5, 1);
    animacionSaltar->setEndValue(0);
    animacionSaltar->setDuration(800);
    animacionSaltar->setEasingCurve(QEasingCurve::OutInQuint);
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
        personaje->estarQuieto();
        timer.stop();
    }
    else if(!timer.isActive())
    {
        personaje->caminar();
        timer.start();
        qDebug()<<"Mover";
    }
}

/*Primero, llamamos a la QGraphicsScene::collidingItems()
 * función de la escena , que toma el elemento para el cual
 *  los elementos en colisión deben detectarse como primer
 * argumento. Con el segundo argumento opcional, puede definir
 * cómo se debe detectar la colisión. El tipo de ese argumento es el Qt::ItemSelectionModeque.
 *  Por defecto, un elemento se considerará colisionando personaje si las formas de los dos elementos se cruzan*/
void NivelUno::verificarColisionMoneda()
{
    for(QGraphicsItem *item : collidingItems(personaje))
    {
        if(Moneda *m = qgraphicsitem_cast<Moneda*>(item))
        {
            removeItem(m);
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
        qreal tierraY = (nivelTierra - personaje->boundingRect().height());
        qreal y = tierraY - animacionSaltar->currentValue().toReal() * alturaSalto;
        personaje->setY(y);

        verificarColisionMoneda();
    }
}

void NivelUno::iniciarEscena()
{
    setSceneRect(0,0,1280,720);

    //Agregamos el cielo
    cielo = new BackgroundItem(QPixmap(":Imagenes/sky.png"));
    cielo->setPos(0,0);
    addItem(cielo);

    //Agregamos el piso
    tierra = new BackgroundItem(QPixmap(":Imagenes/ground.png"));
    addItem(tierra);
    tierra->setPos(0,nivelTierra);

    //Agregamos monedas
    moneda = new Moneda();
    moneda->setPos(500, nivelTierra - moneda->boundingRect().height() - 250);
    addItem(moneda);

    //Agregamos personaje
    personaje =  new Personaje();
    minX = personaje->boundingRect().width() / 2;
    maxX = anchoEscena - personaje->boundingRect().width() / 2;
    personaje->setPos(minX,nivelTierra - personaje->boundingRect().height());
    posicionX = minX;
    addItem(personaje);

}

void NivelUno::moverJugador()
{
    qDebug() << "Mover Personaje";
    verificarColisionMoneda();
    /*A continuación, calculamos el turno que debe obtener el elemento del jugador y
     *  lo almacenamos dx. La distancia que el jugador debe moverse cada 30 milisegundos
     *  está definida por la velocidad variable miembro, expresada en píxeles. */
    const int direccion = personaje->getDireccion();
    if(direccion != 0)
    {
        personaje->siguienteSprite();
        const int dx = direccion * velocidad;
        qreal newX = qBound(minX, posicionX + dx, maxX);
        if (newX == posicionX)
        {
            return;
        }
        posicionX = newX;

        const int longituCambio = 150;
        int derechaLongitudCambio = width() - longituCambio;

        const int posicionVisibleJugador = posicionX - desplazamientoMundo;
        const int newMundoDerecha = posicionVisibleJugador - derechaLongitudCambio;
        if (newMundoDerecha > 0)
        {
            desplazamientoMundo += newMundoDerecha;
        }
        const int newMundoIzquierda = longituCambio - posicionVisibleJugador;
        if (newMundoIzquierda > 0)
        {
            desplazamientoMundo -= newMundoIzquierda;
        }

        const int maxDesplazamientoMundo = anchoEscena - qRound(width());
        desplazamientoMundo = qBound(0, desplazamientoMundo, maxDesplazamientoMundo);
        personaje->setX(posicionX - desplazamientoMundo);

        const qreal proporcion = qreal(desplazamientoMundo) / maxDesplazamientoMundo;
        aplicarParalelismo(proporcion, cielo);
        aplicarParalelismo(proporcion, tierra);
    }


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
        agregarEntradaHorizontal(-1);
        break;
    case Qt::Key_Space:
        saltar();
        break;
    default:
        break;
    }
}

void NivelUno::keyReleaseEvent(QKeyEvent *event)
{
    if (event->isAutoRepeat()) {
        return;
    }
    switch (event->key()) {
    case Qt::Key_Right:
        agregarEntradaHorizontal(-1);
        break;
    case Qt::Key_Left:
        agregarEntradaHorizontal(1);
        break;

    default:
        break;
    }
}
