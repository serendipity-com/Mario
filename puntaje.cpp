#include "puntaje.h"

Puntaje::Puntaje(QGraphicsItem *padre) : QGraphicsTextItem(padre)
{
    //inicializa puntaje en cero)
    puntaje = 0;

    //dibuja el texto
    int id = QFontDatabase::addApplicationFont(":/Fuente/CoinCount2.ttf");
    QFontDatabase::applicationFontFamilies(id);
    setPlainText(QString("") + QString::number(puntaje));
    setDefaultTextColor(Qt::blue);
    setFont(QFont("CoinCount2", 40));
}

void Puntaje::incrementar()
{
    puntaje++;
    setPlainText(QString("") + QString::number(puntaje));
}

int Puntaje::getPuntaje()
{
    return puntaje;
}

void Puntaje::setPuntaje(int valor)
{
    puntaje = valor;
    setPlainText(QString("") + QString::number(puntaje));
}
