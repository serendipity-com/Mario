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
    Personaje(int tipo, QGraphicsItem *padre = nullptr);
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

    int alto;
    int ancho;

    Estado estado;

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
