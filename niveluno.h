#ifndef NIVELUNO_H
#define NIVELUNO_H

#include <QGraphicsScene>
#include <QTimer>
#include <QKeyEvent>
#include <QPropertyAnimation>
#include <QDebug>
#include <QGraphicsView>
#include <QList>

#include "personaje.h"
#include "personajefisica.h"
#include "backgrounditem.h"
#include "moneda.h"
#include "hongo.h"
#include "ladrillosorpresa.h"
#include "ladrillo.h"
#include "ladrillonota.h"
#include "fantasma.h"
#include "tubo.h"
#include "flor.h"
#include "florfuego.h"
#include "goomba.h"
#include "administradorsonidos.h"
#include "administradorarduino.h"
#include "puntaje.h"
#include "castillo.h"
#include "bandera.h"

class NivelUno: public QGraphicsScene
{
    Q_OBJECT
public:
    explicit NivelUno(QObject *padre = nullptr);
    ~NivelUno();

    int getPuntaje();
    void reiniciarEscenaUno(int in);
    void reiniciarEscenaDos(int _puntaje, int in);
    void iniciarEscenaUno();
    void iniciarEscenaDos();

private:
    void agregarEntradaHorizontal(int entrada);
    void aplicarParalelismo(qreal propocion, QGraphicsItem *item);

    void moverJugador();
    void checkTimer();

    void verificarColisionCastillo();
    void verificarColisionMoneda();
    void verificarColisionAyudas();
    void verificarColisionEnemigos(PersonajeFisica *p);
    void verificarColisionPlataforma(PersonajeFisica *p);
    void verificarColisionBordes(PersonajeFisica *p);
    void cambiarDireccionGomba();

    void enviarReiniciar();
    void enviarFinalizarUno();
    void enviarFinalizarDos();

public slots:
    void correrEscena();
    void actualizar();
    void siguienteSprite();
    void moverConMando();

protected:
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

signals:
    void finalizarNivelUno();
    void finalizarNivelDos();
    void repetirNivel();

private:
    int anchoEscena;

    Personaje *personaje;
    Personaje *personajeSmall;
    Personaje *personajeFire;

    bool salto;
    enum Estado
    {
        small,
        normal,
        fire
    };
    Estado estado;

    enum Nivel
    {
        uno,
        dos
    };
    Nivel nivel;

    BackgroundItem *cielo1;
    BackgroundItem *cielo2;
    BackgroundItem *cielo3;
    BackgroundItem *cielo4;
    BackgroundItem *cielo5;
    BackgroundItem *cielo6;
    BackgroundItem *cielo7;
    BackgroundItem *tierra;

    qreal minX;
    qreal maxX;
    qreal nivelTierra;
    qreal posicionX;
    int desplazamientoMundo;
    int velocidad;

    QTimer *timer;
    QTimer *timerEscena;
    QTimer *timerSprite;
    QTimer *timerMando;

    AdministradorSonidos *sonidos;
    AdministradorArduino *mando;
    QGraphicsItem *mandoImagen;

    //complementos de la escena
    QList <Moneda *> monedas;
    QList <Ladrillo*> ladrillos;
    Hongo *hongo;
    FlorFuego *florFuego;
    QList <LadrilloSorpresa*> ladrillosSorpresa;
    QList <LadrilloNota*> ladrillosNota;
    QList <Fantasma*> fantasmas;
    QList <Tubo *> tubos;
    QList <Flor *> floresCar;
    QList <Goomba*> gombas;
    Castillo *castillo;
    QGraphicsItem *tuboBandera;
    Bandera *bandera;

    Puntaje *puntaje;
    BackgroundItem *puntajeLogo;
};

#endif // NIVELUNO_H
