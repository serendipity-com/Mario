#include "widget.h"
#include <QApplication>
#include <QSplashScreen>
#include <QTimer>

#include "niveluno.h"
#include <QGraphicsView>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//    //Agrga Splash a la pantalla
//    QSplashScreen *splash = new QSplashScreen();
//    splash->setPixmap(QPixmap(":/Imagenes/mario_splash.png"));
//    splash->show();


    Widget w;
    w.show();
//    NivelUno escena;
//    QGraphicsView view;
//    view.setRenderHint(QPainter::Antialiasing);
//    view.setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
//    view.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
//    view.setScene(&escena);
//    view.setFixedSize(1280,720);


//    QTimer::singleShot(2500,splash,SLOT(close()));
//    QTimer::singleShot(2500,&view,SLOT(show()));
    return a.exec();
}
