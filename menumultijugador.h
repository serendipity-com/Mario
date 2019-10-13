#ifndef MENUMULTIJUGADOR_H
#define MENUMULTIJUGADOR_H

#include <QWidget>

namespace Ui {
class MenuMultijugador;
}

class MenuMultijugador : public QWidget
{
    Q_OBJECT

public:
    explicit MenuMultijugador(QWidget *parent = nullptr);
    ~MenuMultijugador();

private:
    Ui::MenuMultijugador *ui;
};

#endif // MENUMULTIJUGADOR_H
