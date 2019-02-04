/*** GEARSystem - CORBA CommandBus class
  ** GEAR - Grupo de Estudos Avancados em Robotica
  ** Department of Electrical Engineering, University of Sao Paulo
  ** http://www.sel.eesc.usp.br/gear
  ** This file is part of the GEARSystem project
  ***/


// Prevents multiple definitions
#ifndef GSCORBACOMMANDBUS
#define GSCORBACOMMANDBUS


// Includes GEARSystem
#include <GEARSystem/namespace.hh>
#include <GEARSystem/Types/types.hh>
#include <GEARSystem/commandbus.hh>
#include <GEARSystem/CORBAImplementations/corbainterfaces.hh>


/*** 'CommandBus' class
  ** Description: This class implements the CommandBus CORBA interface
  ** Comments:
  ***/
class GEARSystem::CORBAImplementations::CommandBus : public POA_GEARSystem::CORBAInterfaces::CommandBus {
    private:
        // Command bus
        GEARSystem::CommandBus* _commandBus;


    public:
        /*** Constructor
          ** Description: Creates the command bus
          ** Receives:    [commandBus] The GEARSystem::CommandBus this object will control
          ***/
        CommandBus(GEARSystem::CommandBus* commandBus);


    public:
        /*** 'addActuator'
          ** Description: Adds an actuator to the server
          ** Receives:    [name]    The actuator name
                          [address] The actuator corba address
          ** Returns:     Nothing
          ***/
        virtual void addActuator(const char* name, const char* address);

        /*** 'delActuator'
          ** Description: Deletes an actuator from the server
          ** Receives:    [name] The actuator name
          ** Returns:     Nothing
          ***/
        virtual void delActuator(const char* name);
};


#endif
