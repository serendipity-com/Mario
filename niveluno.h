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
#include "personajesmall.h"
#include "personajefisica.h"
#include "backgrounditem.h"
#include "moneda.h"
#include "hongo.h"
#include "ladrillosorpresa.h"
#include "ladrillo.h"
#include "tubo.h"
#include "flor.h"
#include "goomba.h"
#include "administradorsonidos.h"

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

    void verificarColisionMoneda();
    void verificarColisionAyudas();
    void verificarColisionEnemigos(PersonajeFisica *p);
    void verificarColisionPlataforma(PersonajeFisica *p);
    void verificarColisionBordes(PersonajeFisica *p);
    void cambiarDireccionGomba();
public slots:
    void actualizar();
    void moverJugador();
    void siguienteSprite();
    void checkTimer();

protected:
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

private:
    int anchoEscena;

    Personaje *personaje;
    PersonajeSmall *personajeSmall;

    enum Estado
    {
        small,
        normal,
        fuego
    };
    Estado estado;

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

    AdministradorSonidos *sonidos;

    //complementos de la escena
    QList <Moneda *> monedas;
    QList <Ladrillo*> ladrillos;
    Hongo *hongo;
    QList <LadrilloSorpresa*> ladrillosSorpresa;
    QList <Tubo *> tubos;
    QList <Flor *> floresCar;
    QList <Goomba*> gombas;
};

#endif // NIVELUNO_H
