#include "menujugador.h"
#include "ui_menujugador.h"

MenuJugador::MenuJugador(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MenuJugador)
{
    ui->setupUi(this);
    incializarEscena();
    construirInformacion();

    connect(ui->NuevaPartida, &QPushButton::clicked, this, &MenuJugador::nuevaPartida);
    connect(ui->CargarPartida, &QPushButton::clicked, this, &MenuJugador::cargarPartida);
}

MenuJugador::~MenuJugador()
{
    delete ui;
    //    actualizarBaseDatos();
}

void MenuJugador::incializarEscena()
{
    escena = new QGraphicsScene();

    view = new QGraphicsView();
    view->setRenderHint(QPainter::Antialiasing);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setScene(escena);
    view->setFixedSize(1280,720);

    view->setScene(escena);
}

void MenuJugador::construirInformacion()
//Lee información de archivo que contiene nombre de usuario, nivel y puntaje en el que quedó

{
    QFile inputFile("://BaseDatos.txt");
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
           //qDebug() << informacion[nombre];
       }
       inputFile.close();
    }
}

void MenuJugador::correrJuego()
{
    switch(informacion[jugadorActual][0])
    {
    case 1:
        comenzarNivelUno();
        break;
    case 2:
//        comenzarNivelDos();
        break;
    }
}

void MenuJugador::nuevaPartida()
{
    jugadorActual = ui->NombreUsuario->text(); //Nombre ingresado
    auto iterador = informacion.find(jugadorActual);
    if(iterador == informacion.end()) //Si no está en el map de base de datos
    {
        informacion.insert({jugadorActual, {1,0}});
    }
    else
        informacion[jugadorActual] = {1,0};
    //qDebug() << informacion[data];
    ui->NombreUsuario->clear(); //Para borrar del lineEdit el nombre

    correrJuego();

}

void MenuJugador::comenzarNivelUno()
{
    nivelUno = new NivelUno(this);
    view->setScene(nivelUno);
    view->show();
    connect(this->nivelUno, SIGNAL(finalizarNivelUno()), this,SLOT(finalizarNivelUno()));
}

void MenuJugador::comenzarNivelDos()
{

}

void MenuJugador::comenzarNivelTres()
{

}

void MenuJugador::finalizarNivelUno()
{
    delete nivelUno;

}

void MenuJugador::finalizarNivelDos()
{

}

void MenuJugador::finalizarNivelTres()
{

}

void MenuJugador::cargarPartida()//***
{
    jugadorActual = ui->NombreUsuario->text(); //Nombre ingresado
}

//void MenuJugador::actualizarBaseDatos()//***
//{
////  una vez finalice la partida del jugador, se procede a hacer esto:
//    QFile inputFile("://BaseDatos.txt");
//    if (inputFile.open(QIODevice::Append)qDebug() << informacion[data];)
//    {
//       QTextStream in(&inputFile);
//       in << data << ":" << "nivel" << "puntaje" <<endl;
//       in.flush();
//       inputFile.close();
//    }
//}




