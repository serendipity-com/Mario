#ifndef WIDGET_H
#define WIDGET_H

#include "menujugador.h"
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


private:
    Ui::Widget *ui;
    MenuJugador *menuJugador;
};
#endif // WIDGET_H
