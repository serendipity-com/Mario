#ifndef MENUMULTIJUGADOR_H
#define MENUMULTIJUGADOR_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>

#include "niveluno.h"
#include "niveldos.h"

namespace Ui {
class MenuMultijugador;
}

class MenuMultijugador : public QWidget
{
    Q_OBJECT

public:
    explicit MenuMultijugador(QWidget *parent = nullptr);
    ~MenuMultijugador();

private:
    void inicializarEscena2();
    void correrJuego2();

private slots:
    void cambiarTurnoJugador();

    void comenzarNivelUno();
    void comenzarNivelDos();

    void finalizarNivelUno();
    void finalizarNivelDos();

private:
    Ui::MenuMultijugador *ui;
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

    NivelUno *nivelUno;
    NivelDos *nivelDos;

};

#endif // MENUMULTIJUGADOR_H
