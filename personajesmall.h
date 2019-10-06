#ifndef PERSONAJESMALL_H
#define PERSONAJESMALL_H

#include <QGraphicsItem>
#include <QPainter>
#include <QPixmap>
#include <QTransform>
#include "personajefisica.h"

class PersonajeSmall : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    PersonajeSmall(QGraphicsItem *padre = nullptr);
    ~PersonajeSmall();

    void caminar();
    void saltar();
    void estarQuieto();
    void atacar();

    int getDireccion();
    void setDireccion(int inDireccion);

    void siguienteSprite();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

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

#endif // PERSONAJESMALL_H
