#include "niveluno.h"

NivelUno::NivelUno(QObject *padre):
    QGraphicsScene(0,0,8000,720,padre)
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
  , cielo7(nullptr)
  , tierra(nullptr)
  , nivelTierra(660)
  , entradaHorizontal(0)
  , velocidad(50)
  , hongo(nullptr)
  , florFuego(nullptr)
{
    iniciarEscena();

    sonidos = new AdministradorSonidos();

    timerSprite = new QTimer(this);
    connect(timerSprite, SIGNAL(timeout()), this, SLOT(siguienteSprite()));

    timerMando = new QTimer(this);
    connect(timerMando, SIGNAL(timeout()), this, SLOT(moverConMando()));

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(actualizar()));
    timer->start(10);
}

NivelUno::~NivelUno()
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
    delete cielo7;
    delete tierra;

    delete hongo;
    delete florFuego;

    delete puntaje;
    delete puntajeLogo;

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
    personajeSmall->setDireccion(qBound(-1, entradaHorizontal, 1));
    personaje->setDireccion(qBound(-1, entradaHorizontal, 1));
    personajeFire->setDireccion(qBound(-1, entradaHorizontal, 1));
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

void NivelUno::verificarColisionAyudas()
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
                    removeItem(m);
                    p->setVel(p->getVelX(), -1*(0.8)*p->getVelY(), p->getPosX(), nivelTierra - m->pos().y() + personajeSmall->boundingRect().height());
                }
                else
                {
                    sonidos->reproducirMuerto();
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
        salto = true;
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

    for (int i = 10; i < ladrillos.size(); i++)
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

    //Agregamos puntaje
    puntajeLogo = new BackgroundItem(QPixmap(":/Imagenes/puntaje.png"));
    puntajeLogo->setPos(50,40);
    addItem(puntajeLogo);
    puntaje = new Puntaje();
    puntaje->setPos(puntajeLogo->pos().x() + puntajeLogo->boundingRect().width() , 25);
    addItem(puntaje);

    //Agregamos el piso
    tierra = new BackgroundItem(QPixmap(":Imagenes/1-8.png"));
    addItem(tierra);
    tierra->setPos(0,-183);


    //Agregamos ladrillos
    int posLadrillo[30][3] = {{550,500,1}, {650,500,1}, {750,500,1}, {650,300,1}, {1150,400,2}, {1350,500,2}, {1350,200,6}, {2150,450,1}
                             , {2250,450,1}, {3050,610,4}, {3100,560,3}, {3150,510,2}, {3200,460,1}, {3425,460,1}, {3425,510,2}, {3425,560,3}
                             , {3425,610,4}, {4000,500,1}, {4100,500,3}, {4100,300,1}, {4250,200,6}, {4650,200,1}, {4850,200,1}, {5400,610,7}
                             , {5450,560,6}, {5500,510,5}, {5550,460,4}, {5600,410,3}, {5650,360,2}, {5700,310,1}};
    int posLadrilloSorpresa[4][2] = {{600,500}, {700,500}, {2200,450}, {4050,500}};
    for (int i = 0; i < 30; i++)
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

    //Agregamos hongos
    hongo = new Hongo();
    hongo->setPos(-500, -500);
    addItem(hongo);

    //Agregamos flor de bonus
    florFuego = new FlorFuego();
    florFuego->setPos(-500,-500);
    addItem(florFuego);

    //Agregamos tubos
    int posTubos[7] = {900, 1500, 2000, 2500, 3275, 4600, 4700};
    for (int i = 0; i < 7; i++)
    {
        tubos.append(new Tubo());
        tubos.last()->setPos(posTubos[i], nivelTierra - tubos.last()->boundingRect().height());
        addItem(tubos.last());
    }

    //Agregamos flor carnobora
    int posFloresCar[4] = {1475, 3250, 4575, 4675};
    for (int i = 0; i < 4; i++)
    {
        floresCar.append(new Flor());
        floresCar.last()->setPos(posFloresCar[i], tubos.at(1)->pos().y() - floresCar.last()->boundingRect().height());
        addItem(floresCar.last());
    }

    //Agregamos enemigo Goomba
    int posGombas[10] = {800, 1000, 1600, 1800, 2100, 2200, 2300, 2400, 3300, 3700};
    for (int i = 0; i < 10; i++)
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

//cambiar posicion actual del personaje
void NivelUno::actualizar()
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
        verificarColisionEnemigos(personaje->getFisica());
        verificarColisionPlataforma(personaje->getFisica());
        verificarColisionBordes(personaje->getFisica());
    }

    else if(estado == fire)
    {
        personajeFire->actualizar(nivelTierra);
        moverJugador();
        verificarColisionEnemigos(personajeFire->getFisica());
        verificarColisionPlataforma(personajeFire->getFisica());
        verificarColisionBordes(personajeFire->getFisica());
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

            //mover hongo
            hongo->setX(-dx + hongo->pos().x());

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
    else if (estado == fire){personajeFire->siguienteSprite();}
}

void NivelUno::moverConMando()
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

void NivelUno::keyPressEvent(QKeyEvent *event)
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
