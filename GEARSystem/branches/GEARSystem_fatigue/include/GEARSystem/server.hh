/*** GEARSystem - Server class
  ** GEAR - Grupo de Estudos Avancados em Robotica
  ** Department of Electrical Engineering, University of Sao Paulo
  ** http://www.sel.eesc.usp.br/gear
  ** This file is part of the GEARSystem project
  ***/


// Prevents multiple definitions
#ifndef GSSERVER
#define GSSERVER


// Includes GEARSystem
#include <GEARSystem/namespace.hh>
#include <GEARSystem/Types/types.hh>
#include <GEARSystem/CORBAImplementations/corbacontroller.hh>
#include <GEARSystem/CORBAImplementations/corbasensor.hh>
#include <GEARSystem/CORBAImplementations/corbacommandbus.hh>


// Includes omniORB 4
#include <omniORB4/CORBA.h>


// Selects namespace
using namespace GEARSystem;


/*** 'Server' class
  ** Description: This class exchanges local and CORBA objects
  ** Comments:
  ***/
class GEARSystem::Server {
    private:
        // CORBA objects
        CORBA::ORB_var               _orb;
        PortableServer::POA_var      _poa;
        CosNaming::NamingContext_var _nameService;

        // Controlled objects
        CORBAImplementations::Controller* _controller;
        CORBAImplementations::Sensor*     _sensor;
        CORBAImplementations::CommandBus* _commandBus;

        // Info flags
        bool _initialized;
        bool _running;


    public:
        /*** Constructor
          ** Description: Creates the server
          ** Receives:    [controller] The Controller the server will handle
                          [sensor]     The Sensor the server will handle
                          [commandBus] The Command Bus the server will handle
          ***/
        Server(CORBAImplementations::Controller* controller, CORBAImplementations::Sensor* sensor,
               CORBAImplementations::CommandBus* commandBus);


    public:
        /*** 'initialize' function
          ** Description: Initializes the server
          ** Receives:    Nothing
          ** Returns:     'true' if everything went OK, 'false' otherwise
          ***/
        bool initialize();

        /*** 'start' function
          ** Description: Starts the server
          ** Receives:    Nothing
          ** Returns:     Nothing
          ***/
        void start();

        /*** 'stop' function
          ** Description: Stops the server
          ** Receives:    Nothing
          ** Returns:     Nothing
          ***/
        void stop();


    public:
        /*** Info functions
          ** Description: Gets information about the server
          ** Receives:    Nothing
          ** Returns:     The wanted information
          ***/
        bool isInitialized() const;
        bool isRunning()     const;


    private:
        /*** 'bindController' function
          ** Description: Binds the controller at the name service
          ** Receives:    Nothing
          ** Returns:     'true' if everything went OK, 'false' otherwise
          ***/
        bool bindController();

        /*** 'bindSensor' function
          ** Description: Binds the sensor at the name service
          ** Receives:    Nothing
          ** Returns:     'true' if everything went OK, 'false' otherwise
          ***/
        bool bindSensor();

        /*** 'bindCommandBus' function
          ** Description: Binds the commandbus at the name service
          ** Receives:    Nothing
          ** Returns:     'true' if everything went OK, 'false' otherwise
          ***/
        bool bindCommandBus();

        /*** 'bindObjectToName' function
          ** Description: Binds an object to a name
          ** Receives:    [objectReference] The object that must be bind
                          [objectName]      The wanted name
          ** Returns:     'true' if everything went OK, 'false' otherwise
          ***/
        bool bindObjectToName(CORBA::Object_ptr objectReference, CosNaming::Name objectName);
};


#endif
