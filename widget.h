#ifndef WIDGET_H
#define WIDGET_H

#include "menujugador.h"
#include "menumultijugador.h"
#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void unJugador();
    void multiJugador();


private:
    Ui::Widget *ui;
    MenuJugador *menuJugador;
    MenuMultijugador *menuMultijugador;
};
#endif // WIDGET_H
