#include "niveluno.h"

NivelUno::NivelUno(QObject *padre):
    QGraphicsScene(0,0,8000,720,padre)
  , anchoEscena(8000)
  , personaje(nullptr)
  , personajeSmall(nullptr)
  , estado(small)
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
{
    iniciarEscena();

    sonidos = new AdministradorSonidos();

    timerSprite = new QTimer(this);
    connect(timerSprite, SIGNAL(timeout()), this, SLOT(siguienteSprite()));

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(actualizar()));
    timer->start(10);
}

NivelUno::~NivelUno()
{
    delete personaje;
    delete personajeSmall;

    delete cielo1;
    delete cielo2;
    delete cielo3;
    delete cielo4;
    delete cielo5;
    delete cielo6;
    delete cielo7;
    delete tierra;

    monedas.clear();
    ladrillos.clear();
    ladrillosSorpresa.clear();
    tubos.clear();
    floresCar.clear();
    gombas.clear();
}

void NivelUno::agregarEntradaHorizontal(int entrada)
{
    entradaHorizontal += entrada;
    if (estado == small){personajeSmall->setDireccion(qBound(-1, entradaHorizontal, 1));}
    else if (estado == normal){personaje->setDireccion(qBound(-1, entradaHorizontal, 1));}
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
    if(estado == small)
    {
        if(personajeSmall->getDireccion() == 0)
        {
            personajeSmall->estarQuieto();
            timerSprite->stop();
            //qDebug() << "No";
        }
        else if(!timerSprite->isActive())
        {
            personajeSmall->caminar();
            timerSprite->start(50);
            //qDebug() << "Si";
        }
    }
    else if(estado == normal)
    {
        if(personaje->getDireccion() == 0)
        {
            personaje->estarQuieto();
            timerSprite->stop();
            //qDebug() << "No";
        }
        else if(!timerSprite->isActive())
        {
            personaje->caminar();
            timerSprite->start(50);
            //qDebug() << "Si";
        }
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
    if(estado == small)
    {
        for(QGraphicsItem *item : collidingItems(personajeSmall))
        {
            if(Moneda *m = qgraphicsitem_cast<Moneda*>(item))
            {
                removeItem(m);
                sonidos->reproducirMoneda();
            }
        }
    }
    else if(estado == normal)
    {
        for(QGraphicsItem *item : collidingItems(personaje))
        {
            if(Moneda *m = qgraphicsitem_cast<Moneda*>(item))
            {
                removeItem(m);
                sonidos->reproducirMoneda();
            }
        }
    }
}

void NivelUno::verificarColisionEnemigos(PersonajeFisica *p)
{
    if(estado == small)
    {
        for(QGraphicsItem *item : collidingItems(personajeSmall))
        {
            if(Goomba *m = qgraphicsitem_cast<Goomba*>(item))
            {
                if(personajeSmall->estarTocandoPies(m) )
                {
                    qDebug() << "Mata";
                    removeItem(m);
                    p->setVel(p->getVelX(), -1*(0.8)*p->getVelY(), p->getPosX(), nivelTierra - m->pos().y() + personajeSmall->boundingRect().height());
                }
                else
                {
                    qDebug() << "Muere";
                }
            }
        }
    }
    else if(estado == normal)
    {
        for(QGraphicsItem *item : collidingItems(personaje))
        {
            if(Goomba *m = qgraphicsitem_cast<Goomba*>(item))
            {
                if(personaje->estarTocandoPies(m) )
                {
                    qDebug() << "Mata";
                    removeItem(m);
                    p->setVel(p->getVelX(), -1*(0.8)*p->getVelY(), p->getPosX(), nivelTierra - m->pos().y() + personaje->boundingRect().height());
                }
                else
                {
                    estado = normal;
                    qDebug() << "Muere";
                }
            }
        }
    }
}

void NivelUno::verificarColisionPlataforma(PersonajeFisica *p)
{
    if(estado == small)
    {
        for(QGraphicsItem *item : collidingItems(personajeSmall))
        {
            if(LadrilloSorpresa *m = qgraphicsitem_cast<LadrilloSorpresa*>(item))
            {
                if(personajeSmall->estarTocandoCabeza(m))
                {
                    p->setVel(p->getVelX(), -1*(0.8)*p->getVelY(),p->getPosX(), p->getPosY());
                }
                else if(personajeSmall->estarTocandoPlataforma(m))
                {
                    p->setVel(p->getVelX(), -1*(0.1)*p->getVelY(), p->getPosX(), nivelTierra - m->pos().y() + personajeSmall->boundingRect().height());
                }
            }
            if(Ladrillo *l = qgraphicsitem_cast<Ladrillo*>(item))
            {
                if(personajeSmall->estarTocandoCabeza(l))
                {
                    p->setVel(p->getVelX(), -1*(0.8)*p->getVelY(),p->getPosX(), p->getPosY());
                }
                else if(personajeSmall->estarTocandoPlataforma(l))
                {
                    p->setVel(p->getVelX(), -1*(0.1)*p->getVelY(), p->getPosX(), nivelTierra - l->pos().y() + personajeSmall->boundingRect().height());
                }
            }
            else if(Tubo *t = qgraphicsitem_cast<Tubo*>(item))
            {
                if(personajeSmall->estarTocandoPlataforma(t))
                {
                    p->setVel(p->getVelX(), -1*(0.1)*p->getVelY(), p->getPosX(), nivelTierra - t->pos().y() + personajeSmall->boundingRect().height());
                }
                else
                {
                    p->setVel(-1*(0.2)*p->getVelX(),p->getVelY(), p->getPosX(),p->getPosY());
                }
            }
        }
    }
    else if(estado == normal)
    {
        for(QGraphicsItem *item : collidingItems(personaje))
        {
            if(LadrilloSorpresa *m = qgraphicsitem_cast<LadrilloSorpresa*>(item))
            {
                if(personaje->estarTocandoCabeza(m))
                {
                    p->setVel(p->getVelX(), -1*(0.8)*p->getVelY(),p->getPosX(), p->getPosY());
                }
                else if(personaje->estarTocandoPlataforma(m))
                {
                    p->setVel(p->getVelX(), -1*(0.1)*p->getVelY(), p->getPosX(), nivelTierra - m->pos().y() + personaje->boundingRect().height());
                }
            }
            if(Ladrillo *l = qgraphicsitem_cast<Ladrillo*>(item))
            {
                if(personaje->estarTocandoCabeza(l))
                {
                    p->setVel(p->getVelX(), -1*(0.8)*p->getVelY(),p->getPosX(), p->getPosY());
                }
                else if(personaje->estarTocandoPlataforma(l))
                {
                    p->setVel(p->getVelX(), -1*(0.1)*p->getVelY(), p->getPosX(), nivelTierra - l->pos().y() + personaje->boundingRect().height());
                }
            }
            else if(Tubo *t = qgraphicsitem_cast<Tubo*>(item))
            {
                if(personaje->estarTocandoPlataforma(t))
                {
                    p->setVel(p->getVelX(), -1*(0.1)*p->getVelY(), p->getPosX(), nivelTierra - t->pos().y() + personaje->boundingRect().height());
                }
                else
                {
                    p->setVel(-1*(0.2)*p->getVelX(),p->getVelY(), p->getPosX(),p->getPosY());
                }
            }
        }
    }
}

void NivelUno::verificarColisionBordes(PersonajeFisica *p)
{

    if(p->getPosX() < p->getAncho())
    {
        p->setVel(0,-1*(0.1)*p->getVelY(), p->getAlto(),p->getPosY());
    }
    if(p->getPosX() > 1280 - p->getAncho() - 200)
    {
        p->setVel(0,-1*(0.1)*p->getVelY(),1280 - p->getAncho() - 200,p->getPosY());
    }
    if(p->getPosY() < p->getAlto())
    {
        p->setVel(p->getVelX(), -1*(0.1)*p->getVelY(), p->getPosX(), p->getAlto());
    }
}

void NivelUno::cambiarDireccionGomba()
{
    for (int i = 0; i < tubos.size(); i++)
    {
        for(QGraphicsItem *item : collidingItems(tubos.at(i)))
        {
            if(Goomba *m = qgraphicsitem_cast<Goomba*>(item))
            {
                if(m->getDireccion() == -1)
                {
                    m->setDireccion(1);
                    m->setX(m->pos().x() - 65);
                }
                else
                {
                    m->setDireccion(-1);
                    m->setX(m->pos().x() + 65);
                }
            }
        }
    }
}

//timerEvent se encarga de manejas los sprites de los objetos en escena.
void NivelUno::timerEvent(QTimerEvent *)
{
    for (int i = 0;i < monedas.size(); i++)
    {
        monedas.at(i)->siguienteSprite();
    }
    for (int i = 0;i < ladrillosSorpresa.size(); i++)
    {
        ladrillosSorpresa.at(i)->siguienteSprite();
    }
    for (int i = 0;i < gombas.size(); i++)
    {
        gombas.at(i)->siguienteSprite();
    }
    for (int i = 0;i < floresCar.size(); i++)
    {
        floresCar.at(i)->siguienteSprite();
    }

    //mueve los goomba
    for (int i = 0;i < gombas.size(); i++)
    {
        gombas.at(i)->setX(gombas.at(i)->pos().x() + gombas.at(i)->getDireccion() * (-7));
    }
}

void NivelUno::aplicarParalelismo(qreal propocion, QGraphicsItem *item)
{
    item->setX(-propocion * (item->boundingRect().width() - width()));
}

//crea valores inciales
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
    tierra->setPos(0,-183);


    //Agregamos ladrillos
    int posLadrillo[17][3] = {{550,500,1}, {650,500,1}, {750,500,1}, {650,300,1}, {1150,400,2}, {1350,500,2}, {1350,200,6}, {2150,450,1}
                             , {2250,450,1}, {3050,610,4}, {3100,560,3}, {3150,510,2}, {3200,460,1}, {3425,460,1}, {3425,510,2}, {3425,560,3}
                             , {3425,610,4}};
    int posLadrilloSorpresa[3][2] = {{600,500}, {700,500}, {2200,450}};
    for (int i = 0; i < 17; i++)
    {
        ladrillos.append(new Ladrillo(posLadrillo[i][2]));
        ladrillos.last()->setPos(posLadrillo[i][0],posLadrillo[i][1]);
        addItem(ladrillos.last());
    }
    for (int j = 0; j < 3; j++)
    {
        ladrillosSorpresa.append(new LadrilloSorpresa());
        ladrillosSorpresa.last()->setPos(posLadrilloSorpresa[j][0],posLadrilloSorpresa[j][1]);
        addItem(ladrillosSorpresa.last());
    }

    //Agregamos monedas
    int posMonedas[24][2] ={{550,450}, {600,450}, {650,450}, {700,450}, {750,450}, {650,250}, {1150,350}, {1200,350}, {1350,150}, {1400,150}
                         , {1450,150}, {1500,150}, {1550,150}, {1600,150}, {2750,500},{2800,500}, {2850,500}, {2900,500}, {2950,500}, {3000,500}, {2950,450}
                         , {2950,550}, {2900,400}, {2900,600}};
    for (int i= 0; i < 24;i++)
    {
        monedas.append(new Moneda());
        monedas.last()->setPos(posMonedas[i][0], posMonedas[i][1]);
        addItem(monedas.last());
    }

    //Agregamos tubos
    int posTubos[5] = {900, 1500, 2000, 2500, 3275};
    for (int i = 0; i < 5; i++)
    {
        tubos.append(new Tubo());
        tubos.last()->setPos(posTubos[i], nivelTierra - tubos.last()->boundingRect().height());
        addItem(tubos.last());
    }

    //Agregamos flor carnobora
    int posFloresCar[2] = {1475, 3250};
    for (int i = 0; i < 2; i++)
    {
        floresCar.append(new Flor());
        floresCar.last()->setPos(posFloresCar[i], tubos.at(1)->pos().y() - floresCar.last()->boundingRect().height());
        addItem(floresCar.last());
    }

    //Agregamos enemigo Goomba
    int posGombas[8] = {800, 1000, 1600, 1800, 2100, 2200, 2300, 2400};
    for (int i = 0; i < 8; i++)
    {
        gombas.append(new Goomba());
        gombas.last()->setPos(posGombas[i], nivelTierra - gombas.last()->boundingRect().height());
        addItem(gombas.last());
    }

    //Agregamos personaje
    personaje =  new Personaje();
    minX = personaje->boundingRect().width();
    maxX = anchoEscena - personaje->boundingRect().width() / 2;
    personaje->setPos(minX,nivelTierra - personaje->boundingRect().height());
    posicionX = minX;
    addItem(personaje);

    personajeSmall = new PersonajeSmall();
    minX = personajeSmall->boundingRect().width();
    maxX = anchoEscena - personajeSmall->boundingRect().width() / 2;
    personajeSmall->setPos(minX,nivelTierra - personajeSmall->boundingRect().height());
    posicionX = minX;
    addItem(personajeSmall);

    startTimer(100);
}

void NivelUno::actualizar()
{

    if(estado == small)
    {
        personajeSmall->actualizar(nivelTierra);
        moverJugador();
        verificarColisionEnemigos(personajeSmall->getFisica());
        verificarColisionPlataforma(personajeSmall->getFisica());
        verificarColisionBordes(personajeSmall->getFisica());}

    else if(estado == normal){
        personaje->actualizar(nivelTierra);
        verificarColisionEnemigos(personajeSmall->getFisica());
        verificarColisionPlataforma(personajeSmall->getFisica());
        verificarColisionBordes(personajeSmall->getFisica());
    }
    verificarColisionMoneda();
    cambiarDireccionGomba();
}

void NivelUno::moverJugador()
{
    /*A continuación, calculamos el turno que debe obtener el elemento del jugador y
     *  lo almacenamos dx. La distancia que el jugador debe moverse cada 30 milisegundos
     *  está definida por la velocidad variable miembro, expresada en píxeles. */
    int direccion = 0;
    if(estado == small){ direccion = personajeSmall->getDireccion();}
    else if (estado == normal){personaje->getDireccion();}
    if(direccion != 0)
    {
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

        if((personaje->pos().x() >= 1035 && personaje->getDireccion()  == 1) || (personajeSmall->pos().x() >= 1035 && personajeSmall->getDireccion()  == 1))
        {
            //mueve los ladrillos
            for (int i = 0;i < ladrillos.size(); i++)
            {
                ladrillos.at(i)->setX(-dx + ladrillos.at(i)->pos().x());
            }
            for (int i = 0;i < ladrillosSorpresa.size(); i++)
            {
                ladrillosSorpresa.at(i)->setX(-dx + ladrillosSorpresa.at(i)->pos().x());
            }

            //mueve las monedas
            for (int i = 0;i < monedas.size(); i++)
            {
                monedas.at(i)->setX(-dx + monedas.at(i)->pos().x());
            }

            //mover goombas
            for (int i = 0;i < gombas.size(); i++)
            {
                gombas.at(i)->setX(-dx + gombas.at(i)->pos().x());
            }

            //mover tubos
            for (int i = 0;i < tubos.size(); i++)
            {
                tubos.at(i)->setX(-dx + tubos.at(i)->pos().x());
            }

            //mover flores
            for (int i = 0;i < floresCar.size(); i++)
            {
                floresCar.at(i)->setX(-dx + floresCar.at(i)->pos().x());
            }

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
    if (estado == small){personajeSmall->siguienteSprite();}
    else if (estado == normal){personaje->siguienteSprite();}
}

void NivelUno::keyPressEvent(QKeyEvent *event)
{
    PersonajeFisica *p = personajeSmall->getFisica();
    if(estado == normal){p = personaje->getFisica();}

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
            p->setVel(p->getVelX(), 250, p->getPosX(), p->getPosY());
            sonidos->reproducirSalto();
        break;
    }
}

void NivelUno::keyReleaseEvent(QKeyEvent *event)
{
    switch (event->key())
    {
    case Qt::Key_Right:
        if (event->isAutoRepeat()) {return;}
        agregarEntradaHorizontal(-1);
        break;
    case Qt::Key_Left:
        if (event->isAutoRepeat()) {return;}
        agregarEntradaHorizontal(1);
        break;

    default:
        break;
    }
}
