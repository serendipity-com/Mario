#include "instrucciones.h"
#include "ui_instrucciones.h"

Instrucciones::Instrucciones(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Instrucciones)
{
    ui->setupUi(this);
    connect(ui->OK, SIGNAL(clicked()), this, SLOT(cerrar()));
}

Instrucciones::~Instrucciones()
{
    delete ui;
}

void Instrucciones::cerrar()
{
    this->close();
}
