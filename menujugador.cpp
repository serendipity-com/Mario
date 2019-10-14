#include "menujugador.h"
#include "ui_menujugador.h"

MenuJugador::MenuJugador(QWidget *parent) :
    QWidget(parent)
  , ui(new Ui::MenuJugador)
  , vidas(5)
{
    ui->setupUi(this);
    incializarEscena();
    construirInformacion();

    connect(ui->NuevaPartida, &QPushButton::clicked, this, &MenuJugador::nuevaPartida);
    connect(ui->CargarPartida, &QPushButton::clicked, this, &MenuJugador::cargarPartida);
}

MenuJugador::~MenuJugador()
{
    actualizarBaseDatos();
    delete ui;
    delete escena;
    delete view;
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
    if(vidas >= 1)
    {
        switch(informacion[jugadorActual][0])
        {
        case 1:
            comenzarNivelUno();
            break;
        case 2:
            comenzarNivelDos();
            break;
//        case 3:
//    //      comenzarNivelTres();
//            break;
        }
    }
    else
    {
        //Si el número de vidas es menor a cero, GAME OVER
        view->close();
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

    vidas = 5;
    correrJuego();

}

void MenuJugador::repetirNivel()
{
    vidas -= 1;
    escena->clear();
    correrJuego();
}

void MenuJugador::comenzarNivelUno()
{
    nivelUno = new NivelUno();
    view->setScene(nivelUno);
    view->show();
    connect(this->nivelUno, SIGNAL(repetirNivel()), this, SLOT(repetirNivel()));
    connect(this->nivelUno, SIGNAL(finalizarNivelUno()), this,SLOT(finalizarNivelUno()));
}

void MenuJugador::comenzarNivelDos()
{
    nivelDos = new NivelDos(informacion[jugadorActual][1]);
    view->setScene(nivelDos);
    view->show();
    informacion[jugadorActual][0] = 2; //actualizar base de datos local en map para al final escribir estos en el archivo dataBase
    connect(this->nivelDos, SIGNAL(finalizarNivelDos()), this,SLOT(finalizarNivelDos())); //conecta señal de clase nivelDos con slot de esta clase que tiene el mismo nombre
    connect(this->nivelDos, SIGNAL(repetirNivel()), this,SLOT(repetirNivel()));
}

//void MenuJugador::comenzarNivelTres()
//{
    //instanciar nivel tres
    //poner en la escena el nivel tres
    //mostrar escena
//    informacion[jugadorActual][0] = 3;
    //connect(this->nivelTres, SIGNAL(finalizarNivelTres()), this,SLOT(finalizarNivelTres())); conecta señal de clase nivelTres con slot de esta clase que tiene el mismo nombre
    //connect(this->nivelTres, SIGNAL(finalizarNivelTres()), this,SLOT(repetirNivel()));
//}

void MenuJugador::finalizarNivelUno()
{
    informacion[jugadorActual][1] = nivelUno->getPuntaje();
    escena->clear();
    delete nivelUno;
    comenzarNivelDos();
}

void MenuJugador::finalizarNivelDos()
{
    informacion[jugadorActual][1] = nivelDos->getPuntaje();
    escena->clear();
    delete nivelDos;
//    comenzarNivelTres();
    //mostrar widget con puntaje y vidas CONGRATULATIONS!
}

//void MenuJugador::finalizarNivelTres()
//{
//    delete nivelTres;
    //mostrar widget con puntaje y vidas CONGRATULATIONS!
//}

void MenuJugador::cargarPartida()//***
{
    jugadorActual = ui->NombreUsuario->text(); //Nombre ingresado
    auto iterador = informacion.find(jugadorActual);
    if(iterador == informacion.end()) //Si no está en el map de base de datos
    {
        QMessageBox::warning(this, tr("Información"), tr("No tienes partida guardada"));
    }
    else
    {
        ui->NombreUsuario->clear(); //Para borrar del lineEdit el nombre
        vidas = 5;
        correrJuego();
    }
}

void MenuJugador::actualizarBaseDatos()
{
//  una vez finalice la partida del jugador en cualquiera de los niveles, se procede a hacer esto:
    int nivel = informacion[jugadorActual][0];
    int puntaje = informacion[jugadorActual][1];
    QFile inputFile("BaseDatos.txt");
    if (inputFile.open(QIODevice::Append | QIODevice::Text))
    {
       QTextStream in(&inputFile); //hay que indexar en el map de base de datos y todos esos datos escribirlos en el archivo dataBase.txt
       in << jugadorActual << ":" << nivel << puntaje << endl;
       in.flush();
    }
    inputFile.close();
}




