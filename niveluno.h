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
#include "backgrounditem.h"
#include "moneda.h"
#include "ladrillosorpresa.h"


class NivelUno: public QGraphicsScene
{
    Q_OBJECT
    Q_PROPERTY(qreal getFactorSalto
               READ getFactorSalto
               WRITE setFactorSalto
               NOTIFY cambiarFactorSalto)
public:
    explicit NivelUno(QObject *padre = nullptr);
    ~NivelUno();

    void timerEvent(QTimerEvent *);

    void agregarEntradaHorizontal(int entrada);
    void aplicarParalelismo(qreal propocion, QGraphicsItem *item);

    void saltar();
    qreal getFactorSalto() const;
    void setFactorSalto(const qreal &pos);

    void iniciarEscena();

public slots:
    void moverJugador();
    void checkTimer();

    void verificarColisionMoneda();
    void verificarColisionPlataforma();

signals:
    void cambiarFactorSalto(qreal);

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

    int alturaSalto;
    qreal factorSalto;
    QPropertyAnimation *animacionSaltar;

    int velocidad;
    QTimer timer;

    int entradaHorizontal;


    Moneda *moneda;
    Moneda *moneda1;
    LadrilloSorpresa *sorpresa;
};

#endif // NIVELUNO_H
