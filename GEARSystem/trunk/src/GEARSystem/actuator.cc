/*** GEARSystem - Actuator implementation
  ** GEAR - Grupo de Estudos Avancados em Robotica
  ** Department of Electrical Engineering, University of Sao Paulo
  ** http://www.sel.eesc.usp.br/gear
  ** This file is part of the GEARSystem project
  ***/


// Includes the class header
#include <GEARSystem/actuator.hh>


// Includes IO streams
#include <iostream>

// Includes C string library
#include <cstring>

// Includes Qt library
#include <QtCore/QtCore>

// Includes omniORB 4
#include <omniORB4/CORBA.h>


// Selects namespace
using namespace GEARSystem;
using std::cerr;
using std::endl;
using std::flush;


/*** Constructor
  ** Description: Creates the actuator
  ** Receives:    [name] The actuator name
  ***/
Actuator::Actuator(const QString& name) {
    // Initializes the variables
    _corbaActuator        = new CORBAImplementations::Actuator(this);
    _corbaCommandBus      = NULL;
    _name                 = name;
    _isConnected          = false;
    _serverPort           = 0;
    _serverAddress.clear();

    _orb         = NULL;
    _poa         = NULL;
    _nameService = NULL;
}

/*** Destructor
  ** Description: Destroys the actuator
  ** Receives:    Nothing
  ***/
Actuator::~Actuator() {
    disconnect();
}


/*** 'connect' function
  ** Description: Connects to the server
  ** Receives:    [address] The server address
                  [port]    The server port
  ** Returns:     'true' if the connection was established, 'false' otherwise
  ***/
bool Actuator::connect(const QString& address, uint16 port) {
    // Intializes CORBA objects
    try {
        // Initializes ORB
        int dummy = 0;
        _orb = CORBA::ORB_init(dummy, NULL);

        // Leaves if any error occourred
        if (CORBA::is_nil(_orb)) {
            _orb         = NULL;
            _poa         = NULL;
            _nameService = NULL;

            #ifdef GSDEBUGMSG
            cerr << ">> GEARSystem: Actuator::connect(const QString&, uint16): Could not initialize ORB!!";
            cerr << endl << flush;
            #endif

            return(false);
        }

        // Gets POA reference
        CORBA::Object_var obj;
        obj = _orb->resolve_initial_references("RootPOA");

        // Narrows it to poa
        _poa = PortableServer::POA::_narrow(obj);

        // Leaves if any error occourred
        if (CORBA::is_nil(_poa)) {
            _orb         = NULL;
            _poa         = NULL;
            _nameService = NULL;

            #ifdef GSDEBUGMSG
            cerr << ">> GEARSystem: Actuator::connect(const QString&, uint16): ";
            cerr << "Could not resolve POA!!" <<endl << flush;
            #endif

            return(false);
        }

        // Gets NameService reference
        obj = _orb->resolve_initial_references("NameService");

        // Narrows it to nameService
        _nameService = CosNaming::NamingContext::_narrow(obj);

        // Leaves if any error occourred
        if (CORBA::is_nil(_nameService)) {
            _orb         = NULL;
            _poa         = NULL;
            _nameService = NULL;

            #ifdef GSDEBUGMSG
            cerr << ">> GEARSystem: Actuator::connect(const QString&, uint16): ";
            cerr << "Could not resolve NameService!!" <<endl << flush;
            #endif

            return(false);
        }
    }

    // Catches CORBA exceptions and leave
    catch (CORBA::Exception& exception) {
        _orb         = NULL;
        _poa         = NULL;
        _nameService = NULL;

        #ifdef GSDEBUGMSG
        cerr << ">> GEARSystem: Actuator::connect(const QString&, uint16): Caught CORBA exception: ";
        cerr << exception._name() << "!!" << endl << flush;
        #endif

        return(false);
    }

    // Gets the command bus
    bool ok;
    ok = getCommandBus(address, port);
    if (!ok) {
        _orb         = NULL;
        _poa         = NULL;
        _nameService = NULL;
        return(false);
    }

    // Binds the actuator
    ok = bindToServer();
    if (!ok) {
        _orb         = NULL;
        _poa         = NULL;
        _nameService = NULL;
        return(false);
    }

    // Activates the POA Manager
    _poa->the_POAManager()->activate();

    // Adds the actuator to the server
    _corbaCommandBus->addActuator(_name.toStdString().c_str(), _orb->object_to_string(_corbaActuator->_this()));

    // Sets as connected
    _serverAddress = address;
    _serverPort    = port;
    _isConnected   = true;

    // Returns 'true' if everything went OK
    return(true);
}

/*** 'disconnect' function
  ** Description: Disconnects from the server
  ** Receives:    Nothing
  ** Returns:     Nothing
  ***/
void Actuator::disconnect() {
    if (isConnected()) {
        // Deletes the actuator from the server
        _corbaCommandBus->delActuator(_name.toStdString().c_str());

        // Sets as disconnected
        _serverAddress.clear();
        _serverPort  = 0;
        _isConnected = false;
    }
}

/*** 'isConnected' function
  ** Description: Verifies if the actuator is connected to the server
  ** Receives:    Nothing
  ** Returns:     'true' if the connection was established, 'false' otherwise
  ***/
bool Actuator::isConnected() const { return(_isConnected); }


/*** 'bindToServer' function
  ** Description: Binds the actuator at the name service
  ** Receives:    Nothing
  ** Returns:     'true' if everything went OK, 'false' otherwise
  ***/
bool Actuator::bindToServer() {
    // Activates the actuator at POA
    (void) _poa->activate_object(_corbaActuator);

    // Binds it to a name
    CORBA::Object_var objectReference;
    objectReference = _corbaActuator->_this();

    CosNaming::Name objectName;
    char* name;
    name = new char[_name.length()];
    strcpy(name, _name.toStdString().c_str());
    objectName.length(1);
    objectName[0].id   = "GEARSystem";
    objectName[0].kind = name;

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
        cerr << ">> GEARSystem: Actuator::bindToServer(): ";
        cerr << "Caught CORBA exception: ";
        cerr << exception._name() << "!!" << endl << flush;
        #endif

        return(false);
    }

    // Removes its reference
    _corbaActuator->_remove_ref();

    // Returns 'true' if everything went OK
    return(true);
}


/*** 'getCommandBus' function
  ** Description: Connects to the remote command bus
  ** Receives:    [address] The server address
                  [port]    The server port
  ** Returns:     'true' if everything went OK, 'false' otherwise
  ***/
bool Actuator::getCommandBus(const QString& address, uint16 port) {
    // Connects to the command bus
    try {
        // Sets the CORBA CommandBus address
        QString commandBusAddr("corbaname::");
        commandBusAddr.append(address);
        if (port != 0) {
            commandBusAddr.append(":");
            commandBusAddr.append(QString("%1").arg(port));
        }
        commandBusAddr.append("#GEARSystem.CommandBus");

        // Gets the CORBA CommandBus reference
        CORBA::Object_var obj;
        obj = _orb->string_to_object(commandBusAddr.toStdString().c_str());
        if (CORBA::is_nil(obj)) {
            _corbaCommandBus = NULL;

            #ifdef GSDEBUGMSG
            cerr << ">> GEARSystem: Actuator::getCommandBus(const QString&, uint16): ";
            cerr << "Could not connect to the server at " << address.toStdString() << ":" << port << "!!";
            cerr << endl << flush;
            #endif

            return(false);
        }

        // Narrows it to the local object
        _corbaCommandBus = CORBAInterfaces::CommandBus::_narrow(obj);
        if (CORBA::is_nil(_corbaCommandBus)) {
            _corbaCommandBus = NULL;

            #ifdef GSDEBUGMSG
            cerr << ">> GEARSystem: Actuator::getCommandBus(const QString&, uint16): ";
            cerr << "Could not connect to the server at " << address.toStdString() << ":" << port << "!!";
            cerr << endl << flush;
            #endif

            return(false);
        }
    }

    // Catches CORBA exceptions and leaves
    catch (CORBA::Exception& exception) {
        _corbaCommandBus = NULL;

        #ifdef GSDEBUGMSG
        cerr << ">> GEARSystem: Actuator::getCommandBus(const QString&, uint16): ";
        cerr << "Caught CORBA exception: " << exception._name() << "!!" << endl << flush;
        #endif

        return(false);
    }

    // Returns 'true' if everything went OK
    return(true);
}
