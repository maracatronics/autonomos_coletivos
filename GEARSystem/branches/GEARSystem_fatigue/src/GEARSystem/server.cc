/*** GEARSystem - Server implementation
  ** GEAR - Grupo de Estudos Avancados em Robotica
  ** Department of Electrical Engineering, University of Sao Paulo
  ** http://www.sel.eesc.usp.br/gear
  ** This file is part of the GEARSystem project
  ***/


// Includes the class header
#include <GEARSystem/server.hh>


// Includes IO streams
#include <iostream>

// Includes omniORB 4
#include <omniORB4/CORBA.h>

// Includes GEARSystem
#include <GEARSystem/CORBAImplementations/corbacontroller.hh>
#include <GEARSystem/CORBAImplementations/corbasensor.hh>
#include <GEARSystem/CORBAImplementations/corbacommandbus.hh>


// Selects namespace
using namespace GEARSystem;
using std::cerr;
using std::endl;
using std::flush;


/*** Constructor
  ** Description: Creates the server
  ** Receives:    [controller] The Controller the server will handle
                  [sensor]     The Sensor the server will handle
                  [commandBus] The Command Bus the server will handle
  ***/
Server::Server(CORBAImplementations::Controller* controller, CORBAImplementations::Sensor* sensor,
               CORBAImplementations::CommandBus* commandBus) {
    // Initializes the variables
    _orb = NULL;
    _poa = NULL;
    _nameService = NULL;
    _initialized = false;
    _running     = false;

    // Sets the controlled elements
    _controller = controller;
    _sensor     = sensor;
    _commandBus = commandBus;
}


/*** 'initialize' function
  ** Description: Initializes the server
  ** Receives:    Nothing
  ** Returns:     'true' if everything went OK, 'false' otherwise
  ***/
bool Server::initialize() {
    // Intializes server objects
    try {
        // Initializes ORB
        int dummy = 0;
        _orb = CORBA::ORB_init(dummy, NULL);

        // Leaves if any error occourred
        if (CORBA::is_nil(_orb)) {
            _orb = NULL;

            #ifdef GSDEBUGMSG
            cerr << ">> GEARSystem: Server::initialize(): Could not initialize ORB!!" << endl << flush;
            #endif

            return(false);
        }


        // Gets POA reference
        CORBA::Object_var obj;
        obj = _orb->resolve_initial_references("RootPOA");

        // Narrows it to _poa
        _poa = PortableServer::POA::_narrow(obj);

        // Leaves if any error occourred
        if (CORBA::is_nil(_poa)) {
            _orb = NULL;
            _poa = NULL;

            #ifdef GSDEBUGMSG
            cerr << ">> GEARSystem: Server::initialize(): Could not initialize POA!!" << endl << flush;
            #endif

            return(false);
        }


        // Gets NameService reference
        obj = _orb->resolve_initial_references("NameService");

        // Narrows it to _nameService
        _nameService = CosNaming::NamingContext::_narrow(obj);

        // Leaves if any error occourred
        if (CORBA::is_nil(_nameService)) {
            _orb = NULL;
            _poa = NULL;
            _nameService = NULL;

            #ifdef GSDEBUGMSG
            cerr << ">> GEARSystem: Server::initialize(): Could not initialize NameService!!" << endl << flush;
            #endif

            return(false);
        }
    }

    // Catches CORBA exceptions and leave
    catch (CORBA::Exception& exception) {
        _orb = NULL;
        _poa = NULL;
        _nameService = NULL;

        #ifdef GSDEBUGMSG
        cerr << ">> GEARSystem: Server::initialize(): Caught CORBA exception: ";
        cerr << exception._name() << "!!" << endl << flush;
        #endif

        return(false);
    }

    // Binds the controller
    bool ok;
    ok = bindController();
    if (!ok) {
        return(false);
    }

    // Binds the sensor
    ok = bindSensor();
    if (!ok) {
        return(false);
    }

    // Binds the command bus
    ok = bindCommandBus();
    if (!ok) {
        return(false);
    }

    // Activates the POA Manager
    _poa->the_POAManager()->activate();

    // Sets it as initialized
    _initialized = true;

    // Returns 'true' if everything went OK
    return(true);
}

/*** 'start' function
  ** Description: Starts the server
  ** Receives:    Nothing
  ** Returns:     Nothing
  ***/
void Server::start() {
    // Starts the server
    if (isInitialized()) {
        _running = true;
        _orb->run();
    }

    // Prints an error message
    else {
        #ifdef GSDEBUGMSG
        cerr << ">> GEARSystem: Server::start(): The server is not initialized!!" << endl << flush;
        #endif
    }
}

/*** 'stop' function
  ** Description: Stops the server
  ** Receives:    Nothing
  ** Returns:     Nothing
  ***/
void Server::stop() {
    // Stops the server
    if (isRunning()) {
        _orb->shutdown(1);
        _running = false;
    }

    // Prints an error message
    else {
        #ifdef GSDEBUGMSG
        cerr << ">> GEARSystem: Server::stop(): The server is not running!!" << endl << flush;
        #endif
    }
}


/*** 'bindController' function
  ** Description: Binds the controller at the name service
  ** Receives:    Nothing
  ** Returns:     'true' if everything went OK, 'false' otherwise
  ***/
bool Server::bindController() {
    // Activates the controller at POA
    (void) _poa->activate_object(_controller);


    // Binds it to a name
    CORBA::Object_var objectReference;
    objectReference = _controller->_this();

    CosNaming::Name objectName;
    objectName.length(1);
    objectName[0].id   = "GEARSystem";
    objectName[0].kind = "Controller";

    bool ok;
    ok = bindObjectToName(objectReference, objectName);
    if (!ok) {
        return(false);
    }


    // Removes its reference
    _controller->_remove_ref();


    // Returns 'true' if everything went OK
    return(true);
}

/*** 'bindSensor' function
  ** Description: Binds the sensor at the name service
  ** Receives:    Nothing
  ** Returns:     'true' if everything went OK, 'false' otherwise
  ***/
bool Server::bindSensor() {
    // Activates the sensor at POA
    (void) _poa->activate_object(_sensor);


    // Binds it to a name
    CORBA::Object_var objectReference;
    objectReference = _sensor->_this();

    CosNaming::Name objectName;
    objectName.length(1);
    objectName[0].id   = "GEARSystem";
    objectName[0].kind = "Sensor";

    bool ok;
    ok = bindObjectToName(objectReference, objectName);
    if (!ok) {
        return(false);
    }


    // Removes its reference
    _sensor->_remove_ref();


    // Returns 'true' if everything went OK
    return(true);
}

/*** 'bindCommandBus' function
  ** Description: Binds the commandbus at the name service
  ** Receives:    Nothing
  ** Returns:     'true' if everything went OK, 'false' otherwise
  ***/
bool Server::bindCommandBus() {
    // Activates the sensor at POA
    (void) _poa->activate_object(_commandBus);


    // Binds it to a name
    CORBA::Object_var objectReference;
    objectReference = _commandBus->_this();

    CosNaming::Name objectName;
    objectName.length(1);
    objectName[0].id   = "GEARSystem";
    objectName[0].kind = "CommandBus";

    bool ok;
    ok = bindObjectToName(objectReference, objectName);
    if (!ok) {
        return(false);
    }


    // Removes its reference
    _commandBus->_remove_ref();


    // Returns 'true' if everything went OK
    return(true);
}

/*** 'bindObjectToName' function
  ** Description: Binds an object to a name
  ** Receives:    [objectReference] The object that must be bind
                  [objectName]      The wanted name
  ** Returns:     'true' if everything went OK, 'false' otherwise
  ***/
bool Server::bindObjectToName(CORBA::Object_ptr objectReference, CosNaming::Name objectName) {
    // Binds the object to a name
    try {
        try {
            _nameService->bind(objectName, objectReference);

        }
        catch (CosNaming::NamingContext::AlreadyBound&) {
            _nameService->rebind(objectName, objectReference);
        }
    }

    // Catches CORBA exceptions and leave
    catch (CORBA::Exception& exception) {
        #ifdef GSDEBUGMSG
        cerr << ">> GEARSystem: Server::bindObjectToName(): Caught CORBA exception: ";
        cerr << exception._name() << "!!" << endl << flush;
        #endif

        return(false);
    }

    // Returns 'true' if everything went OK
    return(true);
}


// Info functions
bool Server::isInitialized() const { return(_initialized); }
bool Server::isRunning()     const { return(_running);     }
