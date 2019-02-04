/*** GEARSystem - CORBA Sensor implementation
  ** GEAR - Grupo de Estudos Avancados em Robotica
  ** Department of Electrical Engineering, University of Sao Paulo
  ** http://www.sel.eesc.usp.br/gear
  ** This file is part of the GEARSystem project
  ***/


// Includes the class header
#include <GEARSystem/CORBAImplementations/corbasensor.hh>


// Includes omniORB 4
#include <omniORB4/CORBA.h>


// Selects namespace
using namespace GEARSystem;
using CORBA::Boolean;
using CORBA::Float;
using CORBA::Octet;


/*** Constructor
  ** Description: Creates the sensor
  ** Receives:    [worldMap] The world map the sensor will control
  ***/
CORBAImplementations::Sensor::Sensor(WorldMap* worldMap) {
    // Sets the world map
    _worldMap = worldMap;
}


/*** Teams handling functions
  ** Description: Handles the teams
  ** Receives:    [teamNum]  The team number
                  [teamName] The team name
  ** Returns:     Nothing
  ***/
void CORBAImplementations::Sensor::addTeam(Octet teamNum, const char* teamName) {
    // Adds the team
    _worldMap->addTeam(teamNum, QString(teamName));
}
void CORBAImplementations::Sensor::delTeam(Octet teamNum) {
    // Deletes the team
    _worldMap->delTeam(teamNum);
}


/*** Balls handling functions
  ** Description: Handles the balls
  ** Receives:    [ballNum] The ball number
  ** Returns:     Nothing
  ***/
void CORBAImplementations::Sensor::addBall(Octet ballNum) {
    // Adds the ball
    _worldMap->addBall(ballNum);
}

void CORBAImplementations::Sensor::delBall(Octet ballNum) {
    // Deletes the ball
    _worldMap->delBall(ballNum);
}

/*** 'setBallPosition' function
  ** Description: Sets the ball position
  ** Receives:    [ballNum]  The ball number
                  [position] The ball position
  ** Returns:     Nothing
  ***/
void CORBAImplementations::Sensor::setBallPosition(Octet ballNum, const CORBATypes::Position& position) {
    // Sets the position
    _worldMap->setBallPosition(ballNum, Position(position));
}

/*** 'setBallVelocity' function
  ** Description: Sets the ball velocity
  ** Receives:    [ballNum]  The ball number
                  [velocity] The ball velocity
  ** Returns:     Nothing
  ***/
void CORBAImplementations::Sensor::setBallVelocity(Octet ballNum, const CORBATypes::Velocity& velocity) {
    // Sets the velocity
    _worldMap->setBallVelocity(ballNum, Velocity(velocity));
}


/*** Players handling functions
  ** Description: Handles the teams players
  ** Receives:    [teamNum]   The team number
                  [playerNum] The player number
  ** Returns:     Nothing
  ***/
void CORBAImplementations::Sensor::addPlayer(Octet teamNum, Octet playerNum) {
    // Adds the player
    _worldMap->addPlayer(teamNum, playerNum);
}
void CORBAImplementations::Sensor::delPlayer(Octet teamNum, Octet playerNum) {
    // Deletes the player
    _worldMap->delPlayer(teamNum, playerNum);
}

/*** 'setPlayerPosition' function
  ** Description: Sets the player position
  ** Receives:    [teamNum]   The team number
                  [playerNum] The player number
                  [position]  The player position
  ** Returns:     Nothing
  ***/
void CORBAImplementations::Sensor::setPlayerPosition(Octet teamNum, Octet playerNum, const CORBATypes::Position& position) {
    // Sets the position
    _worldMap->setPlayerPosition(teamNum, playerNum, Position(position));
}

/*** 'setPlayerOrientation' function
  ** Description: Sets the player orientation
  ** Receives:    [teamNum]     The team number
                  [playerNum]   The player number
                  [orientation] The player orientation
  ** Returns:     Nothing
  ***/
void CORBAImplementations::Sensor::setPlayerOrientation(Octet teamNum, Octet playerNum, const CORBATypes::Angle& orientation) {
    // Sets the orientation
    _worldMap->setPlayerOrientation(teamNum, playerNum, Angle(orientation));
}

/*** 'setPlayerVelocity' function
  ** Description: Sets the player velocity
  ** Receives:    [teamNum]   The team number
                  [playerNum] The player number
                  [velocity]  The player velocity
  ** Returns:     Nothing
  ***/
void CORBAImplementations::Sensor::setPlayerVelocity(Octet teamNum, Octet playerNum, const CORBATypes::Velocity& velocity) {
    // Sets the velocity
    _worldMap->setPlayerVelocity(teamNum, playerNum, Velocity(velocity));
}

/*** 'setPlayerAngularSpeed' function
  ** Description: Sets the player angular speed
  ** Receives:    [teamNum]      The team number
                  [playerNum]    The player number
                  [angularSpeed] The player angular speed
  ** Returns:     Nothing
  ***/
void CORBAImplementations::Sensor::setPlayerAngularSpeed(Octet teamNum, Octet playerNum, const CORBATypes::AngularSpeed& angularSpeed) {
    // Sets the angular speed
    _worldMap->setPlayerAngularSpeed(teamNum, playerNum, AngularSpeed(angularSpeed));
}


/*** 'setBallPossession' function
  ** Description: Indicates if the player possesses a ball
  ** Receives:    [teamNum]    The team number
                  [playerNum]  The player number
                  [possession] 'true' if the player has the ball, 'false' otherwise
  ** Returns:     Nothing
  ***/
void CORBAImplementations::Sensor::setBallPossession(Octet teamNum, Octet playerNum, bool possession) {
    // Sets the flag
    _worldMap->setBallPossession(teamNum, playerNum, possession);
}


/*** 'fatigue' function
  ** Description: Indicates the player's fatigue
  ** Receives:    [teamNum]    The team number
                  [playerNum]  The player number
                  [fatigue] float value indicating the player fatigue
  ** Returns:     Nothing
  ***/
void CORBAImplementations::Sensor::setFatigue(Octet teamNum, Octet playerNum, float fatigue) {
    // Sets the flag
    _worldMap->setFatigue(teamNum, playerNum, fatigue);
}


/*** Field handling functions
  ** Description: Handles field info
  ***/
void CORBAImplementations::Sensor::setFieldTopRightCorner(const CORBATypes::Position& position) {
    // Sets the position
    _worldMap->setFieldTopRightCorner(Position(position));
}

void CORBAImplementations::Sensor::setFieldTopLeftCorner(const CORBATypes::Position& position) {
    // Sets the position
    _worldMap->setFieldTopLeftCorner(Position(position));
}

void CORBAImplementations::Sensor::setFieldBottomLeftCorner(const CORBATypes::Position& position) {
    // Sets the position
    _worldMap->setFieldBottomLeftCorner(Position(position));
}

void CORBAImplementations::Sensor::setFieldBottomRightCorner(const CORBATypes::Position& position) {
    // Sets the position
    _worldMap->setFieldBottomRightCorner(Position(position));
}

void CORBAImplementations::Sensor::setFieldCenter(const CORBATypes::Position& position) {
    // Sets the position
    _worldMap->setFieldCenter(Position(position));
}

void CORBAImplementations::Sensor::setLeftGoalPosts(const CORBATypes::Position& left, const CORBATypes::Position& right) {
    // Sets the positions
    _worldMap->setLeftGoalPosts(Position(left), Position(right));
}

void CORBAImplementations::Sensor::setRightGoalPosts(const CORBATypes::Position& left, const CORBATypes::Position& right) {
    // Sets the positions
    _worldMap->setRightGoalPosts(Position(left), Position(right));
}

void CORBAImplementations::Sensor::setGoalArea(float length, float width, float roundedRadius) {
    // Sets the goal area
    _worldMap->setGoalArea(length, width, roundedRadius);
}

void CORBAImplementations::Sensor::setGoalDepth(float depth) {
    // Sets the goal depth
    _worldMap->setGoalDepth(depth);
}

void CORBAImplementations::Sensor::setLeftPenaltyMark(const CORBATypes::Position& position) {
    // Sets the position
    _worldMap->setLeftPenaltyMark(Position(position));
}

void CORBAImplementations::Sensor::setRightPenaltyMark(const CORBATypes::Position& position) {
    // Sets the position
    _worldMap->setRightPenaltyMark(Position(position));
}

void CORBAImplementations::Sensor::setFieldCenterRadius(float centerRadius) {
    // Sets the center radius
    _worldMap->setFieldCenterRadius(centerRadius);
}
