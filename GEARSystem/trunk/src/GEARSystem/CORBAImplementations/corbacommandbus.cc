/*** GEARSystem - CORBA CommandBus implementation
  ** GEAR - Grupo de Estudos Avancados em Robotica
  ** Department of Electrical Engineering, University of Sao Paulo
  ** http://www.sel.eesc.usp.br/gear
  ** This file is part of the GEARSystem project
  ***/


// Includes the class header
#include <GEARSystem/CORBAImplementations/corbacommandbus.hh>


// Includes GEARSystem
#include <GEARSystem/commandbus.hh>


// Selects namespace
using namespace GEARSystem;


/*** Constructor
  ** Description: Creates the command bus
  ** Receives:    [commandBus] The GEARSystem::CommandBus this object will control
  ***/
CORBAImplementations::CommandBus::CommandBus(GEARSystem::CommandBus* commandBus) {
    // Sets the command bus
    _commandBus = commandBus;
}


/*** 'addActuator'
  ** Description: Adds an actuator to the command bus
  ** Receives:    [name]    The actuator name
                  [address] The actuator corba address
  ** Returns:     Nothing
  ***/
void CORBAImplementations::CommandBus::addActuator(const char* name, const char* address) {
    // Adds the actuator to the command bus
    _commandBus->addActuator(QString(name), QString(address));
}

/*** 'delActuator'
  ** Description: Deletes an actuator from the command bus
  ** Receives:    [name] The actuator name
  ** Returns:     Nothing
  ***/
void CORBAImplementations::CommandBus::delActuator(const char* name) {
    // Deletes the actuator to the command bus
    _commandBus->delActuator(QString(name));
}
