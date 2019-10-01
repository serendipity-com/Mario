#include "niveluno.h"

NivelUno::NivelUno(QObject *padre):
    QGraphicsScene(0,0,8000,720,padre)
  , anchoEscena(8000)
  , personaje(nullptr)
  , cielo1(nullptr)
  , cielo2(nullptr)
  , cielo3(nullptr)
  , cielo4(nullptr)
  , cielo5(nullptr)
  , cielo6(nullptr)
  , cielo7(nullptr)
  , tierra(nullptr)
  , nivelTierra(660)
  , velocidad(50)
  , entradaHorizontal(0)
  , moneda(nullptr)
  , moneda1(nullptr)
  ,sorpresa(nullptr)
{
    iniciarEscena();

    timerSprite = new QTimer(this);
    connect(timerSprite, SIGNAL(timeout()), this, SLOT(siguienteSprite()));

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(actualizar()));
    timer->start(10);


}

NivelUno::~NivelUno()
{
    delete personaje;

    delete cielo1;
    delete cielo2;
    delete cielo3;
    delete cielo4;
    delete cielo5;
    delete cielo6;
    delete cielo7;
    delete tierra;

    delete moneda1;
    delete moneda;
    delete ladrillo;
    delete ladrillo2;
    delete ladrillo3;
    delete sorpresa;
    delete sorpresa2;
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
        timerSprite->stop();
        qDebug() << "No";
    }
    else if(!timerSprite->isActive())
    {
        personaje->caminar();
        timerSprite->start(50);
        qDebug() << "Si";
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

void NivelUno::verificarColisionPlataforma(PersonajeFisica *p)
{
    for(QGraphicsItem *item : collidingItems(personaje))
    {
        if(LadrilloSorpresa *m = qgraphicsitem_cast<LadrilloSorpresa*>(item))
        {
            if(personaje->estarTocandoCabeza(m))
            {
                p->setVel(p->getVelX(), -1*(0.2)*p->getVelY(),p->getPosX(), p->getPosY());
            }
            else if(personaje->estarTocandoPlataforma(m))
            {
                p->setVel(p->getVelX(), -1*(0.1)*p->getVelY(), p->getPosX(), p->getPosY());
            }
        }
        else if(Ladrillo *l = qgraphicsitem_cast<Ladrillo*>(item))
        {
            if(personaje->estarTocandoCabeza(l))
            {
                p->setVel(p->getVelX(), -1*(0.2)*p->getVelY(),p->getPosX(), p->getPosY());
            }
            else if(personaje->estarTocandoPlataforma(l))
            {
                p->setVel(p->getVelX(), -1*(0.1)*p->getVelY(), p->getPosX(), p->getPosY());
            }
        }
    }
}

void NivelUno::verificarColisionBordes(PersonajeFisica *p)
{

    if(p->getPosX() < personaje->boundingRect().width())
    {
        p->setVel(0,-1*(0.1)*p->getVelY(),personaje->boundingRect().width(),p->getPosY());
    }
    if(p->getPosX() > 1280 - personaje->boundingRect().width() - 200)
    {
        p->setVel(0,-1*(0.1)*p->getVelY(),1280 - personaje->boundingRect().width() - 200,p->getPosY());
    }

    if(p->getPosY() > 660 - personaje->boundingRect().height())
    {
        p->setVel(p->getVelX(), -1*(0.1)*p->getVelY(),p->getPosX(),nivelTierra - personaje->boundingRect().height());
    }
    if(p->getPosY() < personaje->boundingRect().height())
    {
        p->setVel(p->getVelX(), -1*(0.1)*p->getVelY(), p->getPosX(), personaje->boundingRect().height() );
    }
}
//timerEvent se encarga de manejas los sprites de los objetos en escena.
void NivelUno::timerEvent(QTimerEvent *)
{
    moneda->siguienteSprite();
    moneda1->siguienteSprite();
    sorpresa->siguienteSprite();
    sorpresa2->siguienteSprite();
}

void NivelUno::aplicarParalelismo(qreal propocion, QGraphicsItem *item)
{
    item->setX(-propocion * (item->boundingRect().width() - width()));
}


void NivelUno::iniciarEscena()
{
    setSceneRect(0,0,1280,720);

    //Agregamos el cielo
    cielo1 = new BackgroundItem(QPixmap(":/Imagenes/1-1.png"));
    cielo1->setPos(0,-100);
    addItem(cielo1);
    cielo2 = new BackgroundItem(QPixmap(":Imagenes/1-2.png"));
    cielo2->setPos(0,0);
    addItem(cielo2);
    cielo3 = new BackgroundItem(QPixmap(":Imagenes/1-3.png"));
    cielo3->setPos(0,0);
    addItem(cielo3);
    cielo4 = new BackgroundItem(QPixmap(":Imagenes/1-4.png"));
    cielo4->setPos(0,0);
    addItem(cielo4);
    cielo5 = new BackgroundItem(QPixmap(":Imagenes/1-5.png"));
    cielo5->setPos(0,-90);
    addItem(cielo5);
    cielo6 = new BackgroundItem(QPixmap(":Imagenes/1-6.png"));
    cielo6->setPos(0,-90);
    addItem(cielo6);
    cielo7 = new BackgroundItem(QPixmap(":Imagenes/1-7.png"));
    cielo7->setPos(0,-170);
    addItem(cielo7);

    //Agregamos el piso
    tierra = new BackgroundItem(QPixmap(":Imagenes/1-8.png"));
    addItem(tierra);
    tierra->setPos(0,-190);

    //Agregamos monedas
    moneda = new Moneda();
    moneda->setPos(500, nivelTierra - moneda->boundingRect().height() - 250);
    addItem(moneda);
    moneda1 = new Moneda();
    moneda1->setPos(1400, nivelTierra - moneda1->boundingRect().height() - 100);
    addItem(moneda1);



    //Agregamos ladrillo sorpresa
    ladrillo = new Ladrillo();
    ladrillo->setPos(550,500);
    addItem(ladrillo);
    sorpresa = new LadrilloSorpresa();
    sorpresa->setPos(600,500);
    addItem(sorpresa);
    ladrillo2 = new Ladrillo();
    ladrillo2->setPos(650,500);
    addItem(ladrillo2);
    sorpresa2 = new LadrilloSorpresa();
    sorpresa2->setPos(700,500);
    addItem(sorpresa2);
    ladrillo3 = new Ladrillo();
    ladrillo3->setPos(750,500);
    addItem(ladrillo3);


    //Agregamos personaje
    personaje =  new Personaje();
    minX = personaje->boundingRect().width();
    maxX = anchoEscena - personaje->boundingRect().width() / 2;
    personaje->setPos(minX,nivelTierra - personaje->boundingRect().height());
    posicionX = minX;
    addItem(personaje);

    startTimer(100);
}

void NivelUno::actualizar()
{
    verificarColisionPlataforma(personaje->getFisica());
    personaje->actualizar(nivelTierra);
    moverJugador();
    verificarColisionBordes(personaje->getFisica());
}

void NivelUno::moverJugador()
{

    verificarColisionMoneda();
    /*A continuación, calculamos el turno que debe obtener el elemento del jugador y
     *  lo almacenamos dx. La distancia que el jugador debe moverse cada 30 milisegundos
     *  está definida por la velocidad variable miembro, expresada en píxeles. */
    const int direccion = personaje->getDireccion();
    if(direccion != 0)
    {
        PersonajeFisica *p = personaje->getFisica();
        const int dx = 7*direccion;
        qreal newX = qBound(minX, posicionX + dx, maxX);
        if (newX == posicionX)
        {
            return;
        }
        posicionX = newX;

        const int longituCambio = 300;
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

        if(personaje->pos().x() >= 1035 && personaje->getDireccion()  == 1)
        {
            moneda->setX(-dx + moneda->pos().x());
            moneda1->setX(-dx + moneda1->pos().x());
            ladrillo->setX(-dx + ladrillo->pos().x());
            ladrillo2->setX(-dx + ladrillo2->pos().x());
            ladrillo3->setX(-dx + ladrillo3->pos().x());
            sorpresa->setX(-dx + sorpresa->pos().x());
            sorpresa2->setX(-dx + sorpresa2->pos().x());


            const qreal proporcion = qreal(desplazamientoMundo) / maxDesplazamientoMundo;
            aplicarParalelismo(proporcion, cielo1);
            aplicarParalelismo(proporcion, cielo2);
            aplicarParalelismo(proporcion, cielo3);
            aplicarParalelismo(proporcion, cielo4);
            aplicarParalelismo(proporcion, cielo5);
            aplicarParalelismo(proporcion, cielo6);
            aplicarParalelismo(proporcion, cielo7);
            aplicarParalelismo(proporcion, tierra);
        }
    }


}

void NivelUno::siguienteSprite()
{
    personaje->siguienteSprite();
}

void NivelUno::keyPressEvent(QKeyEvent *event)
{
    PersonajeFisica *p = personaje->getFisica();

    switch (event->key())
    {
    case Qt::Key_Right:
        p->setVel(velocidad,p->getVelY(), p->getPosX(), p->getPosY());
        if (event->isAutoRepeat()){return;}
        agregarEntradaHorizontal(1);
        break;
    case Qt::Key_Left:
        p->setVel(-velocidad,p->getVelY(), p->getPosX(), p->getPosY());
        if (event->isAutoRepeat()){return;}
        agregarEntradaHorizontal(-1);
        break;
    case Qt::Key_Space:
        if(p->getPosY() <= 1+personaje->boundingRect().height())
        {
            p->setVel(p->getVelX(), 300, p->getPosX(), p->getPosY());
        }
        break;
    }
}

void NivelUno::keyReleaseEvent(QKeyEvent *event)
{
    if (event->isAutoRepeat()) {
        return;
    }
    switch (event->key())
    {
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
