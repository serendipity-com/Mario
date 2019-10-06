#include "comunicacionarduino.h"
#include "ui_comunicacionarduino.h"
#include <QDebug>

ComunicacionArduino::ComunicacionArduino(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ComunicacionArduino)
{
//    ui->setupUi(this);
    serial = new QSerialPort(); //Inicializar la variable serial
    arduino_available = false;

    foreach (const QSerialPortInfo &serial_info, QSerialPortInfo::availablePorts()) { //Lee toda la información del serial
//        qDebug()<<"Puerto: "<<serial_info.portName();
        portName = serial_info.portName(); //Coloca el puerto serial disponible
//        qDebug()<<"vendorId: "<<serial_info.vendorIdentifier();
        vendorrId = serial_info.vendorIdentifier(); //Coloca el id del dispositivo conectado en ese momento
//        qDebug()<<"ProductId: "<<serial_info.productIdentifier();
        productId = serial_info.productIdentifier();
        arduino_available = true;
    }

    if(arduino_available){
        arduino_init(); //Este método establece todos los parámetros necesarios para iniciar la comunicación
    }
}

ComunicacionArduino::~ComunicacionArduino()
{
    delete ui;
}

void ComunicacionArduino::arduino_init()
{
    serial->setPortName(portName);
    serial->setBaudRate(QSerialPort::Baud9600); //Debe ser la misma velocidad del arduino
    serial->setDataBits(QSerialPort::Data8);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop);
    serial->setFlowControl(QSerialPort::NoFlowControl);
    serial->open(QIODevice::ReadWrite);
    QObject::connect(serial, SIGNAL(readyRead()),this, SLOT(serial_read())); //Conecta el evento del serial cuando hay algun dato en este con un slot definido
}

void ComunicacionArduino::serial_read()
{
    if(serial->isReadable() && arduino_available)
    {
        QByteArray readDAta = serial->readLine();
        qDebug()<<"Dato leido: "<< readDAta;
    }
}
