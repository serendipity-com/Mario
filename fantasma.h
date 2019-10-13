#ifndef FANTASMA_H
#define FANTASMA_H

#include <QGraphicsItem>
#include <QPixmap>
#include <QPainter>

class Fantasma : public QGraphicsItem
{
public:
    enum{ Type = UserType + 12};
    Fantasma(QGraphicsItem *padre = nullptr);
    ~Fantasma();

    bool estarTocandoFantasma(QGraphicsItem *item);

    void siguienteSprite();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    int type() const;

private:
    QPixmap sprite;
    int posSprite;
    int altura;
};

#endif // FANTASMA_H
