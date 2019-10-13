#include "niveldos.h"


NivelDos::NivelDos(QObject *padre) : QGraphicsScene(0,0,8000,720,padre)
, anchoEscena(8000)
, personaje(nullptr)
, personajeSmall(nullptr)
, personajeFire(nullptr)
, salto(true)
, estado(small)
, cielo1(nullptr)
, cielo2(nullptr)
, cielo3(nullptr)
, cielo4(nullptr)
, cielo5(nullptr)
, cielo6(nullptr)
, tierra(nullptr)
, nivelTierra(660)
, velocidad(50)
, hongo(nullptr)
, florFuego(nullptr)
{
    iniciarEscena();
    sonidos = new AdministradorSonidos();
    sonidos->reproducirLevel2();

    timerSprite = new QTimer(this);
    connect(timerSprite, SIGNAL(timeout()), this, SLOT(siguienteSprite()));

    timerMando = new QTimer(this);
    connect(timerMando, SIGNAL(timeout()), this, SLOT(moverConMando()));

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(actualizar()));
    timer->start(10);
}

NivelDos::~NivelDos()
{
    delete personaje;
    delete personajeSmall;
    delete personajeFire;

    delete cielo1;
    delete cielo2;
    delete cielo3;
    delete cielo4;
    delete cielo5;
    delete cielo6;
    delete tierra;

    delete hongo;
    delete florFuego;

    delete puntaje;
    delete puntajeLogo;

    monedas.clear();
    ladrillos.clear();
    ladrillosSorpresa.clear();
    ladrillosNota.clear();
    fantasmas.clear();
    tubos.clear();
    floresCar.clear();
    gombas.clear();
}

void NivelDos::iniciarEscena()
{
    setSceneRect(0,0,1280,720);

    //Agregamos el cielo
    cielo1 = new BackgroundItem(QPixmap(":Imagenes/2-1.png"));
    cielo1->setPos(0,0);
    addItem(cielo1);
    cielo2 = new BackgroundItem(QPixmap(":Imagenes/2-2.png"));
    cielo2->setPos(0,0);
    addItem(cielo2);
    cielo3 = new BackgroundItem(QPixmap(":Imagenes/2-3.png"));
    cielo3->setPos(0,0);
    addItem(cielo3);
    cielo4 = new BackgroundItem(QPixmap(":Imagenes/2-4.png"));
    cielo4->setPos(0,0);
    addItem(cielo4);
    cielo5 = new BackgroundItem(QPixmap(":Imagenes/2-5.png"));
    cielo5->setPos(0,0);
    addItem(cielo5);
    cielo6 = new BackgroundItem(QPixmap(":Imagenes/2-6.png"));
    cielo6->setPos(0,0);
    addItem(cielo6);

    //Agregamos puntaje
    puntajeLogo = new BackgroundItem(QPixmap(":/Imagenes/puntaje.png"));
    puntajeLogo->setPos(50,40);
    addItem(puntajeLogo);
    puntaje = new Puntaje();
    puntaje->setPos(puntajeLogo->pos().x() + puntajeLogo->boundingRect().width() , 25);
    addItem(puntaje);

    //Agregamos el piso
    tierra = new BackgroundItem(QPixmap(":Imagenes/2-7.png"));
    addItem(tierra);
    tierra->setPos(0,-118);


    //Agregamos ladrillos
    int posLadrillo[74][3] = {{200,450,1},{250,400,1},{400,250,1},{450,250,1},{500,250,1},{550,250,1},{600,250,1}
                              ,{200,450,1},{650,250,1},{800,250,1},{950,250,1},{450,100,1},{550,100,1},{1100,100,1}
                              ,{1150,100,1},{1300,250,1},{1500,250,1},{1550,250,1},{1600,250,1},{1100,400,1}
                              ,{1150,400,1},{1300,400,1},{1350,400,1},{2050,400,1},{2100,300,1},{2150,200,1},{2300,200,1}
                              ,{2350,200,1},{2400,200,1},{2700,200,1},{2750,200,1},{2800,200,1},{3100,200,1},{3400,200,1}
                              ,{3550,200,1},{4300,500,1},{4400,300,1},{4450,200,1},{4350,100,1},{4200,100,1},{3800,100,1}
                              ,{4750,200,1},{5050,200,1},{5350,200,1},{5650,200,1},{5950,200,1},{6350,200,1},{7000,610,1}
                              ,{7050,610,1},{7100,610,1},{7150,610,1},{7200,610,1},{7250,610,1},{7300,610,1},{7050,560,1}
                              ,{7100,560,1},{7150,560,1},{7200,560,1},{7250,560,1},{7300,560,1},{7100,510,1},{7150,510,1}
                              ,{7200,510,1},{7250,510,1},{7300,510,1},{7150,460,1},{7200,460,1},{7250,460,1},{7300,460,1}
                              ,{7200,410,1},{7250,410,1},{7300,410,1},{7250,360,1},{7300,360,1}};
    int posLadrilloSorpresa[4][2] = {{500,100},{600,100},{2350,50},{3550,350}};
    for (int i = 0; i < 74; i++)
    {
        ladrillos.append(new Ladrillo(posLadrillo[i][2]));
        ladrillos.last()->setPos(posLadrillo[i][0],posLadrillo[i][1]);
        addItem(ladrillos.last());
    }
    for (int j = 0; j < 4; j++)
    {
        ladrillosSorpresa.append(new LadrilloSorpresa());
        ladrillosSorpresa.last()->setPos(posLadrilloSorpresa[j][0],posLadrilloSorpresa[j][1]);
        if(j == 0){ladrillosSorpresa.last()->setRegalo(3);}
        else if(j == 1){ladrillosSorpresa.last()->setRegalo(1);}
        else {ladrillosSorpresa.last()->setRegalo(2);}
        addItem(ladrillosSorpresa.last());
    }

    //Agregamos fantasmas
    int posFantasmas[18][2] ={{2200,550},{2400,550},{2600,550},{2800,550},{2200,400},{2400,400},{2600,400}
                             ,{2800,400},{5350,550},{5550,550},{5750,550},{5950,550},{6150,550},{5350,400}
                              ,{5550,400},{5750,400},{5950,400},{6150,400}};
    for (int i= 0; i < 18;i++)
    {
        fantasmas.append(new Fantasma());
        fantasmas.last()->setPos(posFantasmas[i][0], posFantasmas[i][1]);
        addItem(fantasmas.last());
    }

//    //Agregamos ladrillos de notas musicales
    int posLadrillonNota[18][3] = {{2200,500,2},{2400,500,2},{2600,500,2},{2800,500,2},{2200,350,2},{2400,350,2}
                                  ,{2600,350,2},{2800,350,2},{5350,500,2},{5550,500,2},{5750,500,2},{5950,500,2}
                                   ,{6150,500,2},{5350,350,2},{5550,350,2},{5750,350,2},{5950,350,2},{6150,350,2}};
    for (int i = 0; i < 18; i++)
    {
        ladrillosNota.append(new LadrilloNota(posLadrillonNota[i][2]));
        ladrillosNota.last()->setPos(posLadrillonNota[i][0],posLadrillonNota[i][1]);
        addItem(ladrillosNota.last());
    }

    //Agregamos monedas
    int posMonedas[80][2] = {{200,400},{250,350},{450,50},{500,50},{550,50},{600,50},{1100,50},{1150,50}
                             ,{1300,200},{1100,350},{1150,350},{1300,350},{1350,350},{1500,200}
                             ,{1550,200},{1600,200},{1000,500},{1050,500},{1100,500},{1150,500},{1200,500}
                             ,{1250,500},{1300,500},{1350,500},{1400,500},{2300,150},{2350,150},{2400,150}
                             ,{2700,150},{2750,150},{2800,150},{3100,150},{3400,150},{3550,150},{3700,250}
                             ,{3700,300},{3750,200},{3750,350},{3800,150},{3800,350},{3850,100},{3850,350}
                             ,{3850,150},{3850,200},{3850,250},{3850,300},{3850,400},{3900,450},{3950,450}
                             ,{4000,450},{4050,450},{3900,100},{3900,150},{3900,200},{3900,50},{3950,200}
                             ,{3950,50},{4000,200},{4000,50},{4050,100},{4050,150},{4050,200},{4050,50}
                             ,{3900,300},{4050,300},{4100,100},{4100,150},{4100,200},{4100,250},{4100,300}
                             ,{4100,350},{4100,400},{4150,150},{4150,350},{4200,200},{4200,350},{4250,250}
                             ,{4250,300},{3950,400},{4000,400}};
    for (int i= 0; i < 80; i++)
    {
        monedas.append(new Moneda());
        monedas.last()->setPos(posMonedas[i][0], posMonedas[i][1]);
        addItem(monedas.last());
    }

    //Agregamos hongos
    hongo = new Hongo();
    hongo->setPos(-500, -500);
    addItem(hongo);

    //Agregamos flor de bonus
    florFuego = new FlorFuego();
    florFuego->setPos(-500,-500);
    addItem(florFuego);

    //Agregamos tubos
    int posTubos[21] = {300,400,500,600,700,800,900,1450,2000,3000,3550,4450,4550,4650,4750,4850,4950,5050,5150,5250
                       ,6350};
    for (int i = 0; i < 21; i++)
    {
        tubos.append(new Tubo());
        tubos.last()->setPos(posTubos[i], nivelTierra - tubos.last()->boundingRect().height());
        addItem(tubos.last());
    }

    //Agregamos flor carnobora
    int posFloresCar[18] = {275,375,475,575,675,775,875,1425,2975,4425,4525,4625,4725,4825,4925,5025,5125,5225};
    for (int i = 0; i < 18; i++)
    {
        floresCar.append(new Flor());
        floresCar.last()->setPos(posFloresCar[i], tubos.at(1)->pos().y() - floresCar.last()->boundingRect().height());
        addItem(floresCar.last());
    }

    //Agregamos enemigo Goomba
    int posGombas[47] = {1050,1100,1150,1200,1300,1350,1400,1475,1525,1625,1675,1725
                        ,1775,1875,1925,1975,2125,2175,2275,2325,2425
                         ,2525,2575,2675,2775,3025,3075,3175,3275,3325
                         ,3375,3525,5300,5350,5450,5500,5600,5650,5700,5750
                        ,5800,5900,5950,6000,6100,6150,6250};
    for (int i = 0; i < 47; i++)
    {
        gombas.append(new Goomba());
        gombas.last()->setPos(posGombas[i], nivelTierra - gombas.last()->boundingRect().height());
        addItem(gombas.last());
    }

    //Agregamos personaje
    personaje =  new Personaje(1);
    addItem(personaje);

    personajeFire = new Personaje(3);
    addItem(personajeFire);

    personajeSmall = new Personaje(2);
    minX = personajeSmall->boundingRect().width();
    maxX = anchoEscena - personajeSmall->boundingRect().width() / 2;
    personajeSmall->setPos(minX,nivelTierra - personajeSmall->boundingRect().height());
    posicionX = minX;
    addItem(personajeSmall);

    startTimer(100);
}

//timerEvent se encarga de manejas los sprites de los objetos en escena.
void NivelDos::timerEvent(QTimerEvent *)
{
    for (int i = 0;i < monedas.size(); i++)
    {
        monedas.at(i)->siguienteSprite();
    }
    for (int i = 0;i < ladrillosSorpresa.size(); i++)
    {
        ladrillosSorpresa.at(i)->siguienteSprite();
    }
    for (int i = 0;i < ladrillosNota.size(); i++)
    {
        ladrillosNota.at(i)->siguienteSprite();
    }
    for (int i = 0;i < gombas.size(); i++)
    {
        gombas.at(i)->siguienteSprite();
    }
    for (int i = 0;i < floresCar.size(); i++)
    {
        floresCar.at(i)->siguienteSprite();
    }
    for (int i = 0;i < fantasmas.size(); i++)
    {
        fantasmas.at(i)->siguienteSprite();
    }

    //mueve los goomba
    for (int i = 0;i < gombas.size(); i++)
    {
        gombas.at(i)->setX(gombas.at(i)->pos().x() + gombas.at(i)->getDireccion() * (-7));
    }
}

void NivelDos::agregarEntradaHorizontal(int entrada)
{
    personajeSmall->setDireccion(qBound(-1, entrada, 1));
    personaje->setDireccion(qBound(-1, entrada, 1));
    personajeFire->setDireccion(qBound(-1, entrada, 1));
    checkTimer();
}

void NivelDos::aplicarParalelismo(qreal propocion, QGraphicsItem *item)
{
    item->setX(-propocion * (item->boundingRect().width() - width()));
}

void NivelDos::moverJugador()
{
    /*A continuación, calculamos el turno que debe obtener el elemento del jugador y
     *  lo almacenamos dx. La distancia que el jugador debe moverse cada 30 milisegundos
     *  está definida por la velocidad variable miembro, expresada en píxeles. */
    int direccion = 0;
    if(estado == small){ direccion = personajeSmall->getDireccion();}
    else if (estado == normal){direccion = personaje->getDireccion();}
    else if (estado == fire){direccion = personajeFire->getDireccion();}
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

        if((personaje->pos().x() >= 1035 && personaje->getDireccion()  == 1) ||
           (personajeSmall->pos().x() >= 1035 && personajeSmall->getDireccion()  == 1) ||
           (personajeFire->pos().x() >= 1035 && personajeFire->getDireccion()  == 1))
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
            for (int i = 0;i < ladrillosNota.size(); i++)
            {
                ladrillosNota.at(i)->setX(-dx + ladrillosNota.at(i)->pos().x());
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

            //mover fantasmas
            for (int i = 0;i < fantasmas.size(); i++)
            {
                fantasmas.at(i)->setX(-dx + fantasmas.at(i)->pos().x());
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

            //mover hongo
            hongo->setX(-dx + hongo->pos().x());

            const qreal proporcion = qreal(desplazamientoMundo) / maxDesplazamientoMundo;
            aplicarParalelismo(proporcion, cielo1);
            aplicarParalelismo(proporcion, cielo2);
            aplicarParalelismo(proporcion, cielo3);
            aplicarParalelismo(proporcion, cielo4);
            aplicarParalelismo(proporcion, cielo5);
            aplicarParalelismo(proporcion, cielo6);
            aplicarParalelismo(proporcion, tierra);
        }
    }
}

/*Esta función primero verifica si el jugador se mueve.
 *  Si no, el temporizador se detiene, porque nada tiene
 *  que actualizarse cuando nuestro personaje se detiene.
 *  De lo contrario, el temporizador se inicia, pero solo
 *  si aún no se está ejecutando. Verificamos esto llamando
 *  isActive()al temporizador.*/
void NivelDos::checkTimer()
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
    else if(estado == fire)
    {
        if(personaje->getDireccion() == 0)
        {
            personajeFire->estarQuieto();
            timerSprite->stop();
            //qDebug() << "No";
        }
        else if(!timerSprite->isActive())
        {
            personajeFire->caminar();
            timerSprite->start(50);
            //qDebug() << "Si";
        }
    }
}

void NivelDos::verificarColisionMoneda()
{
    if(estado == small)
    {
        for(QGraphicsItem *item : collidingItems(personajeSmall))
        {
            if(Moneda *m = qgraphicsitem_cast<Moneda*>(item))
            {
                removeItem(m);
                sonidos->reproducirMoneda();
                puntaje->incrementar();
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
                puntaje->incrementar();
            }
        }
    }
    else if(estado == fire)
    {
        for(QGraphicsItem *item : collidingItems(personajeFire))
        {
            if(Moneda *m = qgraphicsitem_cast<Moneda*>(item))
            {
                removeItem(m);
                sonidos->reproducirMoneda();
                puntaje->incrementar();
            }
        }
    }
}

void NivelDos::verificarColisionAyudas()
{
    if(estado == small)
    {
        PersonajeFisica *p = personajeSmall->getFisica();
        PersonajeFisica *m = personaje->getFisica();
        if(personajeSmall->collidesWithItem(hongo))
        {
            hongo->setPos(-500,-500);
            personajeSmall->setPos(-1000,-1000);
            sonidos->reproducirHongo();
            estado = normal;
            m->setVel(p->getVelX(), p->getVelY(), p->getPosX(), p->getPosY() - personajeSmall->boundingRect().height() + personaje->boundingRect().height());
        }
    }
    else if(estado == normal)
    {
        if(personaje->collidesWithItem(hongo))
        {
            hongo->setPos(-500,-500);
            sonidos->reproducirMoneda();
        }
        if(personaje->collidesWithItem(florFuego))
        {
            florFuego->setPos(-500,-500);
            personaje->setPos(-1000,-1000);
            sonidos->reproducirFlor();
            estado = fire;
            PersonajeFisica *p = personaje->getFisica();
            PersonajeFisica *m = personajeFire->getFisica();
            m->setVel(p->getVelX(), p->getVelY(), p->getPosX(), p->getPosY() - personaje->boundingRect().height() + personajeFire->boundingRect().height());
        }
    }
    else if(estado == fire)
    {
        if(personajeFire->collidesWithItem(hongo))
        {
            hongo->setPos(-500,-500);
            sonidos->reproducirHongo();
        }
    }
}

void NivelDos::verificarColisionEnemigos(PersonajeFisica *p)
{
    if(estado == small)
    {
        for(QGraphicsItem *item : collidingItems(personajeSmall))
        {
            if(Goomba *m = qgraphicsitem_cast<Goomba*>(item))
            {
                if(personajeSmall->estarTocandoPies(m) )
                {
                    removeItem(m);
                    p->setVel(p->getVelX(), -1*(0.8)*p->getVelY(), p->getPosX(), nivelTierra - m->pos().y() + personajeSmall->boundingRect().height());
                }
                else
                {
                    sonidos->reproducirMuerto2();
                    repetirNivel();
                    timerMando->stop();
                    timerSprite->stop();
                    timer->stop();
                    personaje->setDireccion(0);
                    personajeSmall->setDireccion(0);
                    personajeFire->setDireccion(0);
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
                    removeItem(m);
                    p->setVel(p->getVelX(), -1*(0.8)*p->getVelY(), p->getPosX(), nivelTierra - m->pos().y() + personaje->boundingRect().height());
                }
                else
                {
                    //camiar de personaje
                    estado = small;
                    sonidos->reproducirGolpe();
                    PersonajeFisica *p = personajeSmall->getFisica();
                    PersonajeFisica *s = personaje->getFisica();
                    p->setVel(s->getVelX(), s->getVelY(), s->getPosX(), s->getPosY());
                    personaje->setPos(-1000,-1000);
                }
            }
        }
    }
    else if(estado == fire)
    {
        for(QGraphicsItem *item : collidingItems(personajeFire))
        {
            if(Goomba *m = qgraphicsitem_cast<Goomba*>(item))
            {
                if(personajeFire->estarTocandoPies(m) )
                {
                    removeItem(m);
                    p->setVel(p->getVelX(), -1*(0.8)*p->getVelY(), p->getPosX(), nivelTierra - m->pos().y() + personajeFire->boundingRect().height());
                }
                else
                {
                    //camiar de personaje
                    estado = normal;
                    sonidos->reproducirGolpe();
                    PersonajeFisica *p = personaje->getFisica();
                    PersonajeFisica *s = personajeFire->getFisica();
                    p->setVel(s->getVelX(), s->getVelY(), s->getPosX(), s->getPosY());
                    personajeFire->setPos(-1000,-1000);
                }
            }
        }
    }
}

void NivelDos::verificarColisionPlataforma(PersonajeFisica *p)
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
                    //verifica con que tipo de ladrillo colisiona
                    if(m->getRegalo() == 1)
                    {
                        florFuego->setPos(m->pos().x(), m->pos().y() - 40);
                        m->setRegalo(2);
                    }
                    else if(m->getRegalo() == 2)
                    {
                        sonidos->reproducirMoneda();
                    }
                    else if(m->getRegalo() == 3)
                    {
                        hongo->setPos(m->pos().x(), m->pos().y() - 40);
                        m->setRegalo(2);
                    }
                }
                else if(personajeSmall->estarTocandoPlataforma(m))
                {
                    p->setVel(p->getVelX(), -1*(0.1)*p->getVelY(), p->getPosX(), nivelTierra - m->pos().y() + personajeSmall->boundingRect().height());
                    salto = true;
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
                    salto = true;
                }
            }
            else if(Tubo *t = qgraphicsitem_cast<Tubo*>(item))
            {
                if(personajeSmall->estarTocandoPlataforma(t))
                {
                    p->setVel(p->getVelX(), -1*(0.1)*p->getVelY(), p->getPosX(), nivelTierra - t->pos().y() + personajeSmall->boundingRect().height());
                    salto = true;
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
                    //verifica con que tipo de ladrillo colisiona
                    if(m->getRegalo() == 1)
                    {
                        florFuego->setPos(m->pos().x(), m->pos().y() - 40);
                        m->setRegalo(2);
                    }
                    else if(m->getRegalo() == 2)
                    {
                        sonidos->reproducirMoneda();
                    }
                    else if(m->getRegalo() == 3)
                    {
                        hongo->setPos(m->pos().x(), m->pos().y() - 40);
                        m->setRegalo(2);
                    }
                }
                else if(personaje->estarTocandoPlataforma(m))
                {
                    p->setVel(p->getVelX(), -1*(0.1)*p->getVelY(), p->getPosX(), nivelTierra - m->pos().y() + personaje->boundingRect().height());
                    salto = true;
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
                    salto = true;
                }
            }
            else if(Tubo *t = qgraphicsitem_cast<Tubo*>(item))
            {
                if(personaje->estarTocandoPlataforma(t))
                {
                    p->setVel(p->getVelX(), -1*(0.1)*p->getVelY(), p->getPosX(), nivelTierra - t->pos().y() + personaje->boundingRect().height());
                    salto = true;
                }
                else
                {
                    p->setVel(-1*(0.2)*p->getVelX(),p->getVelY(), p->getPosX(),p->getPosY());
                }
            }
        }
    }
    else if(estado == fire)
    {
        for(QGraphicsItem *item : collidingItems(personajeFire))
        {
            if(LadrilloSorpresa *m = qgraphicsitem_cast<LadrilloSorpresa*>(item))
            {
                if(personajeFire->estarTocandoCabeza(m))
                {
                    p->setVel(p->getVelX(), -1*(0.8)*p->getVelY(),p->getPosX(), p->getPosY());
                    //verifica con que tipo de ladrillo colisiona
                    if(m->getRegalo() == 1)
                    {
                        florFuego->setPos(m->pos().x(), m->pos().y() - 40);
                        m->setRegalo(2);
                    }
                    else if(m->getRegalo() == 2)
                    {
                        sonidos->reproducirMoneda();
                    }
                    else if(m->getRegalo() == 3)
                    {
                        hongo->setPos(m->pos().x(), m->pos().y() - 40);
                        m->setRegalo(2);
                    }
                }
                else if(personajeFire->estarTocandoPlataforma(m))
                {
                    p->setVel(p->getVelX(), -1*(0.1)*p->getVelY(), p->getPosX(), nivelTierra - m->pos().y() + personajeFire->boundingRect().height());
                    salto = true;
                }
            }
            if(Ladrillo *l = qgraphicsitem_cast<Ladrillo*>(item))
            {
                if(personajeFire->estarTocandoCabeza(l))
                {
                    p->setVel(p->getVelX(), -1*(0.8)*p->getVelY(),p->getPosX(), p->getPosY());
                }
                else if(personajeFire->estarTocandoPlataforma(l))
                {
                    p->setVel(p->getVelX(), -1*(0.1)*p->getVelY(), p->getPosX(), nivelTierra - l->pos().y() + personajeFire->boundingRect().height());
                    salto = true;
                }
            }
            else if(Tubo *t = qgraphicsitem_cast<Tubo*>(item))
            {
                if(personajeFire->estarTocandoPlataforma(t))
                {
                    p->setVel(p->getVelX(), -1*(0.1)*p->getVelY(), p->getPosX(), nivelTierra - t->pos().y() + personajeFire->boundingRect().height());
                    salto = true;
                }
                else
                {
                    p->setVel(-1*(0.2)*p->getVelX(),p->getVelY(), p->getPosX(),p->getPosY());
                }
            }
        }
    }
}

void NivelDos::verificarColisionBordes(PersonajeFisica *p)
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
        salto = true;
    }
}

void NivelDos::cambiarDireccionGomba()
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

    for (int i = 0; i < ladrillos.size(); i++)
    {
        for(QGraphicsItem *item : collidingItems(ladrillos.at(i)))
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

void NivelDos::actualizar()
{
    verificarColisionAyudas();
    if(estado == small)
    {
        personajeSmall->actualizar(nivelTierra);
        moverJugador();
        verificarColisionEnemigos(personajeSmall->getFisica());
        verificarColisionPlataforma(personajeSmall->getFisica());
        verificarColisionBordes(personajeSmall->getFisica());
    }

    else if(estado == normal)
    {
        personaje->actualizar(nivelTierra);
        moverJugador();
        verificarColisionEnemigos(personajeSmall->getFisica());
        verificarColisionPlataforma(personaje->getFisica());
        verificarColisionBordes(personaje->getFisica());
    }

    else if(estado == fire)
    {
        personajeFire->actualizar(nivelTierra);
        moverJugador();
        verificarColisionEnemigos(personajeSmall->getFisica());
        verificarColisionPlataforma(personajeFire->getFisica());
        verificarColisionBordes(personajeFire->getFisica());
    }

    verificarColisionMoneda();
    cambiarDireccionGomba();
}

void NivelDos::siguienteSprite()
{
    if (estado == small){personajeSmall->siguienteSprite();}
    else if (estado == normal){personaje->siguienteSprite();}
    else if (estado == fire){personajeFire->siguienteSprite();}
}

void NivelDos::moverConMando()
{
    PersonajeFisica *p = personajeSmall->getFisica();
    if(estado == normal){p = personaje->getFisica();}
    else if(estado == fire){p = personajeFire->getFisica();}

    int direccion = 0;
    switch (mando->leerArduino()[0])
    {
    case 'W':
        if(salto)
        {
            p->setVel(p->getVelX(), 250, p->getPosX(), p->getPosY());
            sonidos->reproducirSalto();
            salto = false;
        }
        break;
    case 'D':
        p->setVel(velocidad,p->getVelY(), p->getPosX(), p->getPosY());
        direccion = 1;
        personajeSmall->setDireccion(qBound(-1, direccion, 1));
        personaje->setDireccion(qBound(-1, direccion, 1));
        personajeFire->setDireccion(qBound(-1, direccion, 1));
        checkTimer();
        break;
    case 'A':
        p->setVel(-velocidad,p->getVelY(), p->getPosX(), p->getPosY());
        direccion = -1;
        personajeSmall->setDireccion(qBound(-1, direccion, 1));
        personaje->setDireccion(qBound(-1, direccion, 1));
        personajeFire->setDireccion(qBound(-1, direccion, 1));
        checkTimer();
        break;
    default :
        direccion = 0;
        personajeSmall->setDireccion(qBound(-1, direccion, 1));
        personaje->setDireccion(qBound(-1, direccion, 1));
        personajeFire->setDireccion(qBound(-1, direccion, 1));
        checkTimer();
        break;
    }
}

void NivelDos::keyPressEvent(QKeyEvent *event)
{
    PersonajeFisica *p = personajeSmall->getFisica();
    if(estado == normal){p = personaje->getFisica();}
    else if(estado == fire){p = personajeFire->getFisica();}

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
        if(salto)
        {
            p->setVel(p->getVelX(), 250, p->getPosX(), p->getPosY());
            sonidos->reproducirSalto();
            salto = false;
        }
        break;
    case Qt::Key_M:
        mando = new AdministradorArduino();
        if(mando->getEstado())
        {
            timerMando->start(200);
        }
        break;
    }
}

void NivelDos::keyReleaseEvent(QKeyEvent *event)
{
    switch (event->key())
    {
    case Qt::Key_Right:
        if (event->isAutoRepeat()) {return;}
        agregarEntradaHorizontal(0);
        break;
    case Qt::Key_Left:
        if (event->isAutoRepeat()) {return;}
        agregarEntradaHorizontal(0);
        break;

    default:
        break;
    }
}
