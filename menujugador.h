#ifndef MENUJUGADOR_H
#define MENUJUGADOR_H

#include <QWidget>
#include <map>
#include <QList>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QDataStream>

using namespace std;
namespace Ui {
class MenuJugador;
}

class MenuJugador : public QWidget
{
    Q_OBJECT
public:
    explicit MenuJugador(QWidget *parent = 0);
    ~MenuJugador();
    void construirInformacion();

private slots:
    void enter();
    void cargarPartida();
    void nuevaPartida();

private:
    Ui::MenuJugador *ui;
    map <QString, QList<int>> informacion;

};

#endif // MENUJUGADOR_H
