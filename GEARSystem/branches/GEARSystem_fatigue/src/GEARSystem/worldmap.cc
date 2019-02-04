/*** GEARSystem - WorldMap implementation
  ** GEAR - Grupo de Estudos Avancados em Robotica
  ** Department of Electrical Engineering, University of Sao Paulo
  ** http://www.sel.eesc.usp.br/gear
  ** This file is part of the GEARSystem project
  ***/


// Includes the class header
#include <GEARSystem/worldmap.hh>


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
  ** Description: Creates a world map
  ** Recieves:    Nothing
  ***/
WorldMap::WorldMap() {
    // Initializes the variables
    _nTeams = 0;
    _nBalls = 0;

    _validTeams.clear();
    _teams.clear();
    _validBalls.clear();
    _ballsPositions.clear();
    _ballsVelocities.clear();

    // Creates the locks
    //#ifdef GSTHREADSAFE
    _ballsLock = new QReadWriteLock();
    _teamsLock = new QReadWriteLock();
    //#endif
}

WorldMap::~WorldMap() {
    //#ifdef GSTHREADSAFE
    delete _ballsLock;
    delete _teamsLock;
    //#endif
}

/*** Teams handling functions
  ** Description: Handles the teams
  ** Receives:    [teamNum] The team number
                  [name]    The team name
  ** Returns:     Nothing
  ***/
void WorldMap::addTeam(uint8 teamNum, const QString& name) {
    // Handles the lock
    //#ifdef GSTHREADSAFE
    QWriteLocker teamsLocker(_teamsLock);
    // TODO: Fix fault at this point
    //#endif

    // Adds the team
    (void) _teams.remove(teamNum);
    (void) _validTeams.insert(teamNum, true);
    _teams[teamNum] = Team(teamNum, name);
    _nTeams++;
}

void WorldMap::delTeam(uint8 teamNum) {
    // Handles the lock
    //#ifdef GSTHREADSAFE
    QWriteLocker teamsLocker(_teamsLock);
    // TODO: Fix fault at this point
    //#endif

    // Deletes the team
    (void) _validTeams.remove(teamNum);
    (void) _teams.remove(teamNum);
    _nTeams--;
}

QList<uint8> WorldMap::teams() const {
    // Handles the lock
    //#ifdef GSTHREADSAFE
    QReadLocker teamsLocker(_teamsLock);
    // TODO: Fix fault at this point
    //#endif

    // Adds the teams to the list
    QList<uint8> teamsList;
    QHashIterator<uint8,Team> it(_teams);
    while (it.hasNext()) {
        teamsList.append(it.next().key());
    }

    // Returns the list
    return(teamsList);
}


/*** Team info functions
  ** Description: Controls team name and number
  ***/
const QString WorldMap::teamName(uint8 teamNum) const {
    // Handles the lock
    //#ifdef GSTHREADSAFE
    QReadLocker teamsLocker(_teamsLock);
    // TODO: Fix fault at this point
    //#endif

    // Returns the team name
    if (_validTeams.value(teamNum)) {
        return(_teams[teamNum].name());
    }
    else {
        #ifdef GSDEBUGMSG
        cerr << ">> GEARSystem: WorldMap::teamName(uint8): No such Team #";
        cerr << int(teamNum) << " in this map!!" << endl << flush;
        #endif
    }

    // Returns an invalid name
    return(_invalidName);
}

uint8 WorldMap::teamNumber(const QString& name) const {
    // Handles the lock
    //#ifdef GSTHREADSAFE
    QReadLocker teamsLocker(_teamsLock);
    // TODO: Fix fault at this point
    //#endif

    // Runs the teams searching for the wanted name
    QHashIterator<uint8,Team> it(_teams);
    while (it.hasNext()) {
        it.next();
        if (it.value().name() == name) {
            return(it.value().number());
        }
    }

    #ifdef GSDEBUGMSG
    cerr << ">> GEARSystem: WorldMap::teamNumber(const QString&): No such Team ";
    cerr << name.toStdString() << " in this map!!" << endl << flush;
    #endif

    // Returns an invalid number
    return(_invalidNumber);
}


/*** Balls handling functions
  ** Description: Handles the balls
  ** Receives:    [ballNum] The ball number
  ** Returns:     Nothing
  ***/
void WorldMap::addBall(uint8 ballNum) {
    // Handles the lock
    //#ifdef GSTHREADSAFE
    QWriteLocker ballsLocker(_ballsLock);
    // TODO: Fix fault at this point
    //#endif

    // Adds the ball
    (void) _validBalls.insert(ballNum, true);
    (void) _ballsPositions.insert(ballNum, new Position(false,0,0,0));
    (void) _ballsVelocities.insert(ballNum, new Velocity(false,0,0));
}

void WorldMap::delBall(uint8 ballNum) {
    // Handles the lock
    //#ifdef GSTHREADSAFE
    QWriteLocker ballsLocker(_ballsLock);
    // TODO: Fix fault at this point
    //#endif

    // Deletes the ball
    (void) _validBalls.remove(ballNum);
    (void) _ballsPositions.remove(ballNum);
    (void) _ballsVelocities.remove(ballNum);
}

QList<uint8> WorldMap::balls() const {
    // Handles the lock
    //#ifdef GSTHREADSAFE
    QReadLocker ballsLocker(_ballsLock);
    // TODO: Fix fault at this point
    //#endif

    // Adds the balls to the list
    QList<uint8> ballsList;
    QHashIterator<uint8,Position*> it(_ballsPositions);
    while (it.hasNext()) {
        ballsList.append(it.next().key());
    }

    // Returns the list
    return(ballsList);
}


/*** 'ballPosition' function
  ** Description: Gets the ball position
  ** Receives:    [ballNum] The ball number
  ** Returns:     The ball position
  ***/
const Position WorldMap::ballPosition(uint8 ballNum) const {
    // Handles the lock
    //#ifdef GSTHREADSAFE
    QReadLocker ballsLocker(_ballsLock);
    // TODO: Fix fault at this point
    //#endif

    // Returns the ball position
    if (_validBalls.value(ballNum)) {
        return(*(_ballsPositions[ballNum]));
    }
    else {
        #ifdef GSDEBUGMSG
        cerr << ">> GEARSystem: WorldMap::ballPosition(uint8): No such Ball #";
        cerr << int(ballNum) << " in this map!!" << endl << flush;
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
const Velocity WorldMap::ballVelocity(uint8 ballNum) const {
    // Handles the lock
    //#ifdef GSTHREADSAFE
    QReadLocker ballsLocker(_ballsLock);
    // TODO: Fix fault at this point
    //#endif

    // Returns the ball velocity
    if (_validBalls.value(ballNum)) {
        return(*(_ballsVelocities[ballNum]));
    }
    else {
        #ifdef GSDEBUGMSG
        cerr << ">> GEARSystem: WorldMap::ballVelocity(uint8): No such Ball #";
        cerr << int(ballNum) << " in this map!!" << endl << flush;
        #endif
    }

    // Returns an invalid velocity
    return(_invalidVelocity);
}

/*** 'setBallPosition' function
  ** Description: Sets the ball position
  ** Receives:    [ballNum]  The ball number
                  [position] The ball position
  ** Returns:     Nothing
  ***/
void WorldMap::setBallPosition(uint8 ballNum, const Position& position) {
    // Handles the lock
    //#ifdef GSTHREADSAFE
    QWriteLocker ballsLocker(_ballsLock);
    // TODO: Fix fault at this point
    //#endif

    // Sets the ball position
    if (_validBalls.value(ballNum)) {
        (void) _ballsPositions.value(ballNum)->operator =(position);
    }
    else {
        #ifdef GSDEBUGMSG
        cerr << ">> GEARSystem: WorldMap::setBallPosition(uint8, const Position&): No such Ball #";
        cerr << int(ballNum) << " in this map!!" << endl << flush;
        #endif
    }
}

/*** 'setBallVelocity' function
  ** Description: Sets the ball velocity
  ** Receives:    [ballNum]  The ball number
                  [velocity] The ball velocity
  ** Returns:     Nothing
  ***/
void WorldMap::setBallVelocity(uint8 ballNum, const Velocity& velocity) {
    // Handles the lock
    //#ifdef GSTHREADSAFE
    QWriteLocker ballsLocker(_ballsLock);
    // TODO: Fix fault at this point
    //#endif

    // Sets the ball velocity
    if (_validBalls.value(ballNum)) {
        (void) _ballsVelocities.value(ballNum)->operator =(velocity);
    }
    else {
        #ifdef GSDEBUGMSG
        cerr << ">> GEARSystem: WorldMap::setBallVelocity(uint8, const Velocity&): No such Ball #";
        cerr << int(ballNum) << " in this map!!" << endl << flush;
        #endif
    }
}


/*** Players handling functions
  ** Description: Handles the teams players
  ** Receives:    [teamNum]   The team number
                  [playerNum] The player number
  ** Returns:     Nothing
  ***/
void WorldMap::addPlayer(uint8 teamNum, uint8 playerNum) {
    // Handles the lock
    //#ifdef GSTHREADSAFE
    QWriteLocker teamsLocker(_teamsLock);
    // TODO: Fix fault at this point
    //#endif

    // Adds the player
    if (_validTeams.value(teamNum)) {
        _teams[teamNum].addPlayer(playerNum);
    }
    else {
        #ifdef GSDEBUGMSG
        cerr << ">> GEARSystem: WorldMap::addPlayer(uint8, uint8): No such Team #";
        cerr << int(teamNum) << " in this map!!" << endl << flush;
        #endif
    }
}

void WorldMap::delPlayer(uint8 teamNum, uint8 playerNum) {
    // Handles the lock
    //#ifdef GSTHREADSAFE
    QWriteLocker teamsLocker(_teamsLock);
    // TODO: Fix fault at this point
    //#endif

    // Deletes the player
    if (_validTeams.value(teamNum)) {
        _teams[teamNum].delPlayer(playerNum);
    }
    else {
        #ifdef GSDEBUGMSG
        cerr << ">> GEARSystem: WorldMap::delPlayer(uint8, uint8): No such Team #";
        cerr << int(teamNum) << " in this map!!" << endl << flush;
        #endif
    }
}

QList<uint8> WorldMap::players(uint8 teamNum) const {
    // Handles the lock
    //#ifdef GSTHREADSAFE
    QReadLocker teamsLocker(_teamsLock);
    // TODO: Fix fault at this point
    //#endif

    // Returns the players list
    if (_validTeams.value(teamNum)) {
        return(_teams[teamNum].players());
    }
    else {
        #ifdef GSDEBUGMSG
        cerr << ">> GEARSystem: WorldMap::players(uint8): No such Team #";
        cerr << int(teamNum) << " in this map!!" << endl << flush;
        #endif
    }

    // Returns an empty list
    return(QList<uint8>());
}


/*** Gets functions
  ** Description: Gets the player pose, velocity and angular speed
  ** Receives:    [teamNum]   The team number
                  [playerNum] The player number
  ** Returns:     The player position, orientation, velocity or angular speed
  ***/
const Position& WorldMap::playerPosition(uint8 teamNum, uint8 playerNum) const {
    // Handles the lock
    //#ifdef GSTHREADSAFE
    QReadLocker teamsLocker(_teamsLock);
    // TODO: Fix fault at this point
    //#endif

    // Returns an invalid position
    if (!_validTeams.value(teamNum)) {
        #ifdef GSDEBUGMSG
        cerr << ">> GEARSystem: WorldMap::playerPosition(uint8, uint8): No such Team #";
        cerr << int(teamNum) << " in this map!!" << endl << flush;
        #endif
        return(_invalidPosition);
    }

    // Returns the player position
    return(*(_teams[teamNum].position(playerNum)));
}

const Angle& WorldMap::playerOrientation(uint8 teamNum, uint8 playerNum) const {
    // Handles the lock
    //#ifdef GSTHREADSAFE
    QReadLocker teamsLocker(_teamsLock);
    // TODO: Fix fault at this point
    //#endif

    // Returns an invalid orientation
    if (!_validTeams.value(teamNum)) {
        #ifdef GSDEBUGMSG
        cerr << ">> GEARSystem: WorldMap::playerOrientation(uint8, uint8): No such Team #";
        cerr << int(teamNum) << " in this map!!" << endl << flush;
        #endif
        return(_invalidAngle);
    }

    // Returns the player orientation
    return(*(_teams[teamNum].orientation(playerNum)));
}

const Velocity& WorldMap::playerVelocity(uint8 teamNum, uint8 playerNum) const {
    // Handles the lock
    //#ifdef GSTHREADSAFE
    QReadLocker teamsLocker(_teamsLock);
    // TODO: Fix fault at this point
    //#endif

    // Returns an invalid velocity
    if (!_validTeams.value(teamNum)) {
        #ifdef GSDEBUGMSG
        cerr << ">> GEARSystem: WorldMap::playerVelocity(uint8, uint8): No such Team #";
        cerr << int(teamNum) << " in this map!!" << endl << flush;
        #endif
        return(_invalidVelocity);
    }

    // Returns the player velocity
    return(*(_teams[teamNum].velocity(playerNum)));
}

const AngularSpeed& WorldMap::playerAngularSpeed(uint8 teamNum, uint8 playerNum) const {
    // Handles the lock
    //#ifdef GSTHREADSAFE
    QReadLocker teamsLocker(_teamsLock);
    // TODO: Fix fault at this point
    //#endif

    // Returns an invalid speed
    if (!_validTeams.value(teamNum)) {
        #ifdef GSDEBUGMSG
        cerr << ">> GEARSystem: WorldMap::playerAngularSpeed(uint8, uint8): No such Team #";
        cerr << int(teamNum) << " in this map!!" << endl << flush;
        #endif
        return(_invalidAngularSpeed);
    }

    // Returns the player angular speed
    return(*(_teams[teamNum].angularSpeed(playerNum)));
}

bool WorldMap::ballPossession(uint8 teamNum, uint8 playerNum) const {
    // Handles the lock
    //#ifdef GSTHREADSAFE
    QReadLocker teamsLocker(_teamsLock);
    // TODO: Fix fault at this point
    //#endif

    // Returns the flag
    if (!_validTeams.value(teamNum)) {
        #ifdef GSDEBUGMSG
        cerr << ">> GEARSystem: WorldMap::ballPossession(uint8, uint8): No such Team #";
        cerr << int(teamNum) << " in this map!!" << endl << flush;
        #endif
        return(false);
    }

    // Returns the flag
    return(_teams[teamNum].ballPossession(playerNum));
}

float WorldMap::fatigue(uint8 teamNum, uint8 playerNum) const {
    // Handles the lock
    //#ifdef GSTHREADSAFE
    QReadLocker teamsLocker(_teamsLock);
    // TODO: Fix fault at this point
    //#endif

    // Returns the flag
    if (!_validTeams.value(teamNum)) {
        #ifdef GSDEBUGMSG
        cerr << ">> GEARSystem: WorldMap::fatigue(uint8, uint8): No such Team #";
        cerr << int(teamNum) << " in this map!!" << endl << flush;
        #endif
        return(false);
    }

    // Returns the flag
    return(_teams[teamNum].fatigue(playerNum));
}

/*** 'setPlayerPosition' function
  ** Description: Sets the player position
  ** Receives:    [teamNum]   The team number
                  [playerNum] The player number
                  [position]  The player position
  ** Returns:     Nothing
  ***/
void WorldMap::setPlayerPosition(uint8 teamNum, uint8 playerNum, const Position& position) {
    // Handles the lock
    //#ifdef GSTHREADSAFE
    QWriteLocker teamsLocker(_teamsLock);
    // TODO: Fix fault at this point
    //#endif

    // Sets the player position
    if (_validTeams.value(teamNum)) {
        _teams[teamNum].setPosition(playerNum, position);
    }
    else {
        #ifdef GSDEBUGMSG
        cerr << ">> GEARSystem: WorldMap::setPlayerPosition(uint8, uint8, const Position&): No such Team #";
        cerr << int(teamNum) << " in this map!!" << endl << flush;
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
void WorldMap::setPlayerOrientation(uint8 teamNum, uint8 playerNum, const Angle& orientation) {
    // Handles the lock
    //#ifdef GSTHREADSAFE
    QWriteLocker teamsLocker(_teamsLock);
    // TODO: Fix fault at this point
    //#endif

    // Sets the player orientation
    if (_validTeams.value(teamNum)) {
        _teams[teamNum].setOrientation(playerNum, orientation);
    }
    else {
        #ifdef GSDEBUGMSG
        cerr << ">> GEARSystem: WorldMap::setPlayerOrientation(uint8, uint8, const Orientation&): No such Team #";
        cerr << int(teamNum) << " in this map!!" << endl << flush;
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
void WorldMap::setPlayerVelocity(uint8 teamNum, uint8 playerNum, const Velocity& velocity) {
    // Handles the lock
    //#ifdef GSTHREADSAFE
    QWriteLocker teamsLocker(_teamsLock);
    // TODO: Fix fault at this point
    //#endif

    // Sets the player velocity
    if (_validTeams.value(teamNum)) {
        _teams[teamNum].setVelocity(playerNum, velocity);
    }
    else {
        #ifdef GSDEBUGMSG
        cerr << ">> GEARSystem: WorldMap::setPlayerVelocity(uint8, uint8, const Velocity&): No such Team #";
        cerr << int(teamNum) << " in this map!!" << endl << flush;
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
void WorldMap::setPlayerAngularSpeed(uint8 teamNum, uint8 playerNum, const AngularSpeed& angularSpeed) {
    // Handles the lock
    //#ifdef GSTHREADSAFE
    QWriteLocker teamsLocker(_teamsLock);
    // TODO: Fix fault at this point
    //#endif

    // Sets the player angular speed
    if (_validTeams.value(teamNum)) {
        _teams[teamNum].setAngularSpeed(playerNum, angularSpeed);
    }
    else {
        #ifdef GSDEBUGMSG
        cerr << ">> GEARSystem: WorldMap::setPlayerAngularSpeed(uint8, uint8, const AngularSpeed&): No such Team #";
        cerr << int(teamNum) << " in this map!!" << endl << flush;
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
void WorldMap::setBallPossession(uint8 teamNum, uint8 playerNum, bool possession) {
    // Handles the lock
    //#ifdef GSTHREADSAFE
    QWriteLocker teamsLocker(_teamsLock);
    // TODO: Fix fault at this point
    //#endif

    // Sets the flag
    if (_validTeams.value(teamNum)) {
        _teams[teamNum].setBallPossession(playerNum, possession);
    }
    else {
        #ifdef GSDEBUGMSG
        cerr << ">> GEARSystem: WorldMap::setBallPossession(uint8, uint8, bool): No such Team #";
        cerr << int(teamNum) << " in this map!!" << endl << flush;
        #endif
    }
}


/*** 'fatigue' function
  ** Description: Indicates the player's fatigue
  ** Receives:    [teamNum]    The team number
                  [playerNum]  The player number
                  [fatigue] float value indicating the player fatigue
  ** Returns:     Nothing
  ***/
void WorldMap::setFatigue(uint8 teamNum, uint8 playerNum, float fatigue) {
    // Handles the lock
    //#ifdef GSTHREADSAFE
    QWriteLocker teamsLocker(_teamsLock);
    // TODO: Fix fault at this point
    //#endif

    // Sets the flag
    if (_validTeams.value(teamNum)) {
        _teams[teamNum].setFatigue(playerNum, fatigue);
    }
    else {
        #ifdef GSDEBUGMSG
        cerr << ">> GEARSystem: WorldMap::setFatigue(uint8, uint8, float): No such Team #";
        cerr << int(teamNum) << " in this map!!" << endl << flush;
        #endif
    }
}


/*** Field handling functions
  ** Description: Handles field info
  ***/
void WorldMap::setFieldTopRightCorner(const Position& position)    { _field.setTopRightCorner(position);  }
void WorldMap::setFieldTopLeftCorner(const Position& position)     { _field.setTopLeftCorner(position);   }
void WorldMap::setFieldBottomLeftCorner(const Position& position)  { _field.setBottomLeftCorner(position);  }
void WorldMap::setFieldBottomRightCorner(const Position& position) { _field.setBottomRightCorner(position); }
void WorldMap::setFieldCenter(const Position& position)            { _field.setCenter(position); }

void WorldMap::setLeftGoalPosts(const Position& leftPost, const Position& rightPost) {
    _field.setLeftGoalPosts(leftPost, rightPost);
}
void WorldMap::setRightGoalPosts(const Position& leftPost, const Position& rightPost) {
    _field.setRightGoalPosts(leftPost, rightPost);
}

void WorldMap::setGoalArea(float length, float width, float roundedRadius) {
    _field.setGoalArea(length, width, roundedRadius);
}

void WorldMap::setGoalDepth(float depth) {
    _field.setGoalDepth(depth);
}

void WorldMap::setLeftPenaltyMark(const Position& position)  { _field.setLeftPenaltyMark(position); }
void WorldMap::setRightPenaltyMark(const Position& position) { _field.setRightPenaltyMark(position); }

void WorldMap::setFieldCenterRadius(float centerRadius) { _field.setCenterRadius(centerRadius); }

const Position& WorldMap::fieldTopRightCorner()    const { return(_field.topRightCorner()); }
const Position& WorldMap::fieldTopLeftCorner()     const { return(_field.topLeftCorner()); }
const Position& WorldMap::fieldBottomLeftCorner()  const { return(_field.bottomLeftCorner()); }
const Position& WorldMap::fieldBottomRightCorner() const { return(_field.bottomRightCorner()); }
const Position& WorldMap::fieldCenter()            const { return(_field.center()); }

const Goal& WorldMap::leftGoal()  const { return(_field.leftGoal()); }
const Goal& WorldMap::rightGoal() const { return(_field.rightGoal()); }

const Position& WorldMap::leftPenaltyMark()  const { return(_field.leftPenaltyMark()); }
const Position& WorldMap::rightPenaltyMark() const { return(_field.rightPenaltyMark()); }

float WorldMap::fieldCenterRadius() const { return(_field.centerRadius()); }
