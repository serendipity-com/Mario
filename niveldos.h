#ifndef NIVELDOS_H
#define NIVELDOS_H

#include <QGraphicsScene>
#include <QTimer>
#include <QTimerEvent>
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
#include "fantasma.h"
#include "ladrillonota.h"
#include "ladrillosorpresa.h"
#include "ladrillo.h"
#include "tubo.h"
#include "flor.h"
#include "florfuego.h"
#include "goomba.h"
#include "administradorsonidos.h"
#include "administradorarduino.h"
#include "puntaje.h"
#include "castillo.h"
#include "bandera.h"

class NivelDos : public QGraphicsScene
{
    Q_OBJECT

public:
    explicit NivelDos(int _puntaje, QObject *padre = nullptr);
    ~NivelDos();

    int getPuntaje();

private:
    void iniciarEscena();
    void timerEvent(QTimerEvent *);

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
    void enviarFinalizar();

public slots:
    void actualizar();
    void siguienteSprite();
    void moverConMando();

protected:
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

signals:
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

    BackgroundItem *cielo1;
    BackgroundItem *cielo2;
    BackgroundItem *cielo3;
    BackgroundItem *cielo4;
    BackgroundItem *cielo5;
    BackgroundItem *cielo6;
    BackgroundItem *tierra;

    qreal minX;
    qreal maxX;
    qreal nivelTierra;
    qreal posicionX;
    int desplazamientoMundo;
    int velocidad;

    QTimer *timer;
    QTimer *timerSprite;
    QTimer *timerMando;

    AdministradorSonidos *sonidos;
    AdministradorArduino *mando;

    //complementos de la escena
    QList <Moneda *> monedas;
    QList <Ladrillo*> ladrillos;
    QList <LadrilloSorpresa*> ladrillosSorpresa;
    QList <LadrilloNota*> ladrillosNota;
    QList <Fantasma*> fantasmas;
    Hongo *hongo;
    FlorFuego *florFuego;
    QList <Tubo *> tubos;
    QList <Flor *> floresCar;
    QList <Goomba*> gombas;
    Castillo *castillo;
    QGraphicsItem *tuboBandera;
    Bandera *bandera;

    Puntaje *puntaje;
    BackgroundItem *puntajeLogo;
};

#endif // NIVELDOS_H
