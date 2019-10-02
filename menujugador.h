#ifndef MENUJUGADOR_H
#define MENUJUGADOR_H

#include <QWidget>

namespace Ui {
class MenuJugador;
}

class MenuJugador : public QWidget
{
    Q_OBJECT

public:
    explicit MenuJugador(QWidget *parent = 0);
    ~MenuJugador();

private slots:


    void on_CargarPartida_clicked();

    void on_NuevaPartida_clicked();

private:
    Ui::MenuJugador *ui;
};

#endif // MENUJUGADOR_H
