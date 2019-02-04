# !/bin/bash

# GEARSytem - CORBA Skeletons generator
# GEAR - Grupo de Estudos Avancados em Robotica
# Department of Electrical Engineering, University of Sao Paulo
# http://www.sel.eesc.usp.br/gear
# This file is part of the GEARSystem project


# Generates skeletons from IDL definitions
omniidl -bcxx include/GEARSystem/CORBAImplementations/corbainterfaces.idl

# Verifies the generation
if [ -f corbainterfaces.hh ] && [ -f corbainterfacesSK.cc ];
    then
        # Copies the skeletons
        mv corbainterfaces.hh   include/GEARSystem/CORBAImplementations/corbainterfaces.hh
        mv corbainterfacesSK.cc src/GEARSystem/CORBAImplementations/corbainterfacesSK.cc

        # Patches skeletons source
        patch src/GEARSystem/CORBAImplementations/corbainterfacesSK.cc < build/corba_skeletons.diff > /dev/null

    else
        echo ">> GEARSystem: Error in CORBA skeletons generation!!"
        exit
fi
