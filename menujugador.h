#ifndef MENUJUGADOR_H
#define MENUJUGADOR_H

#include <QWidget>
#include <map>
#include <QList>
#include <QString>
#include <QFile>
#include <QTextStream>

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

public: //private?
    void construirInformacion();

private slots:

    void cargarPartida();
    void nuevaPartida();

private:
    Ui::MenuJugador *ui;
    map <QString, QList<int>> informacion;

};

#endif // MENUJUGADOR_H
