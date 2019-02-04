# !/bin/bash

# GEARSytem - Installation file
# GEAR - Grupo de Estudos Avancados em Robotica
# Department of Electrical Engineering, University of Sao Paulo
# http://www.sel.eesc.usp.br/gear
# This file is part of the GEARSystem project


# Install GEARSystem library
make install

# Cleans old headers
if [ -d /usr/include/GEARSystem ];
    then
        if [ -w /usr/include/GEARSystem ];
            then
                rm -rf /usr/include/GEARSystem

            else
                echo ""
                echo ">> GEARSystem: Error in library headers installation!! (Are you root??)"
                exit 1
        fi
fi

# Copies GEARSystem library headers
if [ -w /usr/include ];
    then
        mkdir /usr/include/GEARSystem

    else
        echo ""
        echo ">> GEARSystem: Error in library headers installation!! (Are you root??)"
        exit 1
fi

if [ -d /usr/include/GEARSystem ];
    then
        cp -rf include/GEARSystem/* /usr/include/GEARSystem
        echo ""
        echo ">> GEARSystem: Installation complete!!"

    else
        echo ""
        echo ">> GEARSystem: Error in library headers installation!! (Are you root??)"
        exit 1
fi
