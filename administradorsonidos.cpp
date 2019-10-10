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

    hongo = new  QSoundEffect();
    hongo->setSource(QUrl("qrc:/Sonidos/sprout.wav"));
    hongo->setLoopCount(0);
    hongo->setVolume(60);

    golpe = new  QSoundEffect();
    golpe->setSource(QUrl("qrc:/Sonidos/shrink.wav"));
    golpe->setLoopCount(0);
    golpe->setVolume(60);

    flor = new  QSoundEffect();
    flor->setSource(QUrl("qrc:/Sonidos/powerup.wav"));
    flor->setLoopCount(0);
    flor->setVolume(60);

    nivel->play();
}

AdministradorSonidos::~AdministradorSonidos()
{
    delete nivel;
    delete salto;
    delete moneda;
    delete muerto;
    delete hongo;
    delete flor;
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

void AdministradorSonidos::reproducirHongo()
{
    hongo->play();
}

void AdministradorSonidos::reproducirGolpe()
{
    golpe->play();
}

void AdministradorSonidos::reproducirFlor()
{
    flor->play();
}
