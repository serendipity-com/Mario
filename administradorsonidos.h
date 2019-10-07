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

private:
    QMediaPlayer *nivel;
    QSoundEffect *salto;
    QSoundEffect *moneda;
    QSoundEffect *muerto;
    QSoundEffect *hongo;
    QSoundEffect *golpe;

};

#endif // ADMINISTRADORSONIDOS_H
