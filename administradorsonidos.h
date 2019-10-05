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

private:
    QMediaPlayer *nivel;
    QSoundEffect *salto;
    QSoundEffect *moneda;
    QSoundEffect *muerto;
};

#endif // ADMINISTRADORSONIDOS_H
