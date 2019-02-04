/*** GEARSystem - CommandBus implementation
  ** GEAR - Grupo de Estudos Avancados em Robotica
  ** Department of Electrical Engineering, University of Sao Paulo
  ** http://www.sel.eesc.usp.br/gear
  ** This file is part of the GEARSystem project
  ***/


// Includes the class header
#include <GEARSystem/commandbus.hh>


// Inlcudes Qt library
#include <QtCore/QtCore>

// Inlcudes IO streams
#include <iostream>


// Selects namespace
using namespace GEARSystem;
using std::cerr;
using std::endl;
using std::flush;


/*** Constructor
  ** Description: Creates the bus
  ** Receives:    Nothing
  ***/
CommandBus::CommandBus() {
    // Initializes the variables
    _nActuators = 0;
    _validActuators.clear();
    _actuators.clear();

    // Creates the locks
    #ifdef GSTHREADSAFE
    _actuatorsLock = new QReadWriteLock();
    #endif
}


/*** Actuators handling functions
  ** Description: Handles the actuators
  ** Receives:    [name]    The actuator name
                  [address] The actuator address
  ** Returns:     Nothing
  ***/
void CommandBus::addActuator(const QString& name, const QString& address) {
    // Handles the lock
    #ifdef GSTHREADSAFE
    QWriteLocker actuatorsLocker(_actuatorsLock);
    #endif

    // Adds the actuator
    CORBAInterfaces::Actuator_var actuator = connectToActuator(address);
    if (actuator) {
        (void) _actuators.remove(name);
        (void) _validActuators.insert(name, true);
        _actuators[name] = actuator;
        _nActuators++;
    }
}

void CommandBus::delActuator(const QString& name) {
    // Handles the lock
    #ifdef GSTHREADSAFE
    QWriteLocker actuatorsLocker(_actuatorsLock);
    #endif

    // Deletes the actuator
    (void) _validActuators.remove(name);
    (void) _actuators.remove(name);
    _nActuators--;
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
void CommandBus::setSpeed(uint8 teamNum, uint8 playerNum, float x, float y, float theta) const {
    // Handles the lock
    #ifdef GSTHREADSAFE
    QReadLocker actuatorsLocker(_actuatorsLock);
    #endif

    // Sends the command to all actuators
    QHashIterator<QString,CORBAInterfaces::Actuator_var> it(_actuators);
    while (it.hasNext()) {
        try {
            it.next().value()->setSpeed(teamNum, playerNum, x, y, theta);
        }

        // Handles CORBA exceptions
        catch (const CORBA::Exception& exception) {
            #ifdef GSDEBUGMSG
            cerr << ">> GEARSystem: CommandBus::setSpeed(uint8, uint8, float, float, float): ";
            cerr << "Caught CORBA exception: " << exception._name() << "!!" << endl << flush;
            #endif
        }
    }
}

/*** 'kick'
  ** Description: Activates the player kicking device
  ** Receives:    [teamNum]   The team number
                  [playerNum] The team number
                  [power]     The kick power
  ** Returns:     Nothing
  ***/
void CommandBus::kick(uint8 teamNum, uint8 playerNum, float power) const {
    // Handles the lock
    #ifdef GSTHREADSAFE
    QReadLocker actuatorsLocker(_actuatorsLock);
    #endif

    // Sends the command to all actuators
    QHashIterator<QString,CORBAInterfaces::Actuator_var> it(_actuators);
    while (it.hasNext()) {
        it.next().value()->kick(teamNum, playerNum, power);
    }
}

/*** 'chipKick'
  ** Description: Activates the player chip-kicking device
  ** Receives:    [teamNum]   The team number
                  [playerNum] The team number
                  [power]     The kick power
  ** Returns:     Nothing
  ***/
void CommandBus::chipKick(uint8 teamNum, uint8 playerNum, float power) const {
    // Handles the lock
    #ifdef GSTHREADSAFE
    QReadLocker actuatorsLocker(_actuatorsLock);
    #endif

    // Sends the command to all actuators
    QHashIterator<QString,CORBAInterfaces::Actuator_var> it(_actuators);
    while (it.hasNext()) {
        it.next().value()->chipKick(teamNum, playerNum, power);
    }
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
void CommandBus::kickOnTouch(uint8 teamNum, uint8 playerNum, bool enable, float power) const {
    // Handles the lock
    #ifdef GSTHREADSAFE
    QReadLocker actuatorsLocker(_actuatorsLock);
    #endif

    // Sends the command to all actuators
    QHashIterator<QString,CORBAInterfaces::Actuator_var> it(_actuators);
    while (it.hasNext()) {
        it.next().value()->kickOnTouch(teamNum, playerNum, enable, power);
    }
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
void CommandBus::chipKickOnTouch(uint8 teamNum, uint8 playerNum, bool enable, float power) const {
    // Handles the lock
    #ifdef GSTHREADSAFE
    QReadLocker actuatorsLocker(_actuatorsLock);
    #endif

    // Sends the command to all actuators
    QHashIterator<QString,CORBAInterfaces::Actuator_var> it(_actuators);
    while (it.hasNext()) {
        it.next().value()->chipKickOnTouch(teamNum, playerNum, enable, power);
    }
}

/*** 'holdBall'
  ** Description: Activates the player ball holding device
  ** Receives:    [teamNum]   The team number
                  [playerNum] The team number
                  [enable]    'true' if the player must hold the ball,
                              'false' otherwise
  ** Returns:     Nothing
  ***/
void CommandBus::holdBall(uint8 teamNum, uint8 playerNum, bool enable) const {
    // Handles the lock
    #ifdef GSTHREADSAFE
    QReadLocker actuatorsLocker(_actuatorsLock);
    #endif

    // Sends the command to all actuators
    QHashIterator<QString,CORBAInterfaces::Actuator_var> it(_actuators);
    while (it.hasNext()) {
        it.next().value()->holdBall(teamNum, playerNum, enable);
    }
}


/*** 'connectToActuator'
  ** Description: Connects to a given actuator address
  ** Receives:    [address] The actuator address
  ** Returns:     The connected actuator
  ***/
CORBAInterfaces::Actuator_var CommandBus::connectToActuator(const QString& address) const {
    // Connects to the actuator
    CORBAInterfaces::Actuator_var corbaActuator;

    try {
        // Creates the ORB
        int dummy = 0;
        CORBA::ORB_var orb = CORBA::ORB_init(dummy, NULL);
        if (CORBA::is_nil(orb)) {
            #ifdef GSDEBUGMSG
            cerr << ">> GEARSystem: CommandBus::connectToActuator(const QString&): Could not initialize ORB!!";
            cerr << endl << flush;
            #endif

            return(NULL);
        }

        // Gets the CORBA Controller reference
        CORBA::Object_var corbaObject = orb->string_to_object(address.toStdString().c_str());
        if (CORBA::is_nil(corbaObject)) {
            #ifdef GSDEBUGMSG
            cerr << ">> GEARSystem: CommandBus::connectToActuator(const QString&): Could not connect ";
            cerr << "to the actuator at " << address.toStdString() << "!!" << endl << flush;
            #endif

            return(NULL);
        }

        // Narrows it to the an object
        corbaActuator = CORBAInterfaces::Actuator::_narrow(corbaObject);
        if (CORBA::is_nil(corbaActuator)) {
            #ifdef GSDEBUGMSG
            cerr << ">> GEARSystem: CommandBus::connectToActuator(const QString&): Could not connect ";
            cerr << "to the actuator at " << address.toStdString() << "!!" << endl << flush;
            #endif

            return(NULL);
        }
    }

    // Handles CORBA exceptions
    catch (const CORBA::Exception& exception) {
        #ifdef GSDEBUGMSG
        cerr << ">> GEARSystem: CommandBus::connectToActuator(const QString&): Caught CORBA exception: ";
        cerr << exception._name() << "!!" << endl << flush;
        #endif

        return(NULL);
    }

    // Returns the connected actuator
    return(corbaActuator);
}
