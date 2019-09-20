#include "widget.h"
#include <QApplication>
#include <QSplashScreen>
#include <QTimer>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //Agrga Splash a la pantalla
    QSplashScreen *splash = new QSplashScreen();
    splash->setPixmap(QPixmap(":/Imagenes/mario_splash.png"));
    splash->show();

    Widget w;

    QTimer::singleShot(2500,splash,SLOT(close()));
    QTimer::singleShot(2500,&w,SLOT(show()));
    return a.exec();
}
