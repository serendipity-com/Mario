#ifndef INSTRUCCIONES_H
#define INSTRUCCIONES_H

#include <QDialog>

namespace Ui {
class Instrucciones;
}

class Instrucciones : public QDialog
{
    Q_OBJECT

public:
    explicit Instrucciones(QWidget *parent = 0);
    ~Instrucciones();

private slots:
    void cerrar();

private:
    Ui::Instrucciones *ui;

};

#endif // INSTRUCCIONES_H
