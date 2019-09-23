#ifndef NIVELUNO_H
#define NIVELUNO_H

#include <QGraphicsScene>
#include <QTimer>
#include <QKeyEvent>
#include "personaje.h"

class NivelUno: public QGraphicsScene
{
public:
    NivelUno();
    ~NivelUno();

    void agregarEntradaHorizontal(int entrada);
    void checkTimer();

public slots:
    void moverJugador();

protected:
    void keyPressEvent(QKeyEvent *event);

private:
    int anchoEscena = 720;

    Personaje *personaje;

    qreal minX;
    qreal maxX;
    qreal nivelTierra;
    qreal posicionX;
    int desplazamientoMundo;

    int velocidad;

    QTimer timer;

    int entradaHorizontal;
};

#endif // NIVELUNO_H
