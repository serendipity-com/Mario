#ifndef PUNTAJE_H
#define PUNTAJE_H

#include <QGraphicsTextItem>
#include <QGraphicsItem>
#include <QFont>
#include <QFontDatabase>

class Puntaje : public QGraphicsTextItem
{
public:
    Puntaje(QGraphicsItem *padre = nullptr);
    
    void incrementar();
    int getPuntaje();
    void setPuntaje(int valor);

private:
    int puntaje;
};

#endif // PUNTAJE_H
