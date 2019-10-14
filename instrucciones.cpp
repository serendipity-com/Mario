#include "instrucciones.h"
#include "ui_instrucciones.h"

Instrucciones::Instrucciones(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Instrucciones)
{
    ui->setupUi(this);
}

Instrucciones::~Instrucciones()
{
    delete ui;
}
