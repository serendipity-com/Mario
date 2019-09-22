#ifndef GOOMBA_H
#define GOOMBA_H

#include <QGraphicsItem>
#include <QPixmap>
#include <QPainter>
//#include <QTimer>
//#include <QObject>
//#include <typeinfo>
//#include <QGraphicsScene>
//#include "objecttype.h"

class Goomba :  public QObject, public QGraphicsItem

{
    Q_OBJECT
public:
//    enum { Type = UserType + goombaType };
    Goomba(QRectF platformRect, int direction,QGraphicsItem *padre = nullptr);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
//    int type() const;

public slots:
    void siguienteSprite();

//signals:
//    void marioSizeStatus(int);

private:
    QPixmap sprite;
    int posSprite;
//    QRectF mPlatform;
//    int mDirection;
};

#endif // GOOMBA_H
