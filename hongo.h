#ifndef HONGO_H
#define HONGO_H

#include <QGraphicsItem>
#include <QPixmap>
#include <QPainter>
//#include "objecttype.h"
//#include <QTimer>
//#include <QObject>
//#include <typeinfo>
//#include <QGraphicsScene>

class Hongo: public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
//    enum { Type = UserType + mushroomType };
    Hongo(QRectF platformRect, int direction,QGraphicsItem *padre = nullptr);
    ~Hongo();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
//    int type() const;

public slots:
void siguienteSprite();

//signals:
//void marioSizeStatus(int);

private:
    QPixmap sprite;
    int posSprite;
//    QRectF mPlatform;
//    int mDirection;
//    bool up;
//    bool right;
//    bool down;
//    bool right2;
//
};

#endif // HONGO_H


