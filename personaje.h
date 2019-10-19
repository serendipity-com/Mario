#ifndef PERSONAJE_H
#define PERSONAJE_H

#include <QGraphicsItem>
#include <QPainter>
#include <QPixmap>
#include <QTransform>
#include "personajefisica.h"

class Personaje :public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    Personaje(int _tipo, QGraphicsItem *padre = nullptr);
    ~Personaje();

    void caminar();
    void saltar();
    void estarQuieto();
    void atacar();

    int getDireccion();
    void setDireccion(int inDireccion);

    void siguienteSprite();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    bool estarTocandoL(QGraphicsItem *item);
    bool estarTocandoR(QGraphicsItem *item);
    bool estarTocandoCabeza(QGraphicsItem *item);
    bool estarTocandoPies(QGraphicsItem *item);
    bool estarTocandoPlataforma(QGraphicsItem *item);

    void cambiarPersonaje(int in);

    void actualizar(int lim);
    PersonajeFisica *getFisica();

private:
    enum Estado
    {
        caminando,
        saltando,
        quieto,
        atacando,
    };
    enum Jugador
    {
        mario = 1,
        luigi = 2,
    };

    int alto;
    int ancho;

    Estado estado;
    Jugador jugador;
    int tipo;

    QPixmap sprite;
    QPixmap spriteCaminando;
    QPixmap spriteSaltando;
    QPixmap spriteQuieto;
    QPixmap spriteAtacando;
    int posSprite;

    int direccion;

    PersonajeFisica *personaje;
};

#endif // PERSONAJE_H
