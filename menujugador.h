#ifndef MENUJUGADOR_H
#define MENUJUGADOR_H

#include <QWidget>
#include <map>
#include <QList>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QDataStream>
#include <QDebug>

using namespace std;
namespace Ui {
class MenuJugador;
}

class MenuJugador : public QWidget
{
    Q_OBJECT
public:
    explicit MenuJugador(QWidget *parent = nullptr);
    ~MenuJugador();
    void construirInformacion();
private:
    //    void actualizarBaseDatos();
    void correrJuego();

private slots:
    void cargarPartida();
    void nuevaPartida();

private:
    Ui::MenuJugador *ui;
    QString jugadorActual;
    map <QString, QList<int>> informacion;


};

#endif // MENUJUGADOR_H
