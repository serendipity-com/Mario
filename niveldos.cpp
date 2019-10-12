#include "niveldos.h"


NivelDos::NivelDos(NivelUno *padre) : NivelUno(padre)
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
, entradaHorizontal(0)
, velocidad(50)
, hongo(nullptr)
, florFuego(nullptr)
{
    iniciarEscena();
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
