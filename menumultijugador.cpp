#include "menumultijugador.h"

MenuMultijugador::MenuMultijugador(QWidget *parent) :
    QWidget(parent)
  , turno(player1) , nivelJugador1(1), nivelJugador2(1), puntajeJugador1(0), puntajeJugador2(0)
  , vidasJugador1(5), vidasJugador2(5)
{
    inicializarEscena2();
}

MenuMultijugador::~MenuMultijugador()
{
    delete escena;
    delete view;
}

void MenuMultijugador::inicializarEscena2()
{
    escena = new QGraphicsScene();

    view = new QGraphicsView();
    view->setRenderHint(QPainter::Antialiasing);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setScene(escena);
    view->setFixedSize(1280,720);

    view->setScene(escena);
}

void MenuMultijugador::correrJuego2()
{
    if(turno == player1)
    {
        if(vidasJugador1 >= 1)
        {
            switch(nivelJugador1)
            {
            case 1:
                comenzarNivelUno();
                break;
            case 2:
                comenzarNivelDos();
                break;
            }
        }
    }
    else if(turno == player2)
    {
        if(vidasJugador2 >= 1)
        {
            switch(nivelJugador2)
            {
            case 1:
                comenzarNivelUno();
                break;
            case 2:
                comenzarNivelDos();
                break;
            }
        }
    }
    if((vidasJugador1 < 1) && (vidasJugador2 < 1))
    {
        //Si el número de vidas de ambos es menor a uno, GAME OVER
        view->close();
    }
}

void MenuMultijugador::cambiarTurnoJugador() //Cuando el otro muere
{
    if(turno == player1)
    {
        vidasJugador1 -= 1;
        turno = player2;
    }
    else if(turno == player2)
    {
        vidasJugador2 -= 1;
        turno = player1;
    }
    escena->clear();
    correrJuego2();
}

void MenuMultijugador::comenzarNivelUno()
{
    nivelUno = new NivelUno();
    view->setScene(nivelUno);
    view->show();
    connect(this->nivelUno, SIGNAL(repetirNivel()), this, SLOT(cambiarTurnoJugador())); //conecta señal de nivel uno con slot de esta clase que llevan igual nombre
    connect(this->nivelUno, SIGNAL(finalizarNivelUno()), this,SLOT(finalizarNivelUno()));
}

void MenuMultijugador::comenzarNivelDos()
{
    if(turno == player1)
    {
        nivelDos = new NivelDos(puntajeJugador1);
        nivelJugador1 = 2;
    }
    else if(turno == player2)
    {
       nivelDos = new NivelDos(puntajeJugador2);
       nivelJugador2 = 2;
    }
    view->setScene(nivelDos);
    view->show();
    connect(this->nivelDos, SIGNAL(finalizarNivelDos()), this,SLOT(finalizarNivelDos())); //conecta señal de clase nivelDos con slot de esta clase que tiene el mismo nombre
    connect(this->nivelDos, SIGNAL(repetirNivel()), this,SLOT(cambiarTurnoJugador()));
}

void MenuMultijugador::finalizarNivelUno()
{
    if(turno == player1)
    {
        puntajeJugador1 = nivelUno->getPuntaje();
    }
    else if(turno == player2)
    {
        puntajeJugador2 = nivelUno->getPuntaje();
    }
    escena->clear();
    delete nivelUno;
    comenzarNivelDos();
}

void MenuMultijugador::finalizarNivelDos()
{
    if(turno == player1)
    {
        puntajeJugador1 = nivelDos->getPuntaje();
    }
    else if(turno == player2)
    {
        puntajeJugador2 = nivelDos->getPuntaje();
    }
    escena->clear();
    delete nivelDos;
    //mostrar widget con puntaje y vidas CONGRATULATIONS!
}
