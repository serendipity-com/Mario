#ifndef COMUNICACIONARDUINO_H
#define COMUNICACIONARDUINO_H

//#include <QWidget>
#include <QSerialPort> //Antes de incluir la libreria colocar serialport en el .pro del proyecto
#include <QSerialPortInfo>

//namespace Ui {
//class ComunicacionArduino;
//}

class ComunicacionArduino : /*public QWidget*/
{
//    Q_OBJECT

private:
    Ui::ComunicacionArduino *ui;
    QSerialPort *serial;
    QString portName;
    quint16 vendorrId;
    quint16 productId;
    bool arduino_available;
    void arduino_init();

public:
    ComunicacionArduino();
//    explicit ComunicacionArduino(QWidget *parent = 0);
    ~ComunicacionArduino();

private slots:
    void serial_read();

};

#endif // COMUNICACIONARDUINO_H
