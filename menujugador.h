#ifndef MENUJUGADOR_H
#define MENUJUGADOR_H

#include <QWidget>
#include <map>
#include <QList>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QDataStream>
#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsView>

#include "niveluno.h"

using namespace std;
namespace Ui {
class MenuJugador;
}

class MenuJugador : public QWidget
{
    Q_OBJECT
public:
    explicit MenuJugador(QWidget *parent = nullptr);
    ~MenuJugador();

private:
    void incializarEscena();
    //    void actualizarBaseDatos();
    void correrJuego();
    void construirInformacion();

private slots:
    void cargarPartida();
    void nuevaPartida();

    void repetirNivel();

    void comenzarNivelUno();
    void comenzarNivelDos();
    void comenzarNivelTres();

    void finalizarNivelUno();
    void finalizarNivelDos();
    void finalizarNivelTres();

private:
    Ui::MenuJugador *ui;
    QGraphicsScene *escena;
    QGraphicsView *view;

    //informacion
    QString jugadorActual;
    map <QString, QList<int>> informacion;

    int vidas;

    //Niveles
    NivelUno *nivelUno;
//    NivelDos *nivelDos;
//    NivelTres *nivelTres;

};

#endif // MENUJUGADOR_H
