#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this); //crear elementos
    menuJugador = new MenuJugador();


}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_UnJugador_clicked()
{
    menuJugador->show();
    this->close();
}
