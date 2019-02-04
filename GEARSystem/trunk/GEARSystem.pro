# GEARSystem - Project file
# GEAR - Grupo de Estudos Avancados em Robotica
# Department of Electrical Engineering, University of Sao Paulo
# http://www.sel.eesc.usp.br/gear
# This file is part of the GEARSystem project


# Application info
TEMPLATE = lib
DESTDIR  = lib
TARGET   = GEARSystem
VERSION  = 2.1.1
CONFIG  += c++14


# Qt info
QT -= gui


# Temporary dirs
OBJECTS_DIR = tmp/obj


# Compilation flags
QMAKE_CXXFLAGS_RELEASE = -O2 -Wfloat-equal -Wshadow -Woverloaded-virtual
# -Wold-style-cast
count(arch, 1) {
    QMAKE_CXXFLAGS_RELEASE += -march=$$arch
}


# Libraries definitions
LIBS *= -lomniORB4 -lomnithread


# Project files
INCLUDEPATH *= include

HEADERS     += include/GEARSystem/namespace.hh \
               include/GEARSystem/gearsystem.hh \
               include/GEARSystem/Types/types.hh \
               include/GEARSystem/Types/angle.hh \
               include/GEARSystem/Types/angularspeed.hh \
               include/GEARSystem/Types/field.hh \
               include/GEARSystem/Types/goal.hh \
               include/GEARSystem/Types/position.hh \
               include/GEARSystem/Types/velocity.hh \
               include/GEARSystem/Types/team.hh \
               include/GEARSystem/CORBAImplementations/corbainterfaces.hh \
               include/GEARSystem/CORBAImplementations/corbaactuator.hh \
               include/GEARSystem/CORBAImplementations/corbacommandbus.hh \
               include/GEARSystem/CORBAImplementations/corbacontroller.hh \
               include/GEARSystem/CORBAImplementations/corbasensor.hh \
               include/GEARSystem/actuator.hh \
               include/GEARSystem/controller.hh \
               include/GEARSystem/sensor.hh \
               include/GEARSystem/server.hh \
               include/GEARSystem/commandbus.hh \
               include/GEARSystem/worldmap.hh

SOURCES     += src/GEARSystem/Types/angle.cc \
               src/GEARSystem/Types/angularspeed.cc \
               src/GEARSystem/Types/field.cc \
               src/GEARSystem/Types/goal.cc \
               src/GEARSystem/Types/position.cc \
               src/GEARSystem/Types/velocity.cc \
               src/GEARSystem/Types/team.cc \
               src/GEARSystem/CORBAImplementations/corbainterfacesSK.cc \
               src/GEARSystem/CORBAImplementations/corbaactuator.cc \
               src/GEARSystem/CORBAImplementations/corbacommandbus.cc \
               src/GEARSystem/CORBAImplementations/corbacontroller.cc \
               src/GEARSystem/CORBAImplementations/corbasensor.cc \
               src/GEARSystem/actuator.cc \
               src/GEARSystem/controller.cc \
               src/GEARSystem/sensor.cc \
               src/GEARSystem/server.cc \
               src/GEARSystem/commandbus.cc \
               src/GEARSystem/worldmap.cc

OTHER_FILES += README.txt \
               pre-build.sh \
               build/corba_skeletons.sh \
               include/GEARSystem/CORBAImplementations/corbainterfaces.idl \
               install.sh


# Installation path
count(install_path, 0) {
    target.path = /usr/lib64/
}

count(install_path, 1) {
    target.path = $$install_path
}

INSTALLS += target


# Debug messages configuration
count(debug_msg, 0):        DEFINES += GSDEBUGMSG
contains(debug_msg, true):  DEFINES += GSDEBUGMSG
contains(debug_msg, false): DEFINES -= GSDEBUGMSG


# Thread-safe configuration
#count(thread-safe, 0):        DEFINES -= GSTHREADSAFE
#contains(thread-safe, true):  DEFINES += GSTHREADSAFE
#contains(thread-safe, false): DEFINES -= GSTHREADSAFE
DEFINES -= GSTHREADSAFE
