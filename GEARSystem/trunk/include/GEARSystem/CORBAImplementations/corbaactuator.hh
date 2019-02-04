/*** GEARSystem - CORBA Actuator class
  ** GEAR - Grupo de Estudos Avancados em Robotica
  ** Department of Electrical Engineering, University of Sao Paulo
  ** http://www.sel.eesc.usp.br/gear
  ** This file is part of the GEARSystem project
  ***/


// Prevents multiple definitions
#ifndef GSCORBAACTUATOR
#define GSCORBAACTUATOR


// Includes GEARSystem
#include <GEARSystem/namespace.hh>
#include <GEARSystem/Types/types.hh>
#include <GEARSystem/actuator.hh>
#include <GEARSystem/CORBAImplementations/corbainterfaces.hh>


// Includes omniORB 4
#include <omniORB4/CORBA.h>


// Selects namespace
using namespace GEARSystem;
using CORBA::Boolean;
using CORBA::Float;
using CORBA::Octet;


/*** 'Actuator' class
  ** Description: This class implements the Actuator CORBA interface
  ** Comments:
  ***/
class GEARSystem::CORBAImplementations::Actuator : public POA_GEARSystem::CORBAInterfaces::Actuator {
    private:
        // Actuator
        GEARSystem::Actuator* _actuator;


    public:
        /*** Constructor
          ** Description: Creates the actuator
          ** Receives:    [actuator] The GEARSystem::Actuator this object will control
          ***/
        Actuator(GEARSystem::Actuator* actuator);


    public:
        /*** 'setSpeed'
          ** Description: Sets a player speed
          ** Receives:    [teamNum]   The team number
                          [playerNum] The team number
                          [x]         The x speed component
                          [y]         The y speed component
                          [theta]     The angular speed
          ** Returns:     Nothing
          ***/
        virtual void setSpeed(Octet teamNum, Octet playerNum, Float x, Float y, Float theta);

        /*** 'kick'
          ** Description: Activates the player kicking device
          ** Receives:    [teamNum]   The team number
                          [playerNum] The team number
                          [power]     The kick power
          ** Returns:     Nothing
          ***/
        virtual void kick(Octet teamNum, Octet playerNum, Float power);

        /*** 'chipKick'
          ** Description: Activates the player chip-kicking device
          ** Receives:    [teamNum]   The team number
                          [playerNum] The team number
                          [power]     The kick power
          ** Returns:     Nothing
          ***/
        virtual void chipKick(Octet teamNum, Octet playerNum, Float power);

        /*** 'kickOnTouch'
          ** Description: Activates the player kicking device when the ball touches it
          ** Receives:    [teamNum]   The team number
                          [playerNum] The team number
                          [enable]    'true' if the player must kick on touch,
                                      'false' otherwise
                          [power]     The kick power
          ** Returns:     Nothing
          ***/
        virtual void kickOnTouch(Octet teamNum, Octet playerNum, Boolean enable, Float power);

        /*** 'chipKickOnTouch'
          ** Description: Activates the player chip-kicking device when the ball touches it
          ** Receives:    [teamNum]   The team number
                          [playerNum] The team number
                          [enable]    'true' if the player must kick on touch,
                                      'false' otherwise
                          [power]     The kick power
          ** Returns:     Nothing
          ***/
        virtual void chipKickOnTouch(Octet teamNum, Octet playerNum, Boolean enable, Float power);

        /*** 'holdBall'
          ** Description: Activates the player ball holding device
          ** Receives:    [teamNum]   The team number
                          [playerNum] The team number
                          [enable]    'true' if the player must hold the ball,
                                      'false' otherwise
          ** Returns:     Nothing
          ***/
        virtual void holdBall(Octet teamNum, Octet playerNum, Boolean enable);
};


#endif
