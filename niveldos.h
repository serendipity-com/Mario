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

#include "niveluno.h"

#include "personaje.h"
#include "personajefisica.h"
#include "backgrounditem.h"
#include "moneda.h"
#include "hongo.h"
#include "ladrillosorpresa.h"
#include "ladrillo.h"
#include "tubo.h"
#include "flor.h"
#include "florfuego.h"
#include "goomba.h"
#include "administradorsonidos.h"
#include "administradorarduino.h"
#include "puntaje.h"

class NivelDos : public NivelUno
{
    Q_OBJECT

public:
    explicit NivelDos(NivelUno *padre = nullptr);
    ~NivelDos();

private:
    void iniciarEscena();

signals:
    void finalizarNivelDos();

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
    int entradaHorizontal;
    int velocidad;

    QTimer *timer;
    QTimer *timerSprite;
    QTimer *timerMando;

    AdministradorSonidos *sonidos;
    AdministradorArduino *mando;

    //complementos de la escena
    QList <Moneda *> monedas;
    QList <Ladrillo*> ladrillos;
    Hongo *hongo;
    FlorFuego *florFuego;
    QList <LadrilloSorpresa*> ladrillosSorpresa;
    QList <Tubo *> tubos;
    QList <Flor *> floresCar;
    QList <Goomba*> gombas;

    Puntaje *puntaje;
    BackgroundItem *puntajeLogo;
};

#endif // NIVELDOS_H
