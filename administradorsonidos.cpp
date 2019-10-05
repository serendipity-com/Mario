#include "administradorsonidos.h"

AdministradorSonidos::AdministradorSonidos()
{
    nivel = new QMediaPlayer();
    nivel->setMedia(QUrl("qrc:/Sonidos/level1.mp3"));
    nivel->setVolume(130);

    salto = new QSoundEffect();
    salto->setSource(QUrl("qrc:/Sonidos/jump.wav"));
    salto->setLoopCount(0);
    salto->setVolume(40);

    moneda = new QSoundEffect();
    moneda->setSource(QUrl("qrc:/Sonidos/coin.wav"));
    moneda->setLoopCount(0);
    moneda->setVolume(60);

    muerto = new  QSoundEffect();
    muerto->setSource(QUrl("qrc:/Sonidos/death.wav"));
    muerto->setLoopCount(0);
    muerto->setVolume(40);

    nivel->play();
}

AdministradorSonidos::~AdministradorSonidos()
{
    delete nivel;
    delete salto;
    delete moneda;
    delete muerto;
}

void AdministradorSonidos::reproducirSalto()
{
    salto->play();
    //qDebug() << "sonido salto";
}

void AdministradorSonidos::reproducirMoneda()
{
    moneda->play();
}

void AdministradorSonidos::reproducirMuerto()
{
    muerto->play();
    nivel->stop();
}
