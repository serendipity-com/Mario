#ifndef ADMINISTRADORSONIDOS_H
#define ADMINISTRADORSONIDOS_H

#include <QMediaPlayer>
#include <QMediaResource>
#include <QMediaContent>
#include <QSoundEffect>
#include <QDebug>

class AdministradorSonidos
{
public:
    AdministradorSonidos();
    ~AdministradorSonidos();

    void reproducirSalto();
    void reproducirMoneda();
    void reproducirMuerto();
    void reproducirHongo();
    void reproducirGolpe();
    void reproducirFlor();

private:
    QMediaPlayer *nivel;
    QSoundEffect *salto;
    QSoundEffect *moneda;
    QSoundEffect *muerto;
    QSoundEffect *hongo;
    QSoundEffect *golpe;
    QSoundEffect *flor;

};

#endif // ADMINISTRADORSONIDOS_H
