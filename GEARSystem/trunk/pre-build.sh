# !/bin/bash

# GEARSytem - Pre-build configuration file
# GEAR - Grupo de Estudos Avancados em Robotica
# Department of Electrical Engineering, University of Sao Paulo
# http://www.sel.eesc.usp.br/gear
# This file is part of the GEARSystem project

# Generates CORBA skeletons
sh build/corba_skeletons.sh

# Runs qmake
if type -p qmake-qt5 > /dev/null;
    then
        qmake-qt5 $*
        echo ">> GEARSystem: Pre-build complete with Qt 5!!"

    else
        if type -p qmake-qt4 > /dev/null;
            then
                qmake-qt4 $*
                echo ">> GEARSystem: Pre-build complete with Qt 4!!"

            else
                if type -p qmake > /dev/null;
                    then
                        qmake $*
                        echo ">> GEARSystem: Pre-build complete!!"

                    else
                        echo ">> GEARSystem: Could not generate Makefile!!"
                fi
        fi
fi
