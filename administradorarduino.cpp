#include "administradorarduino.h"

AdministradorArduino::AdministradorArduino(QObject *parent) : QObject(parent)
{
    serial = new QSerialPort(); //Inicializar la variable serial
    isAvailable = false;

    foreach (const QSerialPortInfo &serial_info, QSerialPortInfo::availablePorts())
    {
        //Lee toda la información del serial
//        qDebug()<<"Puerto: "<<serial_info.portName();
        portName = serial_info.portName(); //Coloca el puerto serial disponible
//        qDebug()<<"vendorId: "<<serial_info.vendorIdentifier();
        vendorId = serial_info.vendorIdentifier(); //Coloca el id del dispositivo conectado en ese momento
//        qDebug()<<"ProductId: "<<serial_info.productIdentifier();
        productId = serial_info.productIdentifier();
        isAvailable = true;
    }

    if(isAvailable){
        incializarArduino(); //Este método establece todos los parámetros necesarios para iniciar la comunicación
    }
}

AdministradorArduino::~AdministradorArduino()
{
    delete serial;
}

bool AdministradorArduino::getEstado()
{
    return isAvailable;
}

void AdministradorArduino::incializarArduino()
{
    serial->setPortName(portName);
    serial->setBaudRate(QSerialPort::Baud9600); //Debe ser la misma velocidad del arduino
    serial->setDataBits(QSerialPort::Data8);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop);
    serial->setFlowControl(QSerialPort::NoFlowControl);
    serial->open(QIODevice::ReadWrite);
}

QByteArray AdministradorArduino::leerArduino()
{
    QByteArray readData;
    if(serial->isReadable() && isAvailable)
    {
        readData = serial->readLine();
        qDebug()<<"Dato leido: "<< readData;
    }
    return readData;
}
