#include "menumultijugador.h"
#include "ui_menumultijugador.h"

MenuMultijugador::MenuMultijugador(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MenuMultijugador)
{
    ui->setupUi(this);
}

MenuMultijugador::~MenuMultijugador()
{
    delete ui;
}
