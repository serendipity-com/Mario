#ifndef MENUMULTIJUGADOR_H
#define MENUMULTIJUGADOR_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>

#include "niveluno.h"
#include "niveldos.h"


class MenuMultijugador : public QWidget
{
    Q_OBJECT

public:
    explicit MenuMultijugador(QWidget *parent = nullptr);
    ~MenuMultijugador();
public:
    void correrJuego2(); //porque es llamado desde multiJugador() de Widget.cpp

private:
    void inicializarEscena2();

private slots:
    void cambiarTurnoJugador();

    void comenzarNivelUno();
    void comenzarNivelDos();

    void finalizarNivelUno();
    void finalizarNivelDos();

private:
    QGraphicsScene *escena;
    QGraphicsView *view;

    enum Turno
    {
        player1,
        player2,
    };
    Turno turno;

    int nivelJugador1;
    int nivelJugador2;
    int puntajeJugador1;
    int puntajeJugador2;
    int vidasJugador1;
    int vidasJugador2;

    NivelUno *nivelUno;
};

#endif // MENUMULTIJUGADOR_H
