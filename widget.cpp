#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this); //crear elementos
    menuJugador = new MenuJugador();
    menuMultijugador = new MenuMultijugador();
    connect(ui->UnJugador, &QPushButton::clicked, this, &Widget::unJugador);
    connect(ui->Multijugador, &QPushButton::clicked, this, &Widget::multiJugador);
}

Widget::~Widget()
{
    delete ui;
    delete menuJugador;
    delete menuMultijugador;
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
