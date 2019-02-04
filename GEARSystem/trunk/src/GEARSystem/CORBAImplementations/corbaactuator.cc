/*** GEARSystem - CORBA Actuator implementation
  ** GEAR - Grupo de Estudos Avancados em Robotica
  ** Department of Electrical Engineering, University of Sao Paulo
  ** http://www.sel.eesc.usp.br/gear
  ** This file is part of the GEARSystem project
  ***/


// Includes the class header
#include <GEARSystem/CORBAImplementations/corbaactuator.hh>


// Includes omniORB 4
#include <omniORB4/CORBA.h>

// Includes GEARSystem
#include <GEARSystem/actuator.hh>


// Selects namespace
using namespace GEARSystem;
using CORBA::Boolean;
using CORBA::Float;
using CORBA::Octet;


/*** Constructor
  ** Description: Creates the actuator
  ** Receives:    [actuator] The GEARSystem::Actuator this object will control
  ***/
CORBAImplementations::Actuator::Actuator(GEARSystem::Actuator* actuator) {
    // Sets the actuator
    _actuator = actuator;
}


/*** 'setSpeed'
  ** Description: Sets a player speed
  ** Receives:    [teamNum]   The team number
                  [playerNum] The team number
                  [x]         The x speed component
                  [y]         The y speed component
                  [theta]     The angular speed
  ** Returns:     Nothing
  ***/
void CORBAImplementations::Actuator::setSpeed(Octet teamNum, Octet playerNum, Float x, Float y, Float theta) {
    // Sends the command via the actuator
    _actuator->setSpeed(teamNum, playerNum, x, y, theta);
}

/*** 'kick'
  ** Description: Activates the player kicking device
  ** Receives:    [teamNum]   The team number
                  [playerNum] The team number
                  [power]     The kick power
  ** Returns:     Nothing
  ***/
void CORBAImplementations::Actuator::kick(Octet teamNum, Octet playerNum, Float power) {
    // Sends the command via the actuator
    _actuator->kick(teamNum, playerNum, power);
}

/*** 'chipKick'
  ** Description: Activates the player chip-kicking device
  ** Receives:    [teamNum]   The team number
                  [playerNum] The team number
                  [power]     The kick power
  ** Returns:     Nothing
  ***/
void CORBAImplementations::Actuator::chipKick(Octet teamNum, Octet playerNum, Float power) {
    // Sends the command via the actuator
    _actuator->chipKick(teamNum, playerNum, power);
}

/*** 'kickOnTouch'
  ** Description: Activates the player kicking device when the ball touches it
  ** Receives:    [teamNum]   The team number
                  [playerNum] The team number
                  [enable]    'true' if the player must kick on touch,
                              'false' otherwise
                  [power]     The kick power
  ** Returns:     Nothing
  ***/
void CORBAImplementations::Actuator::kickOnTouch(Octet teamNum, Octet playerNum, Boolean enable, Float power) {
    // Sends the command via the actuator
    _actuator->kickOnTouch(teamNum, playerNum, enable, power);
}

/*** 'chipKickOnTouch'
  ** Description: Activates the player chip-kicking device when the ball touches it
  ** Receives:    [teamNum]   The team number
                  [playerNum] The team number
                  [enable]    'true' if the player must kick on touch,
                              'false' otherwise
                  [power]     The kick power
  ** Returns:     Nothing
  ***/
void CORBAImplementations::Actuator::chipKickOnTouch(Octet teamNum, Octet playerNum, Boolean enable, Float power) {
    // Sends the command via the actuator
    _actuator->chipKickOnTouch(teamNum, playerNum, enable, power);
}

/*** 'holdBall'
  ** Description: Activates the player ball holding device
  ** Receives:    [teamNum]   The team number
                  [playerNum] The team number
                  [enable]    'true' if the player must hold the ball,
                              'false' otherwise
  ** Returns:     Nothing
  ***/
void CORBAImplementations::Actuator::holdBall(Octet teamNum, Octet playerNum, Boolean enable) {
    // Sends the command via the actuator
    _actuator->holdBall(teamNum, playerNum, enable);
}
