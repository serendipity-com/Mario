#ifndef GOOMBA_H
#define GOOMBA_H

#include <QGraphicsItem>
#include <QPixmap>
#include <QPainter>

class Goomba :  public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    enum{ Type = UserType + 8};
    Goomba(QGraphicsItem *padre = nullptr);

    int getDireccion();
    void setDireccion(int inDireccion);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    int type() const;
    void siguienteSprite();

private:
    QPixmap sprite;
    int posSprite;
    int direccion;
};

#endif // GOOMBA_H
