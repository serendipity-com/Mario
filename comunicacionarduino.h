#ifndef COMUNICACIONARDUINO_H
#define COMUNICACIONARDUINO_H


#include <QSerialPort>
#include <QSerialPortInfo>
#include <QObject>


class ComunicacionArduino : public QObject
{
    Q_OBJECT

private:
    QSerialPort *serial;
    QString portName;
    quint16 vendorrId;
    quint16 productId;
    bool arduino_available;
    void arduino_init();

public:
    explicit ComunicacionArduino(QObject *padre = nullptr);
    ~ComunicacionArduino();

private slots:
    void serial_read();

};

#endif // COMUNICACIONARDUINO_H
