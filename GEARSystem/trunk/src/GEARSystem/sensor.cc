/*** GEARSystem - Sensor implementation
  ** GEAR - Grupo de Estudos Avancados em Robotica
  ** Department of Electrical Engineering, University of Sao Paulo
  ** http://www.sel.eesc.usp.br/gear
  ** This file is part of the GEARSystem project
  ***/


// Includes the class header
#include <GEARSystem/sensor.hh>


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


/*** Constructor
  ** Description: Creates the sensor
  ** Receives:    Nothing
  ***/
Sensor::Sensor() {
    // Initializes the variables
    _corbaSensor = NULL;
    _isConnected = false;
    _serverPort  = 0;
    _serverAddress.clear();
}


/*** 'connect' function
  ** Description: Connects to the server
  ** Receives:    [address] The server address
                  [port]    The server port
  ** Returns:     'true' if the connection was established, 'false' otherwise
  ***/
bool Sensor::connect(const QString& address, uint16 port) {
    try {
        // Creates the ORB
        int argc = 0;
        CORBA::ORB_var orb = CORBA::ORB_init(argc, NULL);
        if (CORBA::is_nil(orb)) {
            #ifdef GSDEBUGMSG
            cerr << ">> GEARSystem: Sensor::connect(const QString&, uint16): Could not initialize ORB!!" << endl << flush;
            #endif

            return(false);
        }

        // Sets the CORBA Sensor address
        QString sensorAddr("corbaname::");
        sensorAddr.append(address);
        if (port != 0) {
            sensorAddr.append(":");
            sensorAddr.append(QString("%1").arg(port));
        }
        sensorAddr.append("#GEARSystem.Sensor");

        // Gets the CORBA Sensor reference
        CORBA::Object_var corbaObject = orb->string_to_object(sensorAddr.toStdString().c_str());
        if (CORBA::is_nil(corbaObject)) {
            #ifdef GSDEBUGMSG
            cerr << ">> GEARSystem: Sensor::connect(const QString&, uint16): Could not connect ";
            cerr << "to the server at " << address.toStdString() << ":" << port << "!!" << endl << flush;
            #endif

            return(false);
        }

        // Narrows it to the encapsulated object
        _corbaSensor = CORBAInterfaces::Sensor::_narrow(corbaObject);
        if (CORBA::is_nil(_corbaSensor)) {
            #ifdef GSDEBUGMSG
            cerr << ">> GEARSystem: Sensor::connect(const QString&, uint16): Could not connect ";
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
        cerr << ">> GEARSystem: Sensor::connect(const QString&, uint16): Caught CORBA exception: ";
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
void Sensor::disconnect() {
    // Sets as disconnected
    _serverAddress.clear();
    _serverPort  = 0;
    _isConnected = false;
}

/*** 'isConnected' function
  ** Description: Verifies if the sensor is connected to the server
  ** Receives:    Nothing
  ** Returns:     'true' if the connection was established, 'false' otherwise
  ***/
bool Sensor::isConnected() const { return(_isConnected); }


/*** Teams handling functions
  ** Description: Handles the teams
  ** Receives:    [teamNum]  The team number
                  [teamName] The team name
  ** Returns:     Nothing
  ***/
void Sensor::addTeam(uint8 teamNum, const QString& teamName) {
    // Adds the team
    if (isConnected()) {
        try {
            _corbaSensor->addTeam(teamNum, teamName.toStdString().c_str());
        }

        // Handles CORBA exceptions
        catch (const CORBA::Exception& exception) {
            #ifdef GSDEBUGMSG
            cerr << ">> GEARSystem: Sensor::addTeam(uint8, const QString&): ";
            cerr << "Caught CORBA exception: " << exception._name() << "!!" << endl << flush;
            #endif
        }
    }
    else {
        #ifdef GSDEBUGMSG
        cerr << ">> GEARSystem: Sensor::addTeam(uint8, const QString&): ";
        cerr << "The sensor is not connected!!" << endl << flush;
        #endif
    }
}

void Sensor::delTeam(uint8 teamNum) {
    // Deletes the team
    if (isConnected()) {
        try {
            _corbaSensor->delTeam(teamNum);
        }

        // Handles CORBA exceptions
        catch (const CORBA::Exception& exception) {
            #ifdef GSDEBUGMSG
            cerr << ">> GEARSystem: Sensor::delTeam(uint8): ";
            cerr << "Caught CORBA exception: " << exception._name() << "!!" << endl << flush;
            #endif
        }
    }
    else {
        #ifdef GSDEBUGMSG
        cerr << ">> GEARSystem: Sensor::delTeam(uint8): ";
        cerr << "The sensor is not connected!!" << endl << flush;
        #endif
    }
}


/*** Balls handling functions
  ** Description: Handles the balls
  ** Receives:    [ballNum] The ball number
  ** Returns:     Nothing
  ***/
void Sensor::addBall(uint8 ballNum) {
    // Adds the ball
    if (isConnected()) {
        try {
            _corbaSensor->addBall(ballNum);
        }

        // Handles CORBA exceptions
        catch (const CORBA::Exception& exception) {
            #ifdef GSDEBUGMSG
            cerr << ">> GEARSystem: Sensor::addBall(uint8): ";
            cerr << "Caught CORBA exception: " << exception._name() << "!!" << endl << flush;
            #endif
        }
    }
    else {
        #ifdef GSDEBUGMSG
        cerr << ">> GEARSystem: Sensor::addBall(uint8): ";
        cerr << "The sensor is not connected!!" << endl << flush;
        #endif
    }
}

void Sensor::delBall(uint8 ballNum) {
    // Deletes the ball
    if (isConnected()) {
        try {
            _corbaSensor->delBall(ballNum);
        }

        // Handles CORBA exceptions
        catch (const CORBA::Exception& exception) {
            #ifdef GSDEBUGMSG
            cerr << ">> GEARSystem: Sensor::delBall(uint8): ";
            cerr << "Caught CORBA exception: " << exception._name() << "!!" << endl << flush;
            #endif
        }
    }
    else {
        #ifdef GSDEBUGMSG
        cerr << ">> GEARSystem: Sensor::delBall(uint8): ";
        cerr << "The sensor is not connected!!" << endl << flush;
        #endif
    }
}

/*** 'setBallPosition' function
  ** Description: Sets the ball position
  ** Receives:    [ballNum]  The ball number
                  [position] The ball position
  ** Returns:     Nothing
  ***/
void Sensor::setBallPosition(uint8 ballNum, const Position& position) {
    // Sets the ball position
    if (isConnected()) {
        try {
            CORBATypes::Position corbaPosition;
            position.toCORBA(&corbaPosition);
            _corbaSensor->setBallPosition(ballNum, corbaPosition);
        }

        // Handles CORBA exceptions
        catch (const CORBA::Exception& exception) {
            #ifdef GSDEBUGMSG
            cerr << ">> GEARSystem: Sensor::setBallPosition(uint8, const Position&): ";
            cerr << "Caught CORBA exception: " << exception._name() << "!!" << endl << flush;
            #endif
        }
    }
    else {
        #ifdef GSDEBUGMSG
        cerr << ">> GEARSystem: Sensor::setBallPosition(uint8, const Position&): ";
        cerr << "The sensor is not connected!!" << endl << flush;
        #endif
    }
}

/*** 'setBallVelocity' function
  ** Description: Sets the ball velocity
  ** Receives:    [ballNum]  The ball number
                  [velocity] The ball velocity
  ** Returns:     Nothing
  ***/
void Sensor::setBallVelocity(uint8 ballNum, const Velocity& velocity) {
    // Sets the ball velocity
    if (isConnected()) {
        try {
            CORBATypes::Velocity corbaVelocity;
            velocity.toCORBA(&corbaVelocity);
            _corbaSensor->setBallVelocity(ballNum, corbaVelocity);
        }

        // Handles CORBA exceptions
        catch (const CORBA::Exception& exception) {
            #ifdef GSDEBUGMSG
            cerr << ">> GEARSystem: Sensor::setBallVelocity(uint8, const Velocity&): ";
            cerr << "Caught CORBA exception: " << exception._name() << "!!" << endl << flush;
            #endif
        }
    }
    else {
        #ifdef GSDEBUGMSG
        cerr << ">> GEARSystem: Sensor::setBallVelocity(uint8, const Velocity&): ";
        cerr << "The sensor is not connected!!" << endl << flush;
        #endif
    }
}


/*** Players handling functions
  ** Description: Handles the teams players
  ** Receives:    [teamNum]   The team number
                  [playerNum] The player number
  ** Returns:     Nothing
  ***/
void Sensor::addPlayer(uint8 teamNum, uint8 playerNum) {
    // Adds the player
    if (isConnected()) {
        try {
            _corbaSensor->addPlayer(teamNum, playerNum);
        }

        // Handles CORBA exceptions
        catch (const CORBA::Exception& exception) {
            #ifdef GSDEBUGMSG
            cerr << ">> GEARSystem: Sensor::addPlayer(uint8, uint8): ";
            cerr << "Caught CORBA exception: " << exception._name() << "!!" << endl << flush;
            #endif
        }
    }
    else {
        #ifdef GSDEBUGMSG
        cerr << ">> GEARSystem: Sensor::addPlayer(uint8, uint8): ";
        cerr << "The sensor is not connected!!" << endl << flush;
        #endif
    }
}

void Sensor::delPlayer(uint8 teamNum, uint8 playerNum) {
    // Deletes the player
    if (isConnected()) {
        try {
            _corbaSensor->delPlayer(teamNum, playerNum);
        }

        // Handles CORBA exceptions
        catch (const CORBA::Exception& exception) {
            #ifdef GSDEBUGMSG
            cerr << ">> GEARSystem: Sensor::delPlayer(uint8, uint8): ";
            cerr << "Caught CORBA exception: " << exception._name() << "!!" << endl << flush;
            #endif
        }
    }
    else {
        #ifdef GSDEBUGMSG
        cerr << ">> GEARSystem: Sensor::delPlayer(uint8, uint8): ";
        cerr << "The sensor is not connected!!" << endl << flush;
        #endif
    }
}

/*** 'setPlayerPosition' function
  ** Description: Sets the player position
  ** Receives:    [teamNum]   The team number
                  [playerNum] The player number
                  [position]  The player position
  ** Returns:     Nothing
  ***/
void Sensor::setPlayerPosition(uint8 teamNum, uint8 playerNum, const Position& position) {
    // Sets the player position
    if (isConnected()) {
        try {
            CORBATypes::Position corbaPosition;
            position.toCORBA(&corbaPosition);
            _corbaSensor->setPlayerPosition(teamNum, playerNum, corbaPosition);
        }

        // Handles CORBA exceptions
        catch (const CORBA::Exception& exception) {
            #ifdef GSDEBUGMSG
            cerr << ">> GEARSystem: Sensor::setPlayerPosition(uint8, uint8, const Position&): ";
            cerr << "Caught CORBA exception: " << exception._name() << "!!" << endl << flush;
            #endif
        }
    }
    else {
        #ifdef GSDEBUGMSG
        cerr << ">> GEARSystem: Sensor::setPlayerPosition(uint8, uint8, const Position&): ";
        cerr << "The sensor is not connected!!" << endl << flush;
        #endif
    }
}

/*** 'setPlayerOrientation' function
  ** Description: Sets the player orientation
  ** Receives:    [teamNum]     The team number
                  [playerNum]   The player number
                  [orientation] The player orientation
  ** Returns:     Nothing
  ***/
void Sensor::setPlayerOrientation(uint8 teamNum, uint8 playerNum, const Angle& orientation) {
    // Sets the player orientation
    if (isConnected()) {
        try {
            CORBATypes::Angle corbaOrientation;
            orientation.toCORBA(&corbaOrientation);
            _corbaSensor->setPlayerOrientation(teamNum, playerNum, corbaOrientation);
        }

        // Handles CORBA exceptions
        catch (const CORBA::Exception& exception) {
            #ifdef GSDEBUGMSG
            cerr << ">> GEARSystem: Sensor::setPlayerOrientation(uint8, uint8, const Orientation&): ";
            cerr << "Caught CORBA exception: " << exception._name() << "!!" << endl << flush;
            #endif
        }
    }
    else {
        #ifdef GSDEBUGMSG
        cerr << ">> GEARSystem: Sensor::setPlayerOrientation(uint8, uint8, const Orientation&): ";
        cerr << "The sensor is not connected!!" << endl << flush;
        #endif
    }
}

/*** 'setPlayerVelocity' function
  ** Description: Sets the player velocity
  ** Receives:    [teamNum]   The team number
                  [playerNum] The player number
                  [velocity]  The player velocity
  ** Returns:     Nothing
  ***/
void Sensor::setPlayerVelocity(uint8 teamNum, uint8 playerNum, const Velocity& velocity) {
    // Sets the player velocity
    if (isConnected()) {
        try {
            CORBATypes::Velocity corbaVelocity;
            velocity.toCORBA(&corbaVelocity);
            _corbaSensor->setPlayerVelocity(teamNum, playerNum, corbaVelocity);
        }

        // Handles CORBA exceptions
        catch (const CORBA::Exception& exception) {
            #ifdef GSDEBUGMSG
            cerr << ">> GEARSystem: Sensor::setPlayerVelocity(uint8, uint8, const Velocity&): ";
            cerr << "Caught CORBA exception: " << exception._name() << "!!" << endl << flush;
            #endif
        }
    }
    else {
        #ifdef GSDEBUGMSG
        cerr << ">> GEARSystem: Sensor::setPlayerVelocity(uint8, uint8, const Velocity&): ";
        cerr << "The sensor is not connected!!" << endl << flush;
        #endif
    }
}

/*** 'setPlayerAngularSpeed' function
  ** Description: Sets the player angular speed
  ** Receives:    [teamNum]      The team number
                  [playerNum]    The player number
                  [angularSpeed] The player angular speed
  ** Returns:     Nothing
  ***/
void Sensor::setPlayerAngularSpeed(uint8 teamNum, uint8 playerNum, const AngularSpeed& angularSpeed) {
    // Sets the player angular speed
    if (isConnected()) {
        try {
            CORBATypes::AngularSpeed corbaAnuglarSpeed;
            angularSpeed.toCORBA(&corbaAnuglarSpeed);
            _corbaSensor->setPlayerAngularSpeed(teamNum, playerNum, corbaAnuglarSpeed);
        }

        // Handles CORBA exceptions
        catch (const CORBA::Exception& exception) {
            #ifdef GSDEBUGMSG
            cerr << ">> GEARSystem: Sensor::setPlayerAnuglarSpeed(uint8, uint8, const AnuglarSpeed&): ";
            cerr << "Caught CORBA exception: " << exception._name() << "!!" << endl << flush;
            #endif
        }
    }
    else {
        #ifdef GSDEBUGMSG
        cerr << ">> GEARSystem: Sensor::setPlayerAnuglarSpeed(uint8, uint8, const AnuglarSpeed&): ";
        cerr << "The sensor is not connected!!" << endl << flush;
        #endif
    }
}

/*** 'setBallPossession' function
  ** Description: Indicates if the player possesses a ball
  ** Receives:    [teamNum]    The team number
                  [playerNum]  The player number
                  [possession] 'true' if the player has the ball, 'false' otherwise
  ** Returns:     Nothing
  ***/
void Sensor::setBallPossession(uint8 teamNum, uint8 playerNum, bool possession) {
    // Sets the flag
    if (isConnected()) {
        try {
            _corbaSensor->setBallPossession(teamNum, playerNum, possession);
        }

        // Handles CORBA exceptions
        catch (const CORBA::Exception& exception) {
            #ifdef GSDEBUGMSG
            cerr << ">> GEARSystem: Sensor::setBallPossession(uint8, uint8, const bool): ";
            cerr << "Caught CORBA exception: " << exception._name() << "!!" << endl << flush;
            #endif
        }
    }
    else {
        #ifdef GSDEBUGMSG
        cerr << ">> GEARSystem: Sensor::setBallPossession(uint8, uint8, const bool): ";
        cerr << "The sensor is not connected!!" << endl << flush;
        #endif
    }
}


/*** Field handling functions
  ** Description: Handles field info
  ***/
void Sensor::setFieldTopRightCorner(const Position& position) {
    // Sets the corner position
    if (isConnected()) {
        try {
            CORBATypes::Position corbaPosition;
            position.toCORBA(&corbaPosition);
            _corbaSensor->setFieldTopRightCorner(corbaPosition);
        }

        // Handles CORBA exceptions
        catch (const CORBA::Exception& exception) {
            #ifdef GSDEBUGMSG
            cerr << ">> GEARSystem: Sensor::setTopRightCorner(const Position&): ";
            cerr << "Caught CORBA exception: " << exception._name() << "!!" << endl << flush;
            #endif
        }
    }
    else {
        #ifdef GSDEBUGMSG
        cerr << ">> GEARSystem: Sensor::setTopRightCorner(const Position&): ";
        cerr << "The sensor is not connected!!" << endl << flush;
        #endif
    }
}

void Sensor::setFieldTopLeftCorner(const Position& position) {
    // Sets the corner position
    if (isConnected()) {
        try {
            CORBATypes::Position corbaPosition;
            position.toCORBA(&corbaPosition);
            _corbaSensor->setFieldTopLeftCorner(corbaPosition);
        }

        // Handles CORBA exceptions
        catch (const CORBA::Exception& exception) {
            #ifdef GSDEBUGMSG
            cerr << ">> GEARSystem: Sensor::setTopLeftCorner(const Position&): ";
            cerr << "Caught CORBA exception: " << exception._name() << "!!" << endl << flush;
            #endif
        }
    }
    else {
        #ifdef GSDEBUGMSG
        cerr << ">> GEARSystem: Sensor::setTopLeftCorner(const Position&): ";
        cerr << "The sensor is not connected!!" << endl << flush;
        #endif
    }
}

void Sensor::setFieldBottomLeftCorner(const Position& position) {
    // Sets the corner position
    if (isConnected()) {
        try {
            CORBATypes::Position corbaPosition;
            position.toCORBA(&corbaPosition);
            _corbaSensor->setFieldBottomLeftCorner(corbaPosition);
        }

        // Handles CORBA exceptions
        catch (const CORBA::Exception& exception) {
            #ifdef GSDEBUGMSG
            cerr << ">> GEARSystem: Sensor::setBottomLeftCorner(const Position&): ";
            cerr << "Caught CORBA exception: " << exception._name() << "!!" << endl << flush;
            #endif
        }
    }
    else {
        #ifdef GSDEBUGMSG
        cerr << ">> GEARSystem: Sensor::setBottomLeftCorner(const Position&): ";
        cerr << "The sensor is not connected!!" << endl << flush;
        #endif
    }
}

void Sensor::setFieldBottomRightCorner(const Position& position) {
    // Sets the corner position
    if (isConnected()) {
        try {
            CORBATypes::Position corbaPosition;
            position.toCORBA(&corbaPosition);
            _corbaSensor->setFieldBottomRightCorner(corbaPosition);
        }

        // Handles CORBA exceptions
        catch (const CORBA::Exception& exception) {
            #ifdef GSDEBUGMSG
            cerr << ">> GEARSystem: Sensor::setBottomRightCorner(const Position&): ";
            cerr << "Caught CORBA exception: " << exception._name() << "!!" << endl << flush;
            #endif
        }
    }
    else {
        #ifdef GSDEBUGMSG
        cerr << ">> GEARSystem: Sensor::setBottomRightCorner(const Position&): ";
        cerr << "The sensor is not connected!!" << endl << flush;
        #endif
    }
}

void Sensor::setFieldCenter(const Position& position) {
    // Sets the center position
    if (isConnected()) {
        try {
            CORBATypes::Position corbaPosition;
            position.toCORBA(&corbaPosition);
            _corbaSensor->setFieldCenter(corbaPosition);
        }

        // Handles CORBA exceptions
        catch (const CORBA::Exception& exception) {
            #ifdef GSDEBUGMSG
            cerr << ">> GEARSystem: Sensor::setFieldCenter(const Position&): ";
            cerr << "Caught CORBA exception: " << exception._name() << "!!" << endl << flush;
            #endif
        }
    }
    else {
        #ifdef GSDEBUGMSG
        cerr << ">> GEARSystem: Sensor::setFieldCenter(const Position&): ";
        cerr << "The sensor is not connected!!" << endl << flush;
        #endif
    }
}

void Sensor::setLeftGoalPosts(const Position& leftPost, const Position& rightPost) {
    // Sets the goal position
    if (isConnected()) {
        try {
            CORBATypes::Position corbaLeft, corbaRight;
            leftPost.toCORBA(&corbaLeft);
            rightPost.toCORBA(&corbaRight);
            _corbaSensor->setLeftGoalPosts(corbaLeft, corbaRight);
        }

        // Handles CORBA exceptions
        catch (const CORBA::Exception& exception) {
            #ifdef GSDEBUGMSG
            cerr << ">> GEARSystem: Sensor::setLeftGoalPosts(const Position&, const Position&): ";
            cerr << "Caught CORBA exception: " << exception._name() << "!!" << endl << flush;
            #endif
        }
    }
    else {
        #ifdef GSDEBUGMSG
        cerr << ">> GEARSystem: Sensor::setLeftGoalPosts(const Position&, const Position&): ";
        cerr << "The sensor is not connected!!" << endl << flush;
        #endif
    }
}

void Sensor::setRightGoalPosts(const Position& leftPost, const Position& rightPost) {
    // Sets the goal position
    if (isConnected()) {
        try {
            CORBATypes::Position corbaLeft, corbaRight;
            leftPost.toCORBA(&corbaLeft);
            rightPost.toCORBA(&corbaRight);
            _corbaSensor->setRightGoalPosts(corbaLeft, corbaRight);
        }

        // Handles CORBA exceptions
        catch (const CORBA::Exception& exception) {
            #ifdef GSDEBUGMSG
            cerr << ">> GEARSystem: Sensor::setRightGoalPosts(const Position&, const Position&): ";
            cerr << "Caught CORBA exception: " << exception._name() << "!!" << endl << flush;
            #endif
        }
    }
    else {
        #ifdef GSDEBUGMSG
        cerr << ">> GEARSystem: Sensor::setRightGoalPosts(const Position&, const Position&): ";
        cerr << "The sensor is not connected!!" << endl << flush;
        #endif
    }
}

void Sensor::setGoalArea(float length, float width, float roundedRadius) {
    // Sets the goal area
    if (isConnected()) {
        try {
            _corbaSensor->setGoalArea(length, width, roundedRadius);
        }

        // Handles CORBA exceptions
        catch (const CORBA::Exception& exception) {
            #ifdef GSDEBUGMSG
            cerr << ">> GEARSystem: Sensor::setGoalArea(float, float, float): ";
            cerr << "Caught CORBA exception: " << exception._name() << "!!" << endl << flush;
            #endif
        }
    }
    else {
        #ifdef GSDEBUGMSG
        cerr << ">> GEARSystem: Sensor::setGoalArea(float, float, float): ";
        cerr << "The sensor is not connected!!" << endl << flush;
        #endif
    }
}

void Sensor::setGoalDepth(float depth) {
    // Sets the goal depth
    if (isConnected()) {
        try {
            _corbaSensor->setGoalDepth(depth);
        }

        // Handles CORBA exceptions
        catch (const CORBA::Exception& exception) {
            #ifdef GSDEBUGMSG
            cerr << ">> GEARSystem: Sensor::setGoalDepth(float): ";
            cerr << "Caught CORBA exception: " << exception._name() << "!!" << endl << flush;
            #endif
        }
    }
    else {
        #ifdef GSDEBUGMSG
        cerr << ">> GEARSystem: Sensor::setGoalDepth(float): ";
        cerr << "The sensor is not connected!!" << endl << flush;
        #endif
    }
}

void Sensor::setLeftPenaltyMark(const Position& position) {
    // Sets the mark position
    if (isConnected()) {
        try {
            CORBATypes::Position corbaPosition;
            position.toCORBA(&corbaPosition);
            _corbaSensor->setLeftPenaltyMark(corbaPosition);
        }

        // Handles CORBA exceptions
        catch (const CORBA::Exception& exception) {
            #ifdef GSDEBUGMSG
            cerr << ">> GEARSystem: Sensor::setLeftPenaltyMark(const Position&): ";
            cerr << "Caught CORBA exception: " << exception._name() << "!!" << endl << flush;
            #endif
        }
    }
    else {
        #ifdef GSDEBUGMSG
        cerr << ">> GEARSystem: Sensor::setLeftPenaltyMark(const Position&): ";
        cerr << "The sensor is not connected!!" << endl << flush;
        #endif
    }
}

void Sensor::setRightPenaltyMark(const Position& position) {
    // Sets the mark position
    if (isConnected()) {
        try {
            CORBATypes::Position corbaPosition;
            position.toCORBA(&corbaPosition);
            _corbaSensor->setRightPenaltyMark(corbaPosition);
        }

        // Handles CORBA exceptions
        catch (const CORBA::Exception& exception) {
            #ifdef GSDEBUGMSG
            cerr << ">> GEARSystem: Sensor::setRightPenaltyMark(const Position&): ";
            cerr << "Caught CORBA exception: " << exception._name() << "!!" << endl << flush;
            #endif
        }
    }
    else {
        #ifdef GSDEBUGMSG
        cerr << ">> GEARSystem: Sensor::setRightPenaltyMark(const Position&): ";
        cerr << "The sensor is not connected!!" << endl << flush;
        #endif
    }
}

void Sensor::setFieldCenterRadius(float centerRadius) {
    // Sets the center radius
    if (isConnected()) {
        try {
            _corbaSensor->setFieldCenterRadius(centerRadius);
        }

        // Handles CORBA exceptions
        catch (const CORBA::Exception& exception) {
            #ifdef GSDEBUGMSG
            cerr << ">> GEARSystem: Sensor::setFieldCenterRadius(float): ";
            cerr << "Caught CORBA exception: " << exception._name() << "!!" << endl << flush;
            #endif
        }
    }
    else {
        #ifdef GSDEBUGMSG
        cerr << ">> GEARSystem: Sensor::setFieldCenterRadius(float): ";
        cerr << "The sensor is not connected!!" << endl << flush;
        #endif
    }
}
