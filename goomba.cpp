#include "goomba.h"
//#include "player.h"
//#include "smallmario.h"
//#include "firemario.h"
//#include <QPainter>
//#include <QDebug>

Goomba::Goomba(QRectF platformRect, int direction, QGraphicsItem *parent) : QGraphicsItem(parent), mCurrentFrame3(), mPlatform(platformRect), mDirection(direction)
{
    setFlag(ItemClipsToShape);
    sprite = QPixmap(":images/goombas.png");
//    QTimer *timer = new QTimer(this);
//    connect(timer,SIGNAL(timeout()),this,SLOT(nextFrame()));
//    timer->start(100);
}

void Goomba::siguienteSprite()
{
    //Manejo de Sprites
    //Distancia en caada sprite
    posSprite += 54;
    //Condicion volver al primer sprite, si sobre pasa la dimension la imagen plana
    if(posSprite >= 862)
    {
        posSprite = 0;
    }
}


QRectF Goomba::boundingRect() const {

    return QRectF(0,0,52,50);
}

void Goomba::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(0,0, sprite, posSprite, 0,52, 50);
    setTransformOriginPoint(boundingRect().center());
    Q_UNUSED(widget);
    Q_UNUSED(option);
}

//int Goomba::type() const {

//    return Type;
//}


