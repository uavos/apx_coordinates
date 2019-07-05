#-------------------------------------------------
#
# Project created by QtCreator 2019-03-20T14:09:35
#
#-------------------------------------------------

QT += quick widgets positioning

TARGET = apx_coordinates
TEMPLATE = lib

CONFIG += plugin c++14 silent

DESTDIR = bin
OBJECTS_DIR = obj
UI_DIR = $$OBJECTS_DIR
MOC_DIR = $$OBJECTS_DIR
target.path = ~/Документы/UAVOS/Plugins/
INSTALLS += target

SOURCES += \
    apxcoordinates.cpp \
    apxcoordinatesplugin.cpp

HEADERS += \
    apxcoordinates.h \
    apxcoordinatesplugin.h

INCLUDEPATH += /home/pavel/sources/build-apx-release/packages/sdk/include
LIBS += -L/home/pavel/sources/build-apx-release/packages/sdk/lib \
    -lApxCore \
    -lApxData \
    -ApxGcs
