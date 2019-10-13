#ifndef LADRILLONOTA_H
#define LADRILLONOTA_H

#include <QGraphicsItem>
#include <QPainter>
#include <QPixmap>

class LadrilloNota : public QGraphicsItem
{
public:
    enum{ Type = UserType + 11};
    LadrilloNota(int _longitud, QGraphicsItem *padre = nullptr);
    ~LadrilloNota();

    void siguienteSprite();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    int type() const;

private:
    QPixmap sprite;
    int posSprite;
    int longitud;
};

#endif // LADRILLONOTA_H
