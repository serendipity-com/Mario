#ifndef NIVELUNO_H
#define NIVELUNO_H

#include <QGraphicsScene>
#include <QTimer>
#include <QKeyEvent>
#include <QPropertyAnimation>
#include <QDebug>
#include <QGraphicsView>

#include "personaje.h"
#include "backgrounditem.h"
#include "moneda.h"


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

    void agregarEntradaHorizontal(int entrada);
    void aplicarParalelismo(qreal propocion, QGraphicsItem *item);

    void saltar();
    qreal getFactorSalto() const;
    void setFactorSalto(const qreal &pos);

    void iniciarEscena();

public slots:
    void moverJugador();
    void checkTimer();

    void verificarColisioneMoneda();

signals:
    void cambiarFactorSalto(qreal);

protected:
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

private:
    int anchoEscena = 720;

    Personaje *personaje;

    BackgroundItem *cielo;
    BackgroundItem *tierra;
    BackgroundItem *bloques;

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

};

#endif // NIVELUNO_H
