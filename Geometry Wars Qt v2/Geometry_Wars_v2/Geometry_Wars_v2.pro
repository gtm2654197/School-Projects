TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11

SOURCES += main.cpp \
    game.cpp \
    player.cpp \
    enemy.cpp \
    blue.cpp \
    weapon.cpp \
    weapont1.cpp \
    purple.cpp \
    green.cpp \
    pink.cpp \
    smallpink.cpp \
    weapont2.cpp \
    weapont3.cpp

include(deployment.pri)
qtcAddDeployment()

LIBS += -L"../SFML/lib"
LIBS += -L"../SFML/bin"

CONFIG(release, debug|release): LIBS += -lsfml-audio -lsfml-graphics -lsfml-system -lsfml-network -lsfml-window #ORDER MATTERS!
CONFIG(debug, debug|release): LIBS += -lsfml-audio -lsfml-graphics -lsfml-system -lsfml-network -lsfml-window

INCLUDEPATH += "../SFML/include"
DEPENDPATH += "../SFML/include"

HEADERS += \
    game.h \
    player.h \
    constants.h \
    enemy.h \
    blue.h \
    weapon.h \
    weapont1.h \
    purple.h \
    green.h \
    pink.h \
    smallpink.h \
    expparticles.h \
    weapont2.h \
    weapont3.h
