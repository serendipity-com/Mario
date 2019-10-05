#include "menujugador.h"
#include "ui_menujugador.h"

MenuJugador::MenuJugador(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MenuJugador)
{
    ui->setupUi(this);
}

MenuJugador::~MenuJugador()
{
    delete ui;
}

void MenuJugador::construirInformacion()
{
    //Lee información de archivo que contiene nombre de usuario, nivel y puntaje en el que quedó
    QFile inputFile("BaseDatos.txt");
    if (inputFile.open(QIODevice::ReadOnly))
    {
       QTextStream in(&inputFile);
       while (!in.atEnd())
       {
           QString line = in.readLine();
           int ch = line.indexOf(":");
           QString nombre = line.mid(0, ch);
           QString valores  = line.mid(ch+1);
           int nivel = valores[0].digitValue();
           int puntaje = line.mid(ch+2).toInt();
           informacion.insert({nombre, {nivel,puntaje}});
       }
       inputFile.close();
    }
}





void MenuJugador::cargarPartida()
{

}

void MenuJugador::nuevaPartida()
{
    //Se encarga de verificar si el usuario ya existe
}
