#ifndef NIVELUNO_H
#define NIVELUNO_H

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
#include "ladrillosorpresa.h"
#include "ladrillo.h"
#include "tubo.h"
#include "flor.h"

class NivelUno: public QGraphicsScene
{
    Q_OBJECT
public:
    explicit NivelUno(QObject *padre = nullptr);
    ~NivelUno();

    void timerEvent(QTimerEvent *);

    void agregarEntradaHorizontal(int entrada);
    void aplicarParalelismo(qreal propocion, QGraphicsItem *item);

    void iniciarEscena();

public slots:
    void actualizar();
    void moverJugador();
    void siguienteSprite();
    void checkTimer();

    void verificarColisionMoneda();
    void verificarColisionPlataforma(PersonajeFisica *p);
    void verificarColisionBordes(PersonajeFisica *p);

signals:


protected:
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

private:
    int anchoEscena;

    Personaje *personaje;

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
    QTimer *timerSprite;

    int entradaHorizontal;


    Moneda *moneda;
    Moneda *moneda1;
    Ladrillo *ladrillo;
    Ladrillo *ladrillo2;
    Ladrillo *ladrillo3;
    LadrilloSorpresa *sorpresa;
    LadrilloSorpresa *sorpresa2;
    Tubo *tubo;
    Flor *flor;
};

#endif // NIVELUNO_H
