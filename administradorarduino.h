#ifndef ADMINISTRADORARDUINO_H
#define ADMINISTRADORARDUINO_H

#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>

class AdministradorArduino : public QObject
{
    Q_OBJECT
public:
    explicit AdministradorArduino(QObject *parent = nullptr);
    ~AdministradorArduino();

    bool getEstado();
    QByteArray leerArduino();

private:
    void incializarArduino();

private:
    QSerialPort *serial;
    QString portName;
    quint16 vendorId;
    quint16 productId;
    bool isAvailable;

};

#endif // ADMINISTRADORARDUINO_H
