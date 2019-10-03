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

    void cargarPartida();
    void nuevaPartida();

private:
    Ui::MenuJugador *ui;
};

#endif // MENUJUGADOR_H
