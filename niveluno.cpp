#include "niveluno.h"

NivelUno::NivelUno(QObject *padre):
    QGraphicsScene(0,0,6600,720,padre)
  , anchoEscena(6600)
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
  , velocidad(50)
  , hongo(nullptr)
  , florFuego(nullptr)
{
    //inicilizamos el mando
    mando = new AdministradorArduino();
    mandoImagen = new QGraphicsPixmapItem(QPixmap(":/Imagenes/control.png"));
    mandoImagen->setPos(1280- mandoImagen->boundingRect().width(), 10);

    sonidos = new AdministradorSonidos();

    //inicializamos timer
    timerSprite = new QTimer(this);
    connect(timerSprite, SIGNAL(timeout()), this, SLOT(siguienteSprite()));

    timerEscena = new QTimer(this);
    connect(timerEscena, SIGNAL(timeout()), this, SLOT(correrEscena()));

    timerMando = new QTimer(this);
    connect(timerMando, SIGNAL(timeout()), this, SLOT(moverConMando()));

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(actualizar()));

    setSceneRect(0,0,1280,720);

    //Agregamos el cielo
    cielo1 = new BackgroundItem(QPixmap(":/Imagenes/1-1.png"));
    addItem(cielo1);
    cielo2 = new BackgroundItem(QPixmap(":Imagenes/1-2.png"));
    addItem(cielo2);
    cielo3 = new BackgroundItem(QPixmap(":Imagenes/1-3.png"));
    addItem(cielo3);
    cielo4 = new BackgroundItem(QPixmap(":Imagenes/1-4.png"));
    addItem(cielo4);
    cielo5 = new BackgroundItem(QPixmap(":Imagenes/1-5.png"));
    addItem(cielo5);
    cielo6 = new BackgroundItem(QPixmap(":Imagenes/1-6.png"));
    addItem(cielo6);
    cielo7 = new BackgroundItem(QPixmap(":Imagenes/1-7.png"));
    addItem(cielo7);

    //Agregamos puntaje
    puntajeLogo = new BackgroundItem(QPixmap(":/Imagenes/puntaje.png"));
    addItem(puntajeLogo);
    puntaje = new Puntaje();
    addItem(puntaje);

    //Agregamos el piso
    tierra = new BackgroundItem(QPixmap(":Imagenes/1-8.png"));
    addItem(tierra);

    //Agregamos castillo
    castillo = new Castillo();
    addItem(castillo);

    //Agregamos bandera
    tuboBandera = new QGraphicsPixmapItem(QPixmap(":/Imagenes/tuboBandera.png"));
    bandera = new Bandera();
    addItem(bandera);
    addItem(tuboBandera);

    //Agregamos hongos
    hongo = new Hongo();
    addItem(hongo);

    //Agregamos flor de bonus
    florFuego = new FlorFuego();
    addItem(florFuego);

    //Agregamos personaje
    personaje =  new Personaje(1);
    addItem(personaje);
    personajeFire = new Personaje(3);
    addItem(personajeFire);
    personajeSmall = new Personaje(2);
    addItem(personajeSmall);
}

NivelUno::~NivelUno()
{
    qDebug() << "1";
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
    delete castillo;
    delete tuboBandera;
    delete bandera;

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

int NivelUno::getPuntaje()
{
    return puntaje->getPuntaje();
}

void NivelUno::reiniciarEscenaUno()
{
    nivel = uno;

    puntaje->setPuntaje(0);

    //iniciamos los timer
    sonidos->reproducirLevel1();
    timerEscena->start(100);
    timer->start(10);

    //Ponemos posicion incial del cielo
    cielo1->setPos(0,-100);
    cielo2->setPos(0,0);
    cielo3->setPos(0,0);
    cielo4->setPos(0,0);
    cielo5->setPos(0,-90);
    cielo6->setPos(0,-90);
    cielo7->setPos(0,-170);
    cielo7->show();

    //Ponemos posicion incial del puntaje
    puntajeLogo->setPos(50,40);
    puntaje->setPos(puntajeLogo->pos().x() + puntajeLogo->boundingRect().width() , 25);

    tierra->setPos(0,-183);

    //Agregamos ladrillos
    int posLadrillo[30][3] = {{550,500,1}, {650,500,1}, {750,500,1}, {650,300,1}, {1150,400,2}, {1350,500,2}, {1350,200,6}, {2150,450,1}
                             , {2250,450,1}, {3050,610,4}, {3100,560,3}, {3150,510,2}, {3200,460,1}, {3425,460,1}, {3425,510,2}, {3425,560,3}
                             , {3425,610,4}, {4000,500,1}, {4100,500,3}, {4100,300,1}, {4250,200,6}, {4650,200,1}, {4850,200,1}, {5400,610,7}
                             , {5450,560,6}, {5500,510,5}, {5550,460,4}, {5600,410,3}, {5650,360,2}, {5700,310,1}};
    int posLadrilloSorpresa[4][2] = {{600,500}, {700,500}, {2200,450}, {4050,500}};
    for (int i = 0; i < 30; i++)
    {
        ladrillos.at(i)->setPos(posLadrillo[i][0],posLadrillo[i][1]);
    }
    for (int j = 0; j < 4; j++)
    {
        ladrillosSorpresa.at(j)->setPos(posLadrilloSorpresa[j][0],posLadrilloSorpresa[j][1]);
        if(j == 0){ladrillosSorpresa.at(j)->setRegalo(3);}
        else if(j == 1){ladrillosSorpresa.at(j)->setRegalo(1);}
        else {ladrillosSorpresa.at(j)->setRegalo(2);}
    }

    castillo->setPos(6200,nivelTierra - castillo->boundingRect().height());
    tuboBandera->setPos(5900, nivelTierra - tuboBandera->boundingRect().height());
    bandera->setPos(5985, tuboBandera->boundingRect().height() - 100);

    //Agregamos monedas
    int posMonedas[24][2] ={{550,450}, {600,450}, {650,450}, {700,450}, {750,450}, {650,250}, {1150,350}, {1200,350}, {1350,150}, {1400,150}
                         , {1450,150}, {1500,150}, {1550,150}, {1600,150}, {2750,500},{2800,500}, {2850,500}, {2900,500}, {2950,500}, {3000,500}, {2950,450}
                         , {2950,550}, {2900,400}, {2900,600}};
    for (int i= 0; i < 24;i++)
    {
        monedas.at(i)->setPos(posMonedas[i][0], posMonedas[i][1]);
    }

    hongo->setPos(-500, -500);
    florFuego->setPos(-500,-500);

    //Agregamos tubos
    int posTubos[7] = {900, 1500, 2000, 2500, 3295, 4600, 4700};
    for (int i = 0; i < 7; i++)
    {
        tubos.at(i)->setPos(posTubos[i], nivelTierra - tubos.at(i)->boundingRect().height());
    }

    //Agregamos flor carnobora
    int posFloresCar[4] = {1475, 3270, 4575, 4675};
    for (int i = 0; i < 4; i++)
    {
        floresCar.at(i)->setPos(posFloresCar[i], tubos.at(1)->pos().y() - floresCar.at(i)->boundingRect().height());
    }

    //Agregamos enemigo Goomba
    int posGombas[10] = {800, 1000, 1600, 1800, 2100, 2200, 2300, 2400, 3300, 3700};
    for (int i = 0; i < 10; i++)
    {
        gombas.at(i)->setPos(posGombas[i], nivelTierra - gombas.at(i)->boundingRect().height());
    }

    desplazamientoMundo = 0;

    personaje->setPos(-1000,-1000);
    personajeFire->setPos(-1000,-1000);

    minX = personajeSmall->boundingRect().width();
    maxX = anchoEscena - personajeSmall->boundingRect().width() / 2;
    personajeSmall->setPos(0,720);
    PersonajeFisica *p = personajeSmall->getFisica();
    p->setVel(0,0,0,720);
    posicionX = minX;
    estado = small;

    desplazamientoMundo = 0;
}

void NivelUno::reiniciarEscenaDos(int _puntaje)
{
    nivel = dos;

    //conserva puntaje
    puntaje->setPuntaje(_puntaje);

    sonidos->reproducirLevel2();
    timerEscena->start(100);
    timer->start(10);

    //Ponemos posicion incial del cielo
    cielo1->setPos(0,0);
    cielo2->setPos(0,0);
    cielo3->setPos(0,0);
    cielo4->setPos(0,0);
    cielo5->setPos(0,0);
    cielo6->setPos(0,0);

    //Ponemos posicion incial del puntaje
    puntajeLogo->setPos(50,40);
    puntaje->setPos(puntajeLogo->pos().x() + puntajeLogo->boundingRect().width() , 25);

    //nivel de la tierra
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
        ladrillos.at(i)->setPos(posLadrillo[i][0],posLadrillo[i][1]);
    }
    for (int j = 0; j < 4; j++)
    {
        ladrillosSorpresa.at(j)->setPos(posLadrilloSorpresa[j][0],posLadrilloSorpresa[j][1]);
        if(j == 0){ladrillosSorpresa.at(j)->setRegalo(3);}
        else if(j == 1){ladrillosSorpresa.at(j)->setRegalo(1);}
        else {ladrillosSorpresa.at(j)->setRegalo(2);}
    }

    castillo->setPos(7800,nivelTierra - castillo->boundingRect().height());
    tuboBandera->setPos(7500, nivelTierra - tuboBandera->boundingRect().height());
    bandera->setPos(7585, tuboBandera->boundingRect().height() - 100);

    //Agregamos fantasmas
    int posFantasmas[18][2] ={{2200,550},{2400,550},{2600,550},{2800,550},{2200,400},{2400,400},{2600,400}
                             ,{2800,400},{5350,550},{5550,550},{5750,550},{5950,550},{6150,550},{5350,400}
                              ,{5550,400},{5750,400},{5950,400},{6150,400}};
    for (int i= 0; i < 18;i++)
    {
        fantasmas.at(i)->setPos(posFantasmas[i][0], posFantasmas[i][1]);
    }

    //Agregamos ladrillos de notas musicales
    int posLadrillonNota[18][3] = {{2200,500,2},{2400,500,2},{2600,500,2},{2800,500,2},{2200,350,2},{2400,350,2}
                                  ,{2600,350,2},{2800,350,2},{5350,500,2},{5550,500,2},{5750,500,2},{5950,500,2}
                                   ,{6150,500,2},{5350,350,2},{5550,350,2},{5750,350,2},{5950,350,2},{6150,350,2}};
    for (int i = 0; i < 18; i++)
    {
        ladrillosNota.at(i)->setPos(posLadrillonNota[i][0],posLadrillonNota[i][1]);
    }

    //Agregamos monedas
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
    for (int i= 0; i < 80;i++)
    {
        monedas.at(i)->setPos(posMonedas[i][0], posMonedas[i][1]);
    }

    hongo->setPos(-500, -500);
    florFuego->setPos(-500,-500);

    //Agregamos tubos
    int posTubos[20] = {400,500,600,700,800,900,1450,2000,3000,3550,4450,4550,4650,4750,4850,4950,5050,5150,5250
                       ,6350};
    for (int i = 0; i < 20; i++)
    {
        tubos.at(i)->setPos(posTubos[i], nivelTierra - tubos.at(i)->boundingRect().height());
    }

    //Agregamos flor carnobora
    int posFloresCar[17] = {375,475,575,675,775,875,1425,2975,4425,4525,4625,4725,4825,4925,5025,5125,5225};
    for (int i = 0; i < 17; i++)
    {
        floresCar.at(i)->setPos(posFloresCar[i], tubos.at(1)->pos().y() - floresCar.at(i)->boundingRect().height());
    }

    //Agregamos enemigo Goomba
    int posGombas[47] = {1050,1100,1150,1200,1300,1350,1400,1475,1525,1625,1675,1725
                        ,1775,1875,1925,1975,2125,2175,2275,2325,2425
                         ,2525,2575,2675,2775,3025,3075,3175,3275,3325
                         ,3375,3525,5300,5350,5450,5500,5600,5650,5700,5750
                        ,5800,5900,5950,6000,6100,6150,6250};
    for (int i = 0; i < 47; i++)
    {
        gombas.at(i)->setPos(posGombas[i], nivelTierra - gombas.at(i)->boundingRect().height());
    }

    desplazamientoMundo = 0;

    personaje->setPos(-1000,-1000);
    personajeFire->setPos(-1000,-1000);

    minX = personajeSmall->boundingRect().width();
    maxX = anchoEscena - personajeSmall->boundingRect().width() / 2;
    personajeSmall->setPos(0,720);
    PersonajeFisica *p = personajeSmall->getFisica();
    p->setVel(0,0,0,720);
    posicionX = minX;
    estado = small;

    desplazamientoMundo = 0;
}

void NivelUno::agregarEntradaHorizontal(int entrada)
{
    personajeSmall->setDireccion(qBound(-1, entrada, 1));
    personaje->setDireccion(qBound(-1, entrada, 1));
    personajeFire->setDireccion(qBound(-1, entrada, 1));
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

void NivelUno::verificarColisionCastillo()
{
    if(estado == small)
    {
        if(personajeSmall->collidesWithItem(castillo))
        {
            if(castillo->estarTocandoPuerta(personajeSmall))
            {
                if(nivel == uno){enviarFinalizarUno();}
                else if(nivel == dos){enviarFinalizarDos();}
            }
        }
    }
    else if(estado == normal)
    {
        if(personaje->collidesWithItem(castillo))
        {
            if(castillo->estarTocandoPuerta(personaje))
            {
                if(nivel == uno){enviarFinalizarUno();}
                else if(nivel == dos){enviarFinalizarDos();}
            }
        }
    }
    else if(estado == fire)
    {
        if(personajeFire->collidesWithItem(castillo))
        {
            if(castillo->estarTocandoPuerta(personajeFire))
            {
                if(nivel == uno){enviarFinalizarUno();}
                else if(nivel == dos){enviarFinalizarDos();}
            }
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
                m->setPos(-1000,1000);
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
                m->setPos(-1000,1000);
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
                m->setPos(-1000,1000);
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
                    p->setVel(p->getVelX(), -1*(0.8)*p->getVelY(), p->getPosX(), nivelTierra - m->pos().y() + personajeSmall->boundingRect().height());
                    m->setPos(-1000,1000);
                }
                else
                {
                    timer->stop();
                    m->setPos(-1000,1000);
                    sonidos->reproducirMuerto1();
                    enviarReiniciar();
                }
            }
        }
        for(QGraphicsItem *item : collidingItems(personajeSmall))
        {
            if(Flor *m = qgraphicsitem_cast<Flor*>(item))
            {
                timer->stop();
                m->setPos(-1000,1000);
                sonidos->reproducirMuerto1();
                enviarReiniciar();
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
                    p->setVel(p->getVelX(), -1*(0.8)*p->getVelY(), p->getPosX(), nivelTierra - m->pos().y() + personaje->boundingRect().height());
                    m->setPos(-1000,1000);
                }
                else
                {
                    //camiar de personaje
                    estado = small;
                    sonidos->reproducirGolpe();
                    PersonajeFisica *p = personajeSmall->getFisica();
                    PersonajeFisica *s = personaje->getFisica();
                    p->setVel(s->getVelX(), s->getVelY(), s->getPosX(), s->getPosY());
                    p->setVel(p->getVelX(), 400, p->getPosX(), nivelTierra - m->pos().y() + 20);
                    personaje->setPos(-1000,-1000);
                }
            }
        }
        for(QGraphicsItem *item : collidingItems(personaje))
        {
            if(Flor *m = qgraphicsitem_cast<Flor*>(item))
            {
                //camiar de personaje
                estado = small;
                sonidos->reproducirGolpe();
                PersonajeFisica *p = personajeSmall->getFisica();
                PersonajeFisica *s = personaje->getFisica();
                p->setVel(s->getVelX(), s->getVelY(), s->getPosX(), s->getPosY());
                p->setVel(p->getVelX(), 400, p->getPosX(), nivelTierra - m->pos().y() + 20);
                personaje->setPos(-1000,-1000);
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
                    p->setVel(p->getVelX(), -1*(0.8)*p->getVelY(), p->getPosX(), nivelTierra - m->pos().y() + personajeFire->boundingRect().height());
                    m->setPos(-1000,1000);
                }
                else
                {
                    //camiar de personaje
                    estado = normal;
                    sonidos->reproducirGolpe();
                    PersonajeFisica *p = personaje->getFisica();
                    PersonajeFisica *s = personajeFire->getFisica();
                    p->setVel(s->getVelX(), s->getVelY(), s->getPosX(), s->getPosY());
                    p->setVel(p->getVelX(), 400, p->getPosX(), nivelTierra - m->pos().y() + 20);
                    personajeFire->setPos(-1000,-1000);
                }
            }
        }
        for(QGraphicsItem *item : collidingItems(personajeFire))
        {
            if(Flor *m = qgraphicsitem_cast<Flor*>(item))
            {
                //camiar de personaje
                estado = normal;
                sonidos->reproducirGolpe();
                PersonajeFisica *p = personaje->getFisica();
                PersonajeFisica *s = personajeFire->getFisica();
                p->setVel(s->getVelX(), s->getVelY(), s->getPosX(), s->getPosY());
                p->setVel(p->getVelX(), 400, p->getPosX(), nivelTierra - m->pos().y() + 20);
                personajeFire->setPos(-1000,-1000);
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
                        m->setRegalo(0);
                        puntaje->incrementar();
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
                    p->setCd(5);
                    p->setVel(p->getVelX(), -1*(0.1)*p->getVelY(), p->getPosX(), nivelTierra - l->pos().y() + personajeSmall->boundingRect().height());
                    salto = true;
                }
                else if(personajeSmall->estarTocandoR(l))
                {
                    p->setVel(0,-1*(0.2)*p->getVelY(),l->pos().x() + l->boundingRect().width() + personajeSmall->boundingRect().width(),p->getPosY());
                }
                else if(personajeSmall->estarTocandoL(l))
                {
                    p->setVel(0,-1*(0.2)*p->getVelY(),l->pos().x() - personajeSmall->boundingRect().width(),p->getPosY());
                }
            }
            else if(Tubo *t = qgraphicsitem_cast<Tubo*>(item))
            {
                if(personajeSmall->estarTocandoPlataforma(t))
                {
                    p->setCd(5);
                    p->setVel(p->getVelX(), -1*(0.1)*p->getVelY(), p->getPosX(), nivelTierra - t->pos().y() + personajeSmall->boundingRect().height());
                    salto = true;
                }
                else if(personajeSmall->estarTocandoR(t))
                {
                    p->setVel(0,-1*(0.2)*p->getVelY(),t->pos().x() + t->boundingRect().width() + personajeSmall->boundingRect().width(),p->getPosY());
                }
                else if(personajeSmall->estarTocandoL(t))
                {
                    p->setVel(0,-1*(0.2)*p->getVelY(),t->pos().x() - personajeSmall->boundingRect().width(),p->getPosY());
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
                        m->setRegalo(0);
                        puntaje->incrementar();
                    }
                    else if(m->getRegalo() == 3)
                    {
                        hongo->setPos(m->pos().x(), m->pos().y() - 40);
                        m->setRegalo(2);
                    }
                }
                else if(personaje->estarTocandoPlataforma(m))
                {
                    p->setCd(5);
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
                    p->setCd(5);
                    p->setVel(p->getVelX(), -1*(0.1)*p->getVelY(), p->getPosX(), nivelTierra - l->pos().y() + personaje->boundingRect().height());
                    salto = true;
                }
                else if(personaje->estarTocandoR(l))
                {
                    p->setVel(0,-1*(0.2)*p->getVelY(),l->pos().x() + l->boundingRect().width() + personaje->boundingRect().width(),p->getPosY());
                }
                else if(personaje->estarTocandoL(l))
                {
                    p->setVel(0,-1*(0.2)*p->getVelY(),l->pos().x() - personaje->boundingRect().width(),p->getPosY());
                }
            }
            else if(Tubo *t = qgraphicsitem_cast<Tubo*>(item))
            {
                if(personaje->estarTocandoPlataforma(t))
                {
                    p->setCd(5);
                    p->setVel(p->getVelX(), -1*(0.1)*p->getVelY(), p->getPosX(), nivelTierra - t->pos().y() + personaje->boundingRect().height());
                    salto = true;
                }
                else if(personaje->estarTocandoR(t))
                {
                    p->setVel(0,-1*(0.2)*p->getVelY(),t->pos().x() + t->boundingRect().width() + personaje->boundingRect().width(),p->getPosY());
                }
                else if(personaje->estarTocandoL(t))
                {
                    p->setVel(0,-1*(0.2)*p->getVelY(),t->pos().x() - personaje->boundingRect().width(),p->getPosY());
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
                        m->setRegalo(0);
                        puntaje->incrementar();
                    }
                    else if(m->getRegalo() == 3)
                    {
                        hongo->setPos(m->pos().x(), m->pos().y() - 40);
                        m->setRegalo(2);
                    }
                }
                else if(personajeFire->estarTocandoPlataforma(m))
                {
                    p->setCd(5);
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
                    p->setCd(5);
                    p->setVel(p->getVelX(), -1*(0.1)*p->getVelY(), p->getPosX(), nivelTierra - l->pos().y() + personajeFire->boundingRect().height());
                    salto = true;
                }
                else if(personajeFire->estarTocandoR(l))
                {
                    p->setVel(0,-1*(0.2)*p->getVelY(),l->pos().x() + l->boundingRect().width() + personajeFire->boundingRect().width(),p->getPosY());
                }
                else if(personajeFire->estarTocandoL(l))
                {
                    p->setVel(0,-1*(0.2)*p->getVelY(),l->pos().x() - personajeFire->boundingRect().width(),p->getPosY());
                }
            }
            else if(Tubo *t = qgraphicsitem_cast<Tubo*>(item))
            {
                if(personajeFire->estarTocandoPlataforma(t))
                {
                    p->setCd(5);
                    p->setVel(p->getVelX(), -1*(0.1)*p->getVelY(), p->getPosX(), nivelTierra - t->pos().y() + personajeFire->boundingRect().height());
                    salto = true;
                }
                else if(personajeFire->estarTocandoR(t))
                {
                    p->setVel(0,-1*(0.2)*p->getVelY(),t->pos().x() + t->boundingRect().width() + personajeFire->boundingRect().width(),p->getPosY());
                }
                else if(personajeFire->estarTocandoL(t))
                {
                    p->setVel(0,-1*(0.2)*p->getVelY(),t->pos().x() - personajeFire->boundingRect().width(),p->getPosY());
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
        p->setCd(5);
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

void NivelUno::enviarReiniciar()
{
    sonidos->pararLevel2();
    sonidos->pararLevel1();
    timer->stop();
    timerEscena->stop();
    timerSprite->stop();
    timerMando->stop();

    personaje->setDireccion(0);
    personajeSmall->setDireccion(0);
    personajeFire->setDireccion(0);

    emit repetirNivel();
}

void NivelUno::enviarFinalizarUno()
{
    sonidos->pararLevel2();
    sonidos->pararLevel1();
    timer->stop();
    timerEscena->stop();
    timerSprite->stop();
    timerMando->stop();

    personaje->setDireccion(0);
    personajeSmall->setDireccion(0);
    personajeFire->setDireccion(0);

    emit finalizarNivelUno();
}

void NivelUno::enviarFinalizarDos()
{
    sonidos->pararLevel2();
    sonidos->pararLevel1();
    timer->stop();
    timerEscena->stop();
    timerSprite->stop();
    timerMando->stop();

    personaje->setDireccion(0);
    personajeSmall->setDireccion(0);
    personajeFire->setDireccion(0);

    emit finalizarNivelDos();
}

// se encarga de manejas los sprites de los objetos en escena.
void NivelUno::correrEscena()
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
    bandera->siguienteSprite();

    //mueve los goomba
    for (int i = 0;i < gombas.size(); i++)
    {
        gombas.at(i)->setX(gombas.at(i)->pos().x() + gombas.at(i)->getDireccion() * (-7));
    }

    //verifica si el mando esta activo
    if(mando->getEstado() && !timerMando->isActive())
    {
        timerMando->start(200);
        mandoImagen->show();
    }
    else
    {
        mandoImagen->hide();
    }
}

void NivelUno::aplicarParalelismo(qreal propocion, QGraphicsItem *item)
{
    item->setX(-propocion * (item->boundingRect().width() - width()));
}

//crea valores inciales
void NivelUno::iniciarEscenaUno()
{

    //Agregamos el cielo
    cielo1->setPixmap(QPixmap(":/Imagenes/1-1.png"));
    cielo2->setPixmap(QPixmap(":Imagenes/1-2.png"));
    cielo3->setPixmap(QPixmap(":Imagenes/1-3.png"));
    cielo4->setPixmap(QPixmap(":Imagenes/1-4.png"));
    cielo5->setPixmap(QPixmap(":Imagenes/1-5.png"));
    cielo6->setPixmap(QPixmap(":Imagenes/1-6.png"));
    cielo7->setPixmap(QPixmap(":Imagenes/1-7.png"));

    //Agregamos el piso
    tierra->setPixmap(QPixmap(":Imagenes/1-8.png"));

    //Agregamos ladrillos
    int posLadrillo[30][3] = {{550,500,1}, {650,500,1}, {750,500,1}, {650,300,1}, {1150,400,2}, {1350,500,2}, {1350,200,6}, {2150,450,1}
                             , {2250,450,1}, {3050,610,4}, {3100,560,3}, {3150,510,2}, {3200,460,1}, {3425,460,1}, {3425,510,2}, {3425,560,3}
                             , {3425,610,4}, {4000,500,1}, {4100,500,3}, {4100,300,1}, {4250,200,6}, {4650,200,1}, {4850,200,1}, {5400,610,7}
                             , {5450,560,6}, {5500,510,5}, {5550,460,4}, {5600,410,3}, {5650,360,2}, {5700,310,1}};
    int posLadrilloSorpresa[4][2] = {{600,500}, {700,500}, {2200,450}, {4050,500}};
    for (int i = ladrillos.size() - 1; 0 <= i; i--)
    {
        removeItem(ladrillos.at(i));
    }
    ladrillos.clear();
    for (int i = 0; i < 30; i++)
    {
        ladrillos.append(new Ladrillo(posLadrillo[i][2]));
        ladrillos.last()->setPos(posLadrillo[i][0],posLadrillo[i][1]);
        addItem(ladrillos.last());
    }
    for (int i = ladrillosSorpresa.size() - 1; 0 <= i; i--)
    {
        removeItem(ladrillosSorpresa.at(i));
    }
    ladrillosSorpresa.clear();
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
    for (int i = monedas.size() - 1; 0 <= i; i--)
    {
        removeItem(monedas.at(i));
    }
    monedas.clear();
    for (int i= 0; i < 24;i++)
    {
        monedas.append(new Moneda());
        monedas.last()->setPos(posMonedas[i][0], posMonedas[i][1]);
        addItem(monedas.last());
    }

    //Agregamos tubos
    int posTubos[7] = {900, 1500, 2000, 2500, 3295, 4600, 4700};
    for (int i = tubos.size() - 1; 0 <= i; i--)
    {
        removeItem(tubos.at(i));
    }
    tubos.clear();
    for (int i = 0; i < 7; i++)
    {
        tubos.append(new Tubo());
        tubos.last()->setPos(posTubos[i], nivelTierra - tubos.last()->boundingRect().height());
        addItem(tubos.last());
    }

    //Agregamos flor carnobora
    int posFloresCar[4] = {1475, 3270, 4575, 4675};
    for (int i = floresCar.size() - 1; 0 <= i; i--)
    {
        removeItem(floresCar.at(i));
    }
    floresCar.clear();
    for (int i = 0; i < 4; i++)
    {
        floresCar.append(new Flor());
        floresCar.last()->setPos(posFloresCar[i], tubos.at(1)->pos().y() - floresCar.last()->boundingRect().height());
        addItem(floresCar.last());
    }

    //Agregamos enemigo Goomba
    int posGombas[10] = {800, 1000, 1600, 1800, 2100, 2200, 2300, 2400, 3300, 3700};
    for (int i = gombas.size() - 1 ; 0 <= i; i--)
    {
        removeItem(gombas.at(i));
    }
    gombas.clear();
    for (int i = 0; i < 10; i++)
    {
        gombas.append(new Goomba());
        gombas.last()->setPos(posGombas[i], nivelTierra - gombas.last()->boundingRect().height());
        addItem(gombas.last());
    }
}

void NivelUno::iniciarEscenaDos()
{
    //Cambiamos el fondo
    cielo1->setPixmap(QPixmap(":Imagenes/2-1.png"));
    cielo1->setPos(0,0);
    cielo2->setPixmap(QPixmap(":Imagenes/2-2.png"));
    cielo2->setPos(0,0);
    cielo3->setPixmap(QPixmap(":Imagenes/2-3.png"));
    cielo3->setPos(0,0);
    cielo4->setPixmap(QPixmap(":Imagenes/2-4.png"));
    cielo4->setPos(0,0);
    cielo5->setPixmap(QPixmap(":Imagenes/2-5.png"));
    cielo5->setPos(0,0);
    cielo6->setPixmap(QPixmap(":Imagenes/2-6.png"));
    cielo6->setPos(0,0);
    cielo7->hide();
    tierra->setPixmap(QPixmap(":Imagenes/2-7.png"));
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
    for (int i = ladrillos.size() - 1; 0 <= i; i--)
    {
        removeItem(ladrillos.at(i));
    }
    ladrillos.clear();
    for (int i = 0; i < 74; i++)
    {
        ladrillos.append(new Ladrillo(posLadrillo[i][2]));
        ladrillos.last()->setPos(posLadrillo[i][0],posLadrillo[i][1]);
        addItem(ladrillos.last());
    }
    for (int i = ladrillosSorpresa.size() - 1; 0 <= i; i--)
    {
        removeItem(ladrillosSorpresa.at(i));
    }
    ladrillosSorpresa.clear();
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
    for (int i = fantasmas.size() - 1; 0 <= i; i--)
    {
        removeItem(fantasmas.at(i));
    }
    fantasmas.clear();
    for (int i= 0; i < 18;i++)
    {
        fantasmas.append(new Fantasma());
        fantasmas.last()->setPos(posFantasmas[i][0], posFantasmas[i][1]);
        addItem(fantasmas.last());
    }

    //Agregamos ladrillos de notas musicales
    int posLadrillonNota[18][3] = {{2200,500,2},{2400,500,2},{2600,500,2},{2800,500,2},{2200,350,2},{2400,350,2}
                                  ,{2600,350,2},{2800,350,2},{5350,500,2},{5550,500,2},{5750,500,2},{5950,500,2}
                                   ,{6150,500,2},{5350,350,2},{5550,350,2},{5750,350,2},{5950,350,2},{6150,350,2}};
    for (int i = ladrillosNota.size() - 1; 0 <= i; i--)
    {
        removeItem(ladrillosNota.at(i));
    }
    ladrillosNota.clear();
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
    for (int i = monedas.size() - 1; 0 <= i; i--)
    {
        removeItem(monedas.at(i));
    }
    monedas.clear();
    for (int i= 0; i < 80; i++)
    {
        monedas.append(new Moneda());
        monedas.last()->setPos(posMonedas[i][0], posMonedas[i][1]);
        addItem(monedas.last());
    }

    //Agregamos tubos
    int posTubos[20] = {400,500,600,700,800,900,1450,2000,3000,3550,4450,4550,4650,4750,4850,4950,5050,5150,5250
                       ,6350};
    for (int i = tubos.size() - 1; 0 <= i; i--)
    {
        removeItem(tubos.at(i));
    }
    tubos.clear();
    for (int i = 0; i < 20; i++)
    {
        tubos.append(new Tubo());
        tubos.last()->setPos(posTubos[i], nivelTierra - tubos.last()->boundingRect().height());
        addItem(tubos.last());
    }

    //Agregamos flor carnobora
    int posFloresCar[17] = {375,475,575,675,775,875,1425,2975,4425,4525,4625,4725,4825,4925,5025,5125,5225};
    for (int i = floresCar.size() - 1; 0 <= i; i--)
    {
        removeItem(floresCar.at(i));
    }
    floresCar.clear();
    for (int i = 0; i < 17; i++)
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
    for (int i = gombas.size() - 1 ; 0 <= i; i--)
    {
        removeItem(gombas.at(i));
    }
    gombas.clear();
    for (int i = 0; i < 47; i++)
    {
        gombas.append(new Goomba());
        gombas.last()->setPos(posGombas[i], nivelTierra - gombas.last()->boundingRect().height());
        addItem(gombas.last());
    }
}

//cambiar posicion actual del personaje
void NivelUno::actualizar()
{
    verificarColisionAyudas();
    if(estado == small)
    {
        personajeSmall->actualizar(nivelTierra);
        moverJugador();
        verificarColisionCastillo();
        verificarColisionEnemigos(personajeSmall->getFisica());
        verificarColisionPlataforma(personajeSmall->getFisica());
        verificarColisionBordes(personajeSmall->getFisica());
    }

    else if(estado == normal)
    {
        personaje->actualizar(nivelTierra);
        moverJugador();
        verificarColisionCastillo();
        verificarColisionEnemigos(personajeSmall->getFisica());
        verificarColisionPlataforma(personaje->getFisica());
        verificarColisionBordes(personaje->getFisica());
    }

    else if(estado == fire)
    {
        personajeFire->actualizar(nivelTierra);
        moverJugador();
        verificarColisionCastillo();
        verificarColisionEnemigos(personajeSmall->getFisica());
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
    if((personaje->pos().x() >= 1035 && personaje->getDireccion()  == 1) ||
       (personajeSmall->pos().x() >= 1035 && personajeSmall->getDireccion()  == 1) ||
       (personajeFire->pos().x() >= 1035 && personajeFire->getDireccion()  == 1))
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

        //mover castillo
        castillo->setX(-dx + castillo->pos().x());
        tuboBandera->setX(-dx + tuboBandera->pos().x());
        bandera->setX(-dx + bandera->pos().x());

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

    switch (mando->leerArduino()[0])
    {
    case 'W':
        if(salto)
        {
            p->setCd(1);
            p->setVel(p->getVelX(), 250, p->getPosX(), p->getPosY());
            sonidos->reproducirSalto();
            salto = false;
        }
        break;
    case 'D':
        p->setVel(velocidad,p->getVelY(), p->getPosX(), p->getPosY());
        agregarEntradaHorizontal(1);
        break;
    case 'A':
        p->setVel(-velocidad,p->getVelY(), p->getPosX(), p->getPosY());
        agregarEntradaHorizontal(-1);
        break;
    default :
        agregarEntradaHorizontal(0);
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
    case Qt::Key_D:
        p->setVel(velocidad,p->getVelY(), p->getPosX(), p->getPosY());
        if (event->isAutoRepeat()){return;}
        agregarEntradaHorizontal(1);
        break;
    case Qt::Key_A:
        p->setVel(-velocidad,p->getVelY(), p->getPosX(), p->getPosY());
        if (event->isAutoRepeat()){return;}
        agregarEntradaHorizontal(-1);
        break;
    case Qt::Key_W:
        if(salto)
        {
            p->setCd(1);
            p->setVel(p->getVelX(), 250, p->getPosX(), p->getPosY());
            sonidos->reproducirSalto();
            salto = false;
        }
        break;
    }
}

void NivelUno::keyReleaseEvent(QKeyEvent *event)
{
    switch (event->key())
    {
    case Qt::Key_D:
        if (event->isAutoRepeat()) {return;}
        agregarEntradaHorizontal(0);
        break;
    case Qt::Key_A:
        if (event->isAutoRepeat()) {return;}
        agregarEntradaHorizontal(0);
        break;

    default:
        break;
    }
}
