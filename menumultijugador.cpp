#include "menumultijugador.h"

MenuMultijugador::MenuMultijugador(QWidget *parent) :
    QWidget(parent)
  , turno(player1) , nivelJugador1(1), nivelJugador2(1), puntajeJugador1(0), puntajeJugador2(0)
  , vidasJugador1(5), vidasJugador2(5)
{
    inicializarEscena();
}

MenuMultijugador::~MenuMultijugador()
{
    delete escena;
    delete view;

    delete nivelUno;
}

void MenuMultijugador::inicializarEscena()
{
    escena = new QGraphicsScene();

    view = new QGraphicsView();
    view->setRenderHint(QPainter::Antialiasing);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setScene(escena);
    view->setFixedSize(1280,720);

    view->setScene(escena);

    nivelUno = new NivelUno;
    view->setScene(nivelUno);
    nivelUno->iniciarEscenaUno();

    connect(this->nivelUno, SIGNAL(repetirNivel()), this, SLOT(cambiarTurnoJugador()));
    connect(this->nivelUno, SIGNAL(finalizarNivelUno()), this, SLOT(finalizarNivelUno()));
    connect(this->nivelUno, SIGNAL(finalizarNivelDos()), this, SLOT(finalizarNivelDos()));
}

void MenuMultijugador::correrJuego()
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
        if(nivelJugador2 == 2 && nivelJugador1 == 1)
        {
            nivelUno->iniciarEscenaUno();
        }
        else if(nivelJugador2 == 1 && nivelJugador1 == 2)
        {
            nivelUno->iniciarEscenaDos();
        }
    }
    else if(turno == player2)
    {
        vidasJugador2 -= 1;
        turno = player1;
        if(nivelJugador1 == 2 && nivelJugador2 == 1)
        {
            nivelUno->iniciarEscenaUno();
        }
        else if(nivelJugador1 == 1 && nivelJugador2 == 2)
        {
            nivelUno->iniciarEscenaDos();
        }
    }
    correrJuego();
}

void MenuMultijugador::comenzarNivelUno()
{
    if(turno == player1)
    {
        nivelUno->reiniciarEscenaUno(1);
    }
    else if(turno == player2)
    {
        nivelUno->reiniciarEscenaUno(2);
    }
    view->show();
}

void MenuMultijugador::comenzarNivelDos()
{
    if(turno == player1)
    {
        nivelUno->reiniciarEscenaDos(puntajeJugador1, 1);
        nivelJugador1 = 2;
    }
    else if(turno == player2)
    {
       nivelUno->reiniciarEscenaDos(puntajeJugador2, 2);
       nivelJugador2 = 2;
    }
    view->show();
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
    nivelUno->iniciarEscenaDos();
    comenzarNivelDos();
}

void MenuMultijugador::finalizarNivelDos()
{
    if(turno == player1)
    {
        puntajeJugador1 = nivelUno->getPuntaje();
    }
    else if(turno == player2)
    {
        puntajeJugador2 = nivelUno->getPuntaje();
    }
    //mostrar widget con puntaje y vidas CONGRATULATIONS!
}
