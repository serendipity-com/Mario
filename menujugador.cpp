#include "menujugador.h"
#include "ui_menujugador.h"

MenuJugador::MenuJugador(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MenuJugador)
{
    ui->setupUi(this);
    //Leer información de archivo que contiene nombre de usuario y nivel en el que quedó
    //map<QString, unsigned int>
}

MenuJugador::~MenuJugador()
{
    delete ui;
}





void MenuJugador::cargarPartida()
{

}

void MenuJugador::nuevaPartida()
{
    //Se encarga de verificar si el usuario ya existe
}
