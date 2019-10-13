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

    void pararLevel1();
    void pararLevel2();

    void reproducirLevel1();
    void reproducirLevel2();
    void reproducirSalto();
    void reproducirMoneda();
    void reproducirMuerto1();
    void reproducirMuerto2();
    void reproducirHongo();
    void reproducirGolpe();
    void reproducirFlor();

private:
    QMediaPlayer *nivel1;
    QMediaPlayer *nivel2;
    QSoundEffect *salto;
    QSoundEffect *moneda;
    QSoundEffect *muerto;
    QSoundEffect *hongo;
    QSoundEffect *golpe;
    QSoundEffect *flor;

};

#endif // ADMINISTRADORSONIDOS_H
