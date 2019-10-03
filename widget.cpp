#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this); //crear elementos
    menuJugador = new MenuJugador();
    connect(ui->UnJugador, &QPushButton::clicked, this, &Widget::unJugador);

}

Widget::~Widget()
{
    delete ui;
}


void Widget::unJugador()
{
    menuJugador->show();
    this->close();
}
