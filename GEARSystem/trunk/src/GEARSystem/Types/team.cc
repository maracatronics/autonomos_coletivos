/*** GEARSystem - Team implementation
  ** GEAR - Grupo de Estudos Avancados em Robotica
  ** Department of Electrical Engineering, University of Sao Paulo
  ** http://www.sel.eesc.usp.br/gear
  ** This file is part of the GEARSystem project
  ***/


// Includes the class header
#include <GEARSystem/Types/team.hh>


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
  ** Description: Creates an invalid team
  ** Recieves:    Nothing
  ***/
Team::Team() {
    // Sets as invalid
    setInvalid();

    // Creates invalid types
    _invalidPosition     = new Position();
    _invalidAngle        = new Angle();
    _invalidVelocity     = new Velocity();
    _invalidAngularSpeed = new AngularSpeed();

    // Initializes the players
    _nPlayers = 0;
    _validPlayers.clear();
    _playersPositions.clear();
    _playersOrientations.clear();
    _playersVelocities.clear();
    _playersAngularSpeeds.clear();
    _ballPossessions.clear();

    // Creates the locks
    #ifdef GSTHREADSAFE
    _positionsLock     = new QReadWriteLock();
    _orientationsLock  = new QReadWriteLock();
    _velocitiesLock    = new QReadWriteLock();
    _angularSpeedsLock = new QReadWriteLock();
    _possessionsLock   = new QReadWriteLock();
    #endif
}

/*** Constructor
  ** Description: Creates a team
  ** Recieves:    [teamNumber] The team number
                  [teamName]   The team name
  ***/
Team::Team(uint8 teamNumber, QString teamName) {
    // Sets team info
    _number = teamNumber;
    _name   = teamName;
    _valid  = true;

    // Creates invalid types
    _invalidPosition     = new Position();
    _invalidAngle        = new Angle();
    _invalidVelocity     = new Velocity();
    _invalidAngularSpeed = new AngularSpeed();

    // Initializes the players
    _nPlayers = 0;
    _validPlayers.clear();
    _playersPositions.clear();
    _playersOrientations.clear();
    _playersVelocities.clear();
    _playersAngularSpeeds.clear();
    _ballPossessions.clear();

    // Creates the locks
    #ifdef GSTHREADSAFE
    _positionsLock     = new QReadWriteLock();
    _orientationsLock  = new QReadWriteLock();
    _velocitiesLock    = new QReadWriteLock();
    _angularSpeedsLock = new QReadWriteLock();
    _possessionsLock   = new QReadWriteLock();
    #endif
}


/*** Players handling functions
  ** Description: Handles the team players
  ** Receives:    [playerNum] The player number
  ** Returns:     Nothing
  ***/
void Team::addPlayer(uint8 playerNum) {
    // Handles the locks
    #ifdef GSTHREADSAFE
    QWriteLocker positionsLocker(_positionsLock);
    QWriteLocker orientationsLocker(_orientationsLock);
    QWriteLocker velocitiesLocker(_velocitiesLock);
    QWriteLocker angularSpeedsLocker(_angularSpeedsLock);
    QWriteLocker possessionsLocker(_possessionsLock);
    // TODO: Fix fault at this point
    #endif

    // Adds the player
    (void) _validPlayers.insert(playerNum, true);
    (void) _playersPositions.insert(playerNum, new Position(false,0,0,0));
    (void) _playersOrientations.insert(playerNum, new Angle(false,0));
    (void) _playersVelocities.insert(playerNum, new Velocity(false,0,0));
    (void) _playersAngularSpeeds.insert(playerNum, new AngularSpeed(false,0));
    (void) _ballPossessions.insert(playerNum, false);
    _nPlayers++;
}

void Team::delPlayer(uint8 playerNum) {
    // Handles the locks
    #ifdef GSTHREADSAFE
    QWriteLocker positionsLocker(_positionsLock);
    QWriteLocker orientationsLocker(_orientationsLock);
    QWriteLocker velocitiesLocker(_velocitiesLock);
    QWriteLocker angularSpeedsLocker(_angularSpeedsLock);
    QWriteLocker possessionsLocker(_possessionsLock);
    // TODO: Fix fault at this point
    #endif

    // Deletes the player
    (void) _validPlayers.remove(playerNum);
    (void) delete(_playersPositions[playerNum]);
    (void) delete(_playersOrientations[playerNum]);
    (void) delete(_playersVelocities[playerNum]);
    (void) delete(_playersAngularSpeeds[playerNum]);
    (void) _playersPositions.remove(playerNum);
    (void) _playersOrientations.remove(playerNum);
    (void) _playersVelocities.remove(playerNum);
    (void) _playersAngularSpeeds.remove(playerNum);
    (void) _ballPossessions.remove(playerNum);
    _nPlayers--;
}

QList<uint8> Team::players() const {
    // Adds the players to the list
    QList<uint8> playersList;
    QHashIterator<uint8,Position*> it(_playersPositions);
    while (it.hasNext()) {
        playersList.append(it.next().key());
    }

    // Returns the list
    return(playersList);
}


/*** Team info functions
  ** Description: Controls team name and number
  ***/
const QString& Team::name() const { return(_name); }
uint8 Team::number() const { return(_number); }
void  Team::setName(const QString& teamName) { _name = teamName; }
void  Team::setNumber(uint8 teamNumber) {
    _valid  = true;
    _number = teamNumber;
}


/*** 'setPosition' function
  ** Description: Sets the player position
  ** Receives:    [playerNum]   The player number
                  [thePosition] The player position
  ** Returns:     Nothing
  ***/
void Team::setPosition(uint8 playerNum, const Position& thePosition) {
    // Handles the lock
    #ifdef GSTHREADSAFE
    QWriteLocker positionsLocker(_positionsLock);
    // TODO: Fix fault at this point
    #endif

    // Sets the player position
    if (_validPlayers.value(playerNum)) {
        (void) _playersPositions.value(playerNum)->operator =(thePosition);
    }
    else {
        #ifdef GSDEBUGMSG
        //cerr << ">> GEARSystem: Team::setPosition(uint8, const Position&): No such Player #" << int(playerNum);
        //cerr << " in Team #" << int(_number) << "(" << _name.toStdString() << ")!!" << endl << flush;
        #endif
    }
}

/*** 'setOrientation' function
  ** Description: Sets the player orientation
  ** Receives:    [playerNum]      The player number
                  [theOrientation] The player orientation
  ** Returns:     Nothing
  ***/
void Team::setOrientation(uint8 playerNum, const Angle& theOrientation) {
    // Handles the lock
    #ifdef GSTHREADSAFE
    QWriteLocker orientationsLocker(_orientationsLock);
    // TODO: Fix fault at this point
    #endif

    // Sets the player orientation
    if (_validPlayers.value(playerNum)) {
        (void) _playersOrientations.value(playerNum)->operator =(theOrientation);
    }
    else {
        #ifdef GSDEBUGMSG
        cerr << ">> GEARSystem: Team::setOrientation(uint8, const Angle&): No such Player #" << int(playerNum);
        cerr << " in Team #" << int(_number) << "(" << _name.toStdString() << ")!!" << endl << flush;
        #endif
    }
}

/*** 'setVelocity' function
  ** Description: Sets the player velocity
  ** Receives:    [playerNum] The player number
                  [theVelocity]  The player velocity
  ** Returns:     Nothing
  ***/
void Team::setVelocity(uint8 playerNum, const Velocity& theVelocity) {
    // Handles the lock
    #ifdef GSTHREADSAFE
    QWriteLocker velocitiesLocker(_velocitiesLock);
    // TODO: Fix fault at this point
    #endif

    // Sets the player velocity
    if (_validPlayers.value(playerNum)) {
        (void) _playersVelocities.value(playerNum)->operator =(theVelocity);
    }
    else {
        #ifdef GSDEBUGMSG
        cerr << ">> GEARSystem: Team::setVelocity(uint8, const Velocity&): No such Player #" << int(playerNum);
        cerr << " in Team #" << int(_number) << "(" << _name.toStdString() << ")!!" << endl << flush;
        #endif
    }
}

/*** 'setAngularSpeed' function
  ** Description: Sets the player angular speed
  ** Receives:    [playerNum]    The player number
                  [theAngularSpeed] The player angular speed
  ** Returns:     Nothing
  ***/
void Team::setAngularSpeed(uint8 playerNum, const AngularSpeed& theAngularSpeed) {
    // Handles the lock
    #ifdef GSTHREADSAFE
    QWriteLocker angularSpeedsLocker(_angularSpeedsLock);
    // TODO: Fix fault at this point
    #endif

    // Sets the player speed
    if (_validPlayers.value(playerNum)) {
        (void) _playersAngularSpeeds.value(playerNum)->operator =(theAngularSpeed);
    }
    else {
        #ifdef GSDEBUGMSG
        cerr << ">> GEARSystem: Team::setAngularSpeed(uint8, const AngularSpeed&): No such Player #" << int(playerNum);
        cerr << " in Team #" << int(_number) << "(" << _name.toStdString() << ")!!" << endl << flush;
        #endif
    }
}

/*** 'setBallPossession' function
  ** Description: Indicates if the player possesses a ball
  ** Receives:    [playerNum]  The player number
                  [possession] 'true' if the player has the ball, 'false' otherwise
  ** Returns:     Nothing
  ***/
void Team::setBallPossession(uint8 playerNum, bool possession) {
    // Handles the lock
    #ifdef GSTHREADSAFE
    QWriteLocker possessionsLocker(_possessionsLock);
    // TODO: Fix fault at this point
    #endif

    // Sets the flag
    if (_validPlayers.value(playerNum)) {
        (void) _ballPossessions.insert(playerNum, possession);
    }
    else {
        #ifdef GSDEBUGMSG
        cerr << ">> GEARSystem: Team::setBallPossession(uint8, bool): No such Player #" << int(playerNum);
        cerr << " in Team #" << int(_number) << "(" << _name.toStdString() << ")!!" << endl << flush;
        #endif
    }
}


/*** Gets functions
  ** Description: Gets the player pose, velocity and angular speed
  ** Receives:    [playerNum] The player number
  ** Returns:     The player position, orientation, velocity or angular speed
  ***/
const Position* Team::position(uint8 playerNum) const {
    // Handles the lock
    #ifdef GSTHREADSAFE
    QReadLocker positionsLocker(_positionsLock);
    // TODO: Fix fault at this point
    #endif

    // Returns the player position
    if (_validPlayers.value(playerNum)) {
        return(_playersPositions.value(playerNum));
    }
    else {
        #ifdef GSDEBUGMSG
        cerr << ">> GEARSystem: Team::position(uint8): No such Player #" << int(playerNum) << " in Team #";
        cerr << int(_number) << "(" << _name.toStdString() << ")!!" << endl << flush;
        #endif
    }

    // Returns an invalid position
    return(_invalidPosition);
}

const Angle* Team::orientation(uint8 playerNum) const {
    // Handles the lock
    #ifdef GSTHREADSAFE
    QReadLocker orientationsLocker(_orientationsLock);
    // TODO: Fix fault at this point
    #endif

    // Returns the player orientation
    if (_validPlayers.value(playerNum)) {
        return(_playersOrientations.value(playerNum));
    }
    else {
        #ifdef GSDEBUGMSG
        cerr << ">> GEARSystem: Team::orientation(uint8): No such Player #" << int(playerNum) << " in Team #";
        cerr << int(_number) << "(" << _name.toStdString() << ")!!" << endl << flush;
        #endif
    }

    // Returns an invalid angle
    return(_invalidAngle);
}

const Velocity* Team::velocity(uint8 playerNum) const {
    // Handles the lock
    #ifdef GSTHREADSAFE
    QReadLocker velocitiesLocker(_velocitiesLock);
    // TODO: Fix fault at this point
    #endif

    // Returns the player velocity
    if (_validPlayers.value(playerNum)) {
        return(_playersVelocities.value(playerNum));
    }
    else {
        #ifdef GSDEBUGMSG
        cerr << ">> GEARSystem: Team::velocity(uint8): No such Player #" << int(playerNum) << " in Team #";
        cerr << int(_number) << "(" << _name.toStdString() << ")!!" << endl << flush;
        #endif
    }

    // Returns an invalid velocity
    return(_invalidVelocity);
}

const AngularSpeed* Team::angularSpeed(uint8 playerNum) const {
    // Handles the lock
    #ifdef GSTHREADSAFE
    QReadLocker angularSpeedsLocker(_angularSpeedsLock);
    // TODO: Fix fault at this point
    #endif

    // Returns the player speed
    if (_validPlayers.value(playerNum)) {
        return(_playersAngularSpeeds.value(playerNum));
    }
    else {
        #ifdef GSDEBUGMSG
        cerr << ">> GEARSystem: Team::angularSpeed(uint8): No such Player #" << int(playerNum) << " in Team #";
        cerr << int(_number) << "(" << _name.toStdString() << ")!!" << endl << flush;
        #endif
    }

    // Returns an invalid speed
    return(_invalidAngularSpeed);
}

bool Team::ballPossession(uint8 playerNum) const {
    // Handles the lock
    #ifdef GSTHREADSAFE
    QReadLocker possessionsLocker(_possessionsLock);
    // TODO: Fix fault at this point
    #endif

    // Returns the flag
    if (_validPlayers.value(playerNum)) {
        return(_ballPossessions.value(playerNum));
    }
    else {
        #ifdef GSDEBUGMSG
        cerr << ">> GEARSystem: Team::ballPossession(uint8): No such Player #" << int(playerNum) << " in Team #";
        cerr << int(_number) << "(" << _name.toStdString() << ")!!" << endl << flush;
        #endif
    }

    // Returns 'false'
    return(false);
}


// Info functions
bool Team::isValid() const { return(_valid); }
void Team::setInvalid() {
    _valid = false;
    _validPlayers.clear();
}
