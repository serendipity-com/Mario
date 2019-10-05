#ifndef PUNTAJE_H
#define PUNTAJE_H

#include <QGraphicsTextItem>
#include <QGraphicsItem>
#include <QFont>
#include <QFontDatabase>

class Puntaje : QGraphicsTextItem
{
public:
    Puntaje(QGraphicsItem *padre = nullptr);
    
    void incrementar();
    int getPuntaje();
    
private:
    int puntaje;
};

#endif // PUNTAJE_H
