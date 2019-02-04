/*** GEARSystem - Controller implementation
  ** GEAR - Grupo de Estudos Avancados em Robotica
  ** Department of Electrical Engineering, University of Sao Paulo
  ** http://www.sel.eesc.usp.br/gear
  ** This file is part of the GEARSystem project
  ***/


// Includes the class header
#include <GEARSystem/controller.hh>


// Includes IO streams
#include <iostream>

// Includes Qt library
#include <QtCore/QtCore>

// Includes omniORB 4
#include <omniORB4/CORBA.h>


// Selects namespace
using namespace GEARSystem;
using std::cerr;
using std::endl;
using std::flush;
using CORBA::String_var;


/*** Constructor
  ** Description: Creates the controller
  ** Receives:    Nothing
  ***/
Controller::Controller() {
    // Initializes the variables
    _corbaController = NULL;
    _isConnected     = false;
    _serverPort      = 0;
    _serverAddress.clear();
}


/*** 'connect' function
  ** Description: Connects to the server
  ** Receives:    [address] The server address
                  [port]    The server port
  ** Returns:     'true' if the connection was established, 'false' otherwise
  ***/
bool Controller::connect(const QString& address, uint16 port) {
    try {
        // Creates the ORB
        int argc = 0;
        CORBA::ORB_var orb = CORBA::ORB_init(argc, NULL);
        if (CORBA::is_nil(orb)) {
            #ifdef GSDEBUGMSG
            cerr << ">> GEARSystem: Controller::connect(const QString&, uint16): Could not initialize ORB!!" << endl << flush;
            #endif

            return(false);
        }

        // Sets the CORBA Controller address
        QString controllerAddr("corbaname::");
        controllerAddr.append(address);
        if (port != 0) {
            controllerAddr.append(":");
            controllerAddr.append(QString("%1").arg(port));
        }
        controllerAddr.append("#GEARSystem.Controller");

        // Gets the CORBA Controller reference
        CORBA::Object_var corbaObject = orb->string_to_object(controllerAddr.toStdString().c_str());
        if (CORBA::is_nil(corbaObject)) {
            #ifdef GSDEBUGMSG
            cerr << ">> GEARSystem: Controller::connect(const QString&, uint16): Could not connect ";
            cerr << "to the server at " << address.toStdString() << ":" << port << "!!" << endl << flush;
            #endif

            return(false);
        }

        // Narrows it to the encapsulated object
        _corbaController = CORBAInterfaces::Controller::_narrow(corbaObject);
        if (CORBA::is_nil(_corbaController)) {
            #ifdef GSDEBUGMSG
            cerr << ">> GEARSystem: Controller::connect(const QString&, uint16): Could not connect ";
            cerr << "to the server at " << address.toStdString() << ":" << port << "!!" << endl << flush;
            #endif

            return(false);
        }

        // Sets as connected
        _serverAddress = address;
        _serverPort    = port;
        _isConnected   = true;
    }

    // Handles CORBA exceptions
    catch (const CORBA::Exception& exception) {
        #ifdef GSDEBUGMSG
        cerr << ">> GEARSystem: Controller::connect(const QString&, uint16): Caught CORBA exception: ";
        cerr << exception._name() << "!!" << endl << flush;
        #endif

        return(false);
    }

    // Returns 'true' if everything went OK
    return(true);
}

/*** 'disconnect' function
  ** Description: Disconnects from the server
  ** Receives:    Nothing
  ** Returns:     Nothing
  ***/
void Controller::disconnect() {
    // Sets as disconnected
    _serverAddress.clear();
    _serverPort  = 0;
    _isConnected = false;
}

/*** 'isConnected' function
  ** Description: Verifies if the controller is connected to the server
  ** Receives:    Nothing
  ** Returns:     'true' if the connection was established, 'false' otherwise
  ***/
bool Controller::isConnected() const { return(_isConnected); }


/*** 'teamName' function
  ** Description: Gets the team name
  ** Receives:    [teamNum] The team number
  ** Returns:     The team name
  ***/
const QString Controller::teamName(uint8 teamNum) const {
    // Gets the team name
    if (isConnected()) {
        try {
            String_var name;
            _corbaController->teamName(teamNum, name);
            return(QString(name));
        }

        // Handles CORBA exceptions
        catch (const CORBA::Exception& exception) {
            #ifdef GSDEBUGMSG
            cerr << ">> GEARSystem: Controller::teamName(uint8): ";
            cerr << "Caught CORBA exception: " << exception._name() << "!!" << endl << flush;
            #endif
        }
    }
    else {
        #ifdef GSDEBUGMSG
        cerr << ">> GEARSystem: Controller::teamName(uint8): ";
        cerr << "The controller is not connected!!" << endl << flush;
        #endif
    }

    // Returns an invalid name
    return(_invalidName);
}

/*** 'teamNumber' function
  ** Description: Gets the team number
  ** Receives:    [name] The team name
  ** Returns:     The team number
  ***/
uint8 Controller::teamNumber(const QString& name) const {
    // Gets the team number
    if (isConnected()) {
        try {
            uint8 number;
            _corbaController->teamNumber(name.toStdString().c_str(), number);
            return(number);
        }

        // Handles CORBA exceptions
        catch (const CORBA::Exception& exception) {
            #ifdef GSDEBUGMSG
            cerr << ">> GEARSystem: Controller::teamNumber(const QString&): ";
            cerr << "Caught CORBA exception: " << exception._name() << "!!" << endl << flush;
            #endif
        }
    }
    else {
        #ifdef GSDEBUGMSG
        cerr << ">> GEARSystem: Controller::teamNumber(const QString&): ";
        cerr << "The controller is not connected!!" << endl << flush;
        #endif
    }

    // Returns an invalid number
    return(_invalidNumber);
}

/*** 'teams' function
  ** Description: Gets the created teams
  ** Receives:    Nothing
  ** Returns:     The teams list
  ***/
QList<uint8> Controller::teams() const {
    // Gets the teams
    if (isConnected()) {
        try {
            // Gets the stringfied teams list
            String_var teamsCorba;
            uint8      nTeams;
            bool       hasTeam0;
            _corbaController->teams(teamsCorba, nTeams, hasTeam0);
            char* teamsStr = (char*) teamsCorba;

            // Recreates the list
            QList<uint8> list;
            if (hasTeam0) {
                list.append(0);
                nTeams--;
            }

            uint16 i;
            for (i = 0; i < nTeams; i++) {
                list.append(teamsStr[i]);
            }

            // Returns the list
            return(list);
        }

        // Handles CORBA exceptions
        catch (const CORBA::Exception& exception) {
            #ifdef GSDEBUGMSG
            cerr << ">> GEARSystem: Controller::teams(): ";
            cerr << "Caught CORBA exception: " << exception._name() << "!!" << endl << flush;
            #endif
        }
    }
    else {
        #ifdef GSDEBUGMSG
        cerr << ">> GEARSystem: Controller::teams(): ";
        cerr << "The controller is not connected!!" << endl << flush;
        #endif
    }

    // Returns an empty list
    return(QList<uint8>());
}


/*** 'players' function
  ** Description: Gets the created players in a team
  ** Receives:    [teamNum] The team number
  ** Returns:     The players list
  ***/
QList<uint8> Controller::players(uint8 teamNum) const {
    // Gets the players
    if (isConnected()) {
        try {
            // Gets the stringfied players list
            String_var playersCorba;
            uint8      nPlayers;
            bool       hasPlayer0;
            _corbaController->players(teamNum, playersCorba, nPlayers, hasPlayer0);
            char* playersStr = (char*) playersCorba;

            // Recreates the list
            QList<uint8> list;
            if (hasPlayer0) {
                list.append(0);
                nPlayers--;
            }

            uint16 i;
            for (i = 0; i < nPlayers; i++) {
                list.append(playersStr[i]);
            }

            // Returns the list
            return(list);
        }

        // Handles CORBA exceptions
        catch (const CORBA::Exception& exception) {
            #ifdef GSDEBUGMSG
            cerr << ">> GEARSystem: Controller::players(): ";
            cerr << "Caught CORBA exception: " << exception._name() << "!!" << endl << flush;
            #endif
        }
    }
    else {
        #ifdef GSDEBUGMSG
        cerr << ">> GEARSystem: Controller::players(): ";
        cerr << "The controller is not connected!!" << endl << flush;
        #endif
    }

    // Returns an empty list
    return(QList<uint8>());
}


/*** 'balls' function
  ** Description: Gets the created balls
  ** Receives:    Nothing
  ** Returns:     The balls list
  ***/
QList<uint8> Controller::balls() const {
    // Gets the balls
    if (isConnected()) {
        try {
            // Gets the stringfied balls list
            String_var ballsCorba;
            uint8      nBalls;
            bool       hasBall0;
            _corbaController->balls(ballsCorba, nBalls, hasBall0);
            char* ballsStr = (char*) ballsCorba;

            // Recreates the list
            QList<uint8> list;
            if (hasBall0) {
                list.append(0);
                nBalls--;
            }

            uint16 i;
            for (i = 0; i < nBalls; i++) {
                list.append(ballsStr[i]);
            }

            // Returns the list
            return(list);
        }

        // Handles CORBA exceptions
        catch (const CORBA::Exception& exception) {
            #ifdef GSDEBUGMSG
            cerr << ">> GEARSystem: Controller::balls(): ";
            cerr << "Caught CORBA exception: " << exception._name() << "!!" << endl << flush;
            #endif
        }
    }
    else {
        #ifdef GSDEBUGMSG
        cerr << ">> GEARSystem: Controller::balls(): ";
        cerr << "The controller is not connected!!" << endl << flush;
        #endif
    }

    // Returns an empty list
    return(QList<uint8>());
}


/*** 'ballPosition' function
  ** Description: Gets the ball position
  ** Receives:    [ballNum] The ball number
  ** Returns:     The ball position
  ***/
const Position Controller::ballPosition(uint8 ballNum) const {
    // Gets the ball position
    if (isConnected()) {
        try {
            CORBATypes::Position position;
            _corbaController->ballPosition(ballNum, position);

            // Returns the position
            return(Position(position));
        }

        // Handles CORBA exceptions
        catch (const CORBA::Exception& exception) {
            #ifdef GSDEBUGMSG
            cerr << ">> GEARSystem: Controller::ballPosition(uint8): ";
            cerr << "Caught CORBA exception: " << exception._name() << "!!" << endl << flush;
            #endif
        }
    }
    else {
        #ifdef GSDEBUGMSG
        cerr << ">> GEARSystem: Controller::ballPosition(uint8): ";
        cerr << "The controller is not connected!!" << endl << flush;
        #endif
    }

    // Returns an invalid position
    return(_invalidPosition);
}

/*** 'ballVelocity' function
  ** Description: Gets the ball velocity
  ** Receives:    [ballNum] The ball number
  ** Returns:     The ball velocity
  ***/
const Velocity Controller::ballVelocity(uint8 ballNum) const {
    // Gets the ball velocity
    if (isConnected()) {
        try {
            CORBATypes::Velocity velocity;
            _corbaController->ballVelocity(ballNum, velocity);

            // Returns the velocity
            return(Velocity(velocity));
        }

        // Handles CORBA exceptions
        catch (const CORBA::Exception& exception) {
            #ifdef GSDEBUGMSG
            cerr << ">> GEARSystem: Controller::ballVelocity(uint8): ";
            cerr << "Caught CORBA exception: " << exception._name() << "!!" << endl << flush;
            #endif
        }
    }
    else {
        #ifdef GSDEBUGMSG
        cerr << ">> GEARSystem: Controller::ballVelocity(uint8): ";
        cerr << "The controller is not connected!!" << endl << flush;
        #endif
    }

    // Returns an invalid velocity
    return(_invalidVelocity);
}


/*** Gets functions
  ** Description: Gets the player pose
  ** Receives:    [teamNum]   The team number
                  [playerNum] The player number
  ** Returns:     The player position, orientation, velocity or angular speed
  ***/
const Position Controller::playerPosition(uint8 teamNum, uint8 playerNum) const {
    // Gets the player position
    if (isConnected()) {
        try {
            CORBATypes::Position position;
            _corbaController->playerPosition(teamNum, playerNum, position);

            // Returns the position
            return(Position(position));
        }

        // Handles CORBA exceptions
        catch (const CORBA::Exception& exception) {
            #ifdef GSDEBUGMSG
            cerr << ">> GEARSystem: Controller::playerPosition(uint8, uint8): ";
            cerr << "Caught CORBA exception: " << exception._name() << "!!" << endl << flush;
            #endif
        }
    }
    else {
        #ifdef GSDEBUGMSG
        cerr << ">> GEARSystem: Controller::playerPosition(uint8, uint8): ";
        cerr << "The controller is not connected!!" << endl << flush;
        #endif
    }

    // Returns an invalid position
    return(_invalidPosition);
}

const Angle Controller::playerOrientation(uint8 teamNum, uint8 playerNum) const {
    // Gets the player orientation
    if (isConnected()) {
        try {
            CORBATypes::Angle orientation;
            _corbaController->playerOrientation(teamNum, playerNum, orientation);

            // Returns the orientation
            return(Angle(orientation));
        }

        // Handles CORBA exceptions
        catch (const CORBA::Exception& exception) {
            #ifdef GSDEBUGMSG
            cerr << ">> GEARSystem: Controller::playerOrientation(uint8, uint8): ";
            cerr << "Caught CORBA exception: " << exception._name() << "!!" << endl << flush;
            #endif
        }
    }
    else {
        #ifdef GSDEBUGMSG
        cerr << ">> GEARSystem: Controller::playerOrientation(uint8, uint8): ";
        cerr << "The controller is not connected!!" << endl << flush;
        #endif
    }

    // Returns an invalid orientation
    return(_invalidAngle);
}

const Velocity Controller::playerVelocity(uint8 teamNum, uint8 playerNum) const {
    // Gets the player velocity
    if (isConnected()) {
        try {
            CORBATypes::Velocity velocity;
            _corbaController->playerVelocity(teamNum, playerNum, velocity);

            // Returns the velocity
            return(Velocity(velocity));
        }

        // Handles CORBA exceptions
        catch (const CORBA::Exception& exception) {
            #ifdef GSDEBUGMSG
            cerr << ">> GEARSystem: Controller::playerVelocity(uint8, uint8): ";
            cerr << "Caught CORBA exception: " << exception._name() << "!!" << endl << flush;
            #endif
        }
    }
    else {
        #ifdef GSDEBUGMSG
        cerr << ">> GEARSystem: Controller::playerVelocity(uint8, uint8): ";
        cerr << "The controller is not connected!!" << endl << flush;
        #endif
    }

    // Returns an invalid velocity
    return(_invalidVelocity);
}

const AngularSpeed Controller::playerAngularSpeed(uint8 teamNum, uint8 playerNum) const {
    // Gets the player angular speed
    if (isConnected()) {
        try {
            CORBATypes::AngularSpeed angularSpeed;
            _corbaController->playerAngularSpeed(teamNum, playerNum, angularSpeed);

            // Returns the angular speed
            return(AngularSpeed(angularSpeed));
        }

        // Handles CORBA exceptions
        catch (const CORBA::Exception& exception) {
            #ifdef GSDEBUGMSG
            cerr << ">> GEARSystem: Controller::playerAngularSpeed(uint8, uint8): ";
            cerr << "Caught CORBA exception: " << exception._name() << "!!" << endl << flush;
            #endif
        }
    }
    else {
        #ifdef GSDEBUGMSG
        cerr << ">> GEARSystem: Controller::playerAngularSpeed(uint8, uint8): ";
        cerr << "The controller is not connected!!" << endl << flush;
        #endif
    }

    // Returns an invalid angular speed
    return(_invalidAngularSpeed);
}


/*** 'ballPossession' function
  ** Description: Indicates if the player possesses a ball
  ** Receives:    [teamNum]   The team number
                  [playerNum] The player number
  ** Returns:     'true' if the player has the ball, 'false' otherwise
  ***/
bool Controller::ballPossession(uint8 teamNum, uint8 playerNum) {
    // Gets the flag
    if (isConnected()) {
        try {
            bool possession;
            _corbaController->ballPossession(teamNum, playerNum, possession);

            // Returns the flag
            return(possession);
        }

        // Handles CORBA exceptions
        catch (const CORBA::Exception& exception) {
            #ifdef GSDEBUGMSG
            cerr << ">> GEARSystem: Controller::ballPossession(uint8, uint8): ";
            cerr << "Caught CORBA exception: " << exception._name() << "!!" << endl << flush;
            #endif
        }
    }
    else {
        #ifdef GSDEBUGMSG
        cerr << ">> GEARSystem: Controller::ballPossession(uint8, uint8): ";
        cerr << "The controller is not connected!!" << endl << flush;
        #endif
    }

    // Returns 'false' if an error occourred
    return(false);
}


/*** 'fatigue' function
  ** Description: Indicates the player's fatigue
  ** Receives:    [teamNum]    The team number
                  [playerNum]  The player number
  ** Returns:     float value indicating the player fatigue
  ***/
float Controller::fatigue(uint8 teamNum, uint8 playerNum) {
    // Gets the flag
    if (isConnected()) {
        try {
            float fatigue;
            _corbaController->fatigue(teamNum, playerNum, fatigue);

            // Returns the flag
            return(fatigue);
        }

        // Handles CORBA exceptions
        catch (const CORBA::Exception& exception) {
            #ifdef GSDEBUGMSG
            cerr << ">> GEARSystem: Controller::fatigue(uint8, uint8): ";
            cerr << "Caught CORBA exception: " << exception._name() << "!!" << endl << flush;
            #endif
        }
    }
    else {
        #ifdef GSDEBUGMSG
        cerr << ">> GEARSystem: Controller::fatigue(uint8, uint8): ";
        cerr << "The controller is not connected!!" << endl << flush;
        #endif
    }

    // Returns 'false' if an error occourred
    return(false);
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
void Controller::setSpeed(uint8 teamNum, uint8 playerNum, float x, float y, float theta) {
    // Sends the 'setSpeed' command
    if (isConnected()) {
        try {
            _corbaController->setSpeed(teamNum, playerNum, x, y, theta);
        }

        // Handles CORBA exceptions
        catch (const CORBA::Exception& exception) {
            #ifdef GSDEBUGMSG
            cerr << ">> GEARSystem: Controller::setSpeed(uint8, uint8, float, float, float): ";
            cerr << "Caught CORBA exception: " << exception._name() << "!!" << endl << flush;
            #endif
        }
    }
    else {
        #ifdef GSDEBUGMSG
        cerr << ">> GEARSystem: Controller::setSpeed(uint8, uint8, float, float, float): ";
        cerr << "The controller is not connected!!" << endl << flush;
        #endif
    }
}

/*** 'kick'
  ** Description: Activates the player kicking device
  ** Receives:    [teamNum]   The team number
                  [playerNum] The team number
                  [power]     The kick power
  ** Returns:     Nothing
  ***/
void Controller::kick(uint8 teamNum, uint8 playerNum, float power) {
    // Sends the 'kick' command
    if (isConnected()) {
        try {
            _corbaController->kick(teamNum, playerNum, power);
        }

        // Handles CORBA exceptions
        catch (const CORBA::Exception& exception) {
            #ifdef GSDEBUGMSG
            cerr << ">> GEARSystem: Controller::kick(uint8, uint8, float): ";
            cerr << "Caught CORBA exception: " << exception._name() << "!!" << endl << flush;
            #endif
        }
    }
    else {
        #ifdef GSDEBUGMSG
        cerr << ">> GEARSystem: Controller::kick(uint8, uint8, float): ";
        cerr << "The controller is not connected!!" << endl << flush;
        #endif
    }
}

/*** 'chipKick'
  ** Description: Activates the player chip-kicking device
  ** Receives:    [teamNum]   The team number
                  [playerNum] The team number
                  [power]     The kick power
  ** Returns:     Nothing
  ***/
void Controller::chipKick(uint8 teamNum, uint8 playerNum, float power) {
    // Sends the 'chipKick' command
    if (isConnected()) {
        try {
            _corbaController->chipKick(teamNum, playerNum, power);
        }

        // Handles CORBA exceptions
        catch (const CORBA::Exception& exception) {
            #ifdef GSDEBUGMSG
            cerr << ">> GEARSystem: Controller::chipKick(uint8, uint8, float): ";
            cerr << "Caught CORBA exception: " << exception._name() << "!!" << endl << flush;
            #endif
        }
    }
    else {
        #ifdef GSDEBUGMSG
        cerr << ">> GEARSystem: Controller::chipKick(uint8, uint8, float): ";
        cerr << "The controller is not connected!!" << endl << flush;
        #endif
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
void Controller::kickOnTouch(uint8 teamNum, uint8 playerNum, bool enable, float power) {
    // Sends the 'kickOnTouch' command
    if (isConnected()) {
        try {
            _corbaController->kickOnTouch(teamNum, playerNum, enable, power);
        }

        // Handles CORBA exceptions
        catch (const CORBA::Exception& exception) {
            #ifdef GSDEBUGMSG
            cerr << ">> GEARSystem: Controller::kickOnTouch(uint8, uint8, bool, float): ";
            cerr << "Caught CORBA exception: " << exception._name() << "!!" << endl << flush;
            #endif
        }
    }
    else {
        #ifdef GSDEBUGMSG
        cerr << ">> GEARSystem: Controller::kickOnTouch(uint8, uint8, bool, float): ";
        cerr << "The controller is not connected!!" << endl << flush;
        #endif
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
void Controller::chipKickOnTouch(uint8 teamNum, uint8 playerNum, bool enable, float power) {
    // Sends the 'chipKickOnTouch' command
    if (isConnected()) {
        try {
            _corbaController->chipKickOnTouch(teamNum, playerNum, enable, power);
        }

        // Handles CORBA exceptions
        catch (const CORBA::Exception& exception) {
            #ifdef GSDEBUGMSG
            cerr << ">> GEARSystem: Controller::chipKickOnTouch(uint8, uint8, bool, float): ";
            cerr << "Caught CORBA exception: " << exception._name() << "!!" << endl << flush;
            #endif
        }
    }
    else {
        #ifdef GSDEBUGMSG
        cerr << ">> GEARSystem: Controller::chipKickOnTouch(uint8, uint8, bool, float): ";
        cerr << "The controller is not connected!!" << endl << flush;
        #endif
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
void Controller::holdBall(uint8 teamNum, uint8 playerNum, bool enable) {
    // Sends the 'holdBall' command
    if (isConnected()) {
        try {
            _corbaController->holdBall(teamNum, playerNum, enable);
        }

        // Handles CORBA exceptions
        catch (const CORBA::Exception& exception) {
            #ifdef GSDEBUGMSG
            cerr << ">> GEARSystem: Controller::holdBall(uint8, uint8, bool): ";
            cerr << "Caught CORBA exception: " << exception._name() << "!!" << endl << flush;
            #endif
        }
    }
    else {
        #ifdef GSDEBUGMSG
        cerr << ">> GEARSystem: Controller::holdBall(uint8, uint8, bool): ";
        cerr << "The controller is not connected!!" << endl << flush;
        #endif
    }
}


/*** Field handling functions
  ** Description: Handles field info
  ***/
const Position Controller::fieldTopRightCorner() const {
    // Gets the field corner
    if (isConnected()) {
        try {
            CORBATypes::Position position;
            _corbaController->fieldTopRightCorner(position);

            // Returns the position
            return(Position(position));
        }

        // Handles CORBA exceptions
        catch (const CORBA::Exception& exception) {
            #ifdef GSDEBUGMSG
            cerr << ">> GEARSystem: Controller::fieldTopRightCorner(): ";
            cerr << "Caught CORBA exception: " << exception._name() << "!!" << endl << flush;
            #endif
        }
    }
    else {
        #ifdef GSDEBUGMSG
        cerr << ">> GEARSystem: Controller::fieldTopRightCorner(): ";
        cerr << "The controller is not connected!!" << endl << flush;
        #endif
    }

    // Returns an invalid position
    return(_invalidPosition);
}

const Position Controller::fieldTopLeftCorner() const {
    // Gets the field corner
    if (isConnected()) {
        try {
            CORBATypes::Position position;
            _corbaController->fieldTopLeftCorner(position);

            // Returns the position
            return(Position(position));
        }

        // Handles CORBA exceptions
        catch (const CORBA::Exception& exception) {
            #ifdef GSDEBUGMSG
            cerr << ">> GEARSystem: Controller::fieldTopLeftCorner(): ";
            cerr << "Caught CORBA exception: " << exception._name() << "!!" << endl << flush;
            #endif
        }
    }
    else {
        #ifdef GSDEBUGMSG
        cerr << ">> GEARSystem: Controller::fieldTopLeftCorner(): ";
        cerr << "The controller is not connected!!" << endl << flush;
        #endif
    }

    // Returns an invalid position
    return(_invalidPosition);
}

const Position Controller::fieldBottomLeftCorner() const {
    // Gets the field corner
    if (isConnected()) {
        try {
            CORBATypes::Position position;
            _corbaController->fieldBottomLeftCorner(position);

            // Returns the position
            return(Position(position));
        }

        // Handles CORBA exceptions
        catch (const CORBA::Exception& exception) {
            #ifdef GSDEBUGMSG
            cerr << ">> GEARSystem: Controller::fieldBottomLeftCorner(): ";
            cerr << "Caught CORBA exception: " << exception._name() << "!!" << endl << flush;
            #endif
        }
    }
    else {
        #ifdef GSDEBUGMSG
        cerr << ">> GEARSystem: Controller::fieldBottomLeftCorner(): ";
        cerr << "The controller is not connected!!" << endl << flush;
        #endif
    }

    // Returns an invalid position
    return(_invalidPosition);
}

const Position Controller::fieldBottomRightCorner() const {
    // Gets the field corner
    if (isConnected()) {
        try {
            CORBATypes::Position position;
            _corbaController->fieldBottomRightCorner(position);

            // Returns the position
            return(Position(position));
        }

        // Handles CORBA exceptions
        catch (const CORBA::Exception& exception) {
            #ifdef GSDEBUGMSG
            cerr << ">> GEARSystem: Controller::fieldBottomRightCorner(): ";
            cerr << "Caught CORBA exception: " << exception._name() << "!!" << endl << flush;
            #endif
        }
    }
    else {
        #ifdef GSDEBUGMSG
        cerr << ">> GEARSystem: Controller::fieldBottomRightCorner(): ";
        cerr << "The controller is not connected!!" << endl << flush;
        #endif
    }

    // Returns an invalid position
    return(_invalidPosition);
}

const Position Controller::fieldCenter() const {
    // Gets the field corner
    if (isConnected()) {
        try {
            CORBATypes::Position position;
            _corbaController->fieldCenter(position);

            // Returns the position
            return(Position(position));
        }

        // Handles CORBA exceptions
        catch (const CORBA::Exception& exception) {
            #ifdef GSDEBUGMSG
            cerr << ">> GEARSystem: Controller::fieldCenter(): ";
            cerr << "Caught CORBA exception: " << exception._name() << "!!" << endl << flush;
            #endif
        }
    }
    else {
        #ifdef GSDEBUGMSG
        cerr << ">> GEARSystem: Controller::fieldCenter(): ";
        cerr << "The controller is not connected!!" << endl << flush;
        #endif
    }

    // Returns an invalid position
    return(_invalidPosition);
}

const Goal Controller::leftGoal() const {
    // Gets the goal
    if (isConnected()) {
        try {
            CORBATypes::Position left;
            CORBATypes::Position right;
            float depth;
            float areaLength;
            float areaWidth;
            float areaRoundedRadius;
            _corbaController->leftGoal(left, right, depth, areaLength, areaWidth, areaRoundedRadius);


            // Returns the positions
            return(Goal(left, right, depth, areaLength, areaWidth, areaRoundedRadius));
        }

        // Handles CORBA exceptions
        catch (const CORBA::Exception& exception) {
            #ifdef GSDEBUGMSG
            cerr << ">> GEARSystem: Controller::leftGoal(): ";
            cerr << "Caught CORBA exception: " << exception._name() << "!!" << endl << flush;
            #endif
        }
    }
    else {
        #ifdef GSDEBUGMSG
        cerr << ">> GEARSystem: Controller::leftGoal(): ";
        cerr << "The controller is not connected!!" << endl << flush;
        #endif
    }

    // Returns an invalid goal
    return(_invalidGoal);
}

const Goal Controller::rightGoal() const {
    // Gets the goal
    if (isConnected()) {
        try {
            CORBATypes::Position left;
            CORBATypes::Position right;
            float depth;
            float areaLength;
            float areaWidth;
            float areaRoundedRadius;
            _corbaController->rightGoal(left, right, depth, areaLength, areaWidth, areaRoundedRadius);

            // Returns the positions
            return(Goal(left, right, depth, areaLength, areaWidth, areaRoundedRadius));
        }

        // Handles CORBA exceptions
        catch (const CORBA::Exception& exception) {
            #ifdef GSDEBUGMSG
            cerr << ">> GEARSystem: Controller::rightGoal(): ";
            cerr << "Caught CORBA exception: " << exception._name() << "!!" << endl << flush;
            #endif
        }
    }
    else {
        #ifdef GSDEBUGMSG
        cerr << ">> GEARSystem: Controller::rightGoal(): ";
        cerr << "The controller is not connected!!" << endl << flush;
        #endif
    }

    // Returns an invalid goal
    return(_invalidGoal);
}

const Position Controller::leftPenaltyMark() const {
    // Gets the mark
    if (isConnected()) {
        try {
            CORBATypes::Position position;
            _corbaController->leftPenaltyMark(position);

            // Returns the position
            return(Position(position));
        }

        // Handles CORBA exceptions
        catch (const CORBA::Exception& exception) {
            #ifdef GSDEBUGMSG
            cerr << ">> GEARSystem: Controller::leftPenaltyMark(): ";
            cerr << "Caught CORBA exception: " << exception._name() << "!!" << endl << flush;
            #endif
        }
    }
    else {
        #ifdef GSDEBUGMSG
        cerr << ">> GEARSystem: Controller::leftPenaltyMark(): ";
        cerr << "The controller is not connected!!" << endl << flush;
        #endif
    }

    // Returns an invalid position
    return(_invalidPosition);
}

const Position Controller::rightPenaltyMark() const {
    // Gets the mark
    if (isConnected()) {
        try {
            CORBATypes::Position position;
            _corbaController->rightPenaltyMark(position);

            // Returns the position
            return(Position(position));
        }

        // Handles CORBA exceptions
        catch (const CORBA::Exception& exception) {
            #ifdef GSDEBUGMSG
            cerr << ">> GEARSystem: Controller::rightPenaltyMark(): ";
            cerr << "Caught CORBA exception: " << exception._name() << "!!" << endl << flush;
            #endif
        }
    }
    else {
        #ifdef GSDEBUGMSG
        cerr << ">> GEARSystem: Controller::rightPenaltyMark(): ";
        cerr << "The controller is not connected!!" << endl << flush;
        #endif
    }

    // Returns an invalid position
    return(_invalidPosition);
}

float Controller::fieldCenterRadius() const {
    // Gets the field center radius
    if (isConnected()) {
        try {
            float centerRadius;
            _corbaController->fieldCenterRadius(centerRadius);

            // Returns the position
            return(centerRadius);
        }

        // Handles CORBA exceptions
        catch (const CORBA::Exception& exception) {
            #ifdef GSDEBUGMSG
            cerr << ">> GEARSystem: Controller::fieldCenterRadius(): ";
            cerr << "Caught CORBA exception: " << exception._name() << "!!" << endl << flush;
            #endif
        }
    }
    else {
        #ifdef GSDEBUGMSG
        cerr << ">> GEARSystem: Controller::fieldCenterRadius(): ";
        cerr << "The controller is not connected!!" << endl << flush;
        #endif
    }

    // Returns an invalid position
    return(0.0f);
}
