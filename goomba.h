#ifndef GOOMBA_H
#define GOOMBA_H

#include <QGraphicsItem>
#include <QPixmap>
#include <QPainter>

class Goomba :  public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    Goomba(QGraphicsItem *padre = nullptr);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

public slots:
    void siguienteSprite();

private:
    QPixmap sprite;
    int posSprite;
};

#endif // GOOMBA_H
