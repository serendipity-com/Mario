#include "hongo.h"
//#include "player.h"
//#include "smallmario.h"
//#include <QPainter>
//#include <QDebug>

Hongo::Hongo(QRectF platformRect, int direction,QGraphicsItem *parent): QGraphicsItem(parent),mCurrentFrame(),mPlatform(platformRect), mDirection(direction)

{
    setFlag(ItemClipsToShape);
    sprite = QPixmap(":images/m40.png");
//    QTimer *timer = new QTimer(this);
//    connect(timer,SIGNAL(timeout()),this,SLOT(nextFrame()));
//    timer->start(100);
//    up= true;
//    down = true;
//    right = true;
//    right2 = false;
}

Hongo::~Hongo(){

}

void Hongo::siguienteSprite(){
}

QRectF Hongo::boundingRect() const {
    return QRectF(0,0,70,50);

}

void Hongo::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->drawPixmap(0,0, mPixmap, mCurrentFrame, 0,70, 50);
    setTransformOriginPoint(boundingRect().center());
    Q_UNUSED(widget);
    Q_UNUSED(option);

}



