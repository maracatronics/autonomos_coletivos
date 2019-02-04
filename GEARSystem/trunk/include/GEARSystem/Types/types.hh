/*** GEARSystem - Basic data types
  ** GEAR - Grupo de Estudos Avancados em Robotica
  ** Department of Electrical Engineering, University of Sao Paulo
  ** http://www.sel.eesc.usp.br/gear
  ** This file is part of the GEARSystem project
  ***/


// Prevents multiple definitions
#ifndef GSTYPES
#define GSTYPES

// Includes Qt library
#include <QtCore/QtCore>


// Elementary types
#define int8   qint8
#define int16  qint16
#define int32  qint32
#define uint8  quint8
#define uint16 quint16
#define uint32 quint32


// Includes other types
#include <GEARSystem/Types/angle.hh>
#include <GEARSystem/Types/angularspeed.hh>
#include <GEARSystem/Types/field.hh>
#include <GEARSystem/Types/goal.hh>
#include <GEARSystem/Types/position.hh>
#include <GEARSystem/Types/team.hh>
#include <GEARSystem/Types/velocity.hh>


#endif
