#include "menumultijugador.h"
#include "ui_menumultijugador.h"

MenuMultijugador::MenuMultijugador(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MenuMultijugador)
{
    ui->setupUi(this);
}

MenuMultijugador::~MenuMultijugador()
{
    delete ui;
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
    else if(turno == player2)
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

void MenuMultijugador::cambiarTurnoJugador() //Cuando el otro muere
{
    if(turno == player1) turno = player2;
    else if(turno == player2) turno = player1;
    correrJuego2();
}

void MenuMultijugador::comenzarNivelUno()
{
    nivelUno = new NivelUno();
    view->setScene(nivelUno);
    view->show();
    connect(this->nivelUno, SIGNAL(cambiarTurnoJugador()), this, SLOT(cambiarTurnoJugador())); //conecta señal de nivel uno con slot de esta clase que llevan igual nombre
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
    connect(this->nivelDos, SIGNAL(cambiarTurnoJugador()), this,SLOT(cambiarTurnoJugador()));
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
