#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this); //crear elementos
    menuJugador = new MenuJugador();
    instrucciones = new Instrucciones();
    menuMultijugador = new MenuMultijugador();
    connect(ui->UnJugador, &QPushButton::clicked, this, &Widget::unJugador);
    connect(ui->Multijugador, &QPushButton::clicked, this, &Widget::multiJugador);
    connect(ui->Info, &QPushButton::clicked, this, &Widget::mostrarInstrucciones);
}

Widget::~Widget()
{
    delete ui;
    delete menuJugador;
    delete menuMultijugador;
    delete instrucciones;
}


void Widget::unJugador()
{
    menuJugador->show();
    this->close();
}

void Widget::multiJugador()
{
    menuMultijugador->correrJuego2();
}

void Widget::mostrarInstrucciones()
{
    instrucciones->show();
}
