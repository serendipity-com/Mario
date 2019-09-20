#ifndef PERSONAJE_H
#define PERSONAJE_H

#include <QGraphicsItem>
#include <QPainter>
#include <QPixmap>

class Personaje : public QGraphicsItem
{
public:
    Personaje(QGraphicsItem *padre = nullptr);
    ~Personaje();

    void caminar();
    void saltar();
    void estarQuieto();
    void atacar();

    void siguienteSprite();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

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

    int vidas;

    int posicionX;
    int posicionY;
};

#endif // PERSONAJE_H
