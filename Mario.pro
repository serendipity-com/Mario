QT       += core gui serialport
QT       += multimedia\
            core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    administradorarduino.cpp \
    administradorsonidos.cpp \
    backgrounditem.cpp \
    bandera.cpp \
    castillo.cpp \
    fantasma.cpp \
    florfuego.cpp \
    ladrillonota.cpp \
    ladrillosorpresa.cpp \
    main.cpp \
    menumultijugador.cpp \
    niveldos.cpp \
    personaje.cpp \
    personajefisica.cpp \
    puntaje.cpp \
    tubo.cpp \
    flor.cpp \
    goomba.cpp \
    resultados.cpp \
    moneda.cpp \
    hongo.cpp \
    ladrillo.cpp \
    niveluno.cpp \
    menujugador.cpp \
    widget.cpp \
    instrucciones.cpp

HEADERS += \
    administradorarduino.h \
    administradorsonidos.h \
    backgrounditem.h \
    bandera.h \
    castillo.h \
    fantasma.h \
    florfuego.h \
    ladrillonota.h \
    ladrillosorpresa.h \
    menumultijugador.h \
    niveldos.h \
    personaje.h \
    personajefisica.h \
    puntaje.h \
    tubo.h \
    flor.h \
    goomba.h \
    resultados.h \
    moneda.h \
    hongo.h \
    ladrillo.h \
    niveluno.h \
    menujugador.h \
    widget.h \
    instrucciones.h

FORMS += \
    menujugador.ui \
    widget.ui \
    instrucciones.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Fuente.qrc \
    Imagenes.qrc \
    Sonidos.qrc

DISTFILES +=
