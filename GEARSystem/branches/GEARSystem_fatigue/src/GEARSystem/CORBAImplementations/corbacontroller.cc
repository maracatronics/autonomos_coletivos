/*** GEARSystem - CORBA Controller implementation
  ** GEAR - Grupo de Estudos Avancados em Robotica
  ** Department of Electrical Engineering, University of Sao Paulo
  ** http://www.sel.eesc.usp.br/gear
  ** This file is part of the GEARSystem project
  ***/


// Includes the class header
#include <GEARSystem/CORBAImplementations/corbacontroller.hh>


// Includes omniORB 4
#include <omniORB4/CORBA.h>
#include <iostream>

// Selects namespace
using namespace GEARSystem;
using CORBA::Boolean;
using CORBA::Float;
using CORBA::Octet;
using CORBA::String_out;


/*** Constructor
  ** Description: Creates the controller
  ** Receives:    [worldMap]   The world map the controller will read from
                  [commandBus] The command bus the controller will write into
  ***/
CORBAImplementations::Controller::Controller(const WorldMap* worldMap, const GEARSystem::CommandBus* commandBus) {
    // Sets the controller elements
    _worldMap   = worldMap;
    _commandBus = commandBus;
}


/*** 'teamName' function
  ** Description: Gets a team name
  ** Receives:    [teamNum] The team number
                  [name]    A reference to where the name will be stored
  ** Returns:     Nothing
  ***/
void CORBAImplementations::Controller::teamName(Octet teamNum, String_out name) {
    // Gets the team name
    QString str = _worldMap->teamName(teamNum);

    // Returns it
    name = CORBA::string_dup(str.toStdString().c_str());
}

/*** 'teamNumber' function
  ** Description: Gets a team name
  ** Receives:    [name]    The team name
                  [teamNum] A reference to where the number will be stored
  ** Returns:     Nothing
  ***/
void CORBAImplementations::Controller::teamNumber(const char* name, Octet& teamNum) {
    // Returns the team number
    teamNum = _worldMap->teamNumber(QString(name));
}

/*** 'teams' function
  ** Description: Gets the created teams
  ** Receives:    [teamsStr] A reference to where the stringfied teams list will be stored
                  [nTeams]   A reference to where the number of teams will be stored
                  [hasTeam0] A reference to where the Team #0 flag will be stored
  ** Returns:     Nothing
  ***/
void CORBAImplementations::Controller::teams(String_out teamsStr, Octet& nTeams, Boolean& hasTeam0) {
    // Gets the teams list
    QList<uint8> list(_worldMap->teams());
    QListIterator<uint8> it(list);

    // Stringfies it
    hasTeam0 = false;

    char* str = new char[list.size()+1];
    str[list.size()-1] = '\0';
    str[list.size()]   = '\0';

    uint16 i;
    uint8  number;
    for (i = 0; it.hasNext(); i++) {
        number = it.next();
        if (number != 0) {
            str[i] = number;
        }
        else {
            hasTeam0 = true;
            i--;
        }
    }

    // Returns the stringfied list
    nTeams = list.size();
    teamsStr = CORBA::string_dup(str);
}


/*** 'players' function
  ** Description: Gets the created players
  ** Receives:    [teamNum]    The team number
                  [playersStr] A reference to where the stringfied players list will be stored
                  [nPlayers]   A reference to where the number of players will be stored
                  [hasPlayer0] A reference to where the Player #0 flag will be stored
  ** Returns:     Nothing
  ***/
void CORBAImplementations::Controller::players(Octet teamNum, String_out playersStr, Octet& nPlayers, Boolean& hasPlayer0) {
    // Gets the players list
    QList<uint8> list(_worldMap->players(teamNum));
    QListIterator<uint8> it(list);

    // Stringfies it
    hasPlayer0 = false;

    char* str = new char[list.size()+1];
    str[list.size()-1] = '\0';
    str[list.size()]   = '\0';

    uint16 i;
    uint8  number;
    for (i = 0; it.hasNext(); i++) {
        number = it.next();
        if (number != 0) {
            str[i] = number;
        }
        else {
            hasPlayer0 = true;
            i--;
        }
    }

    // Returns the stringfied list
    nPlayers = list.size();
    playersStr = CORBA::string_dup(str);
}


/*** 'balls' function
  ** Description: Gets the created balls
  ** Receives:    [ballsStr] A reference to where the stringfied balls list will be stored
                  [nBalls]   A reference to where the number of balls will be stored
                  [hasBall0] A reference to where the Ball #0 flag will be stored
  ** Returns:     Nothing
  ***/
void CORBAImplementations::Controller::balls(String_out ballsStr, Octet& nBalls, Boolean& hasBall0) {
    // Gets the balls list
    QList<uint8> list(_worldMap->balls());
    QListIterator<uint8> it(list);

    // Stringfies it
    hasBall0 = false;

    char* str = new char[list.size()+1];
    str[list.size()-1] = '\0';
    str[list.size()]   = '\0';

    uint16 i;
    uint8  number;
    for (i = 0; it.hasNext(); i++) {
        number = it.next();
        if (number != 0) {
            str[i] = number;
        }
        else {
            hasBall0 = true;
            i--;
        }
    }

    // Returns the stringfied list
    nBalls = list.size();
    ballsStr = CORBA::string_dup(str);
}


/*** 'ballPosition' function
  ** Description: Gets the ball position
  ** Receives:    [ballNum]  The ball number
                  [position] The ball position
  ** Returns:     Nothing
  ***/
void CORBAImplementations::Controller::ballPosition(Octet ballNum, CORBATypes::Position& position) {
    // Returns the ball position
    _worldMap->ballPosition(ballNum).toCORBA(&position);
}

/*** 'ballVelocity' function
  ** Description: Gets the ball velocity
  ** Receives:    [ballNum]  The ball number
                  [velocity] The ball velocity
  ** Returns:     Nothing
  ***/
void CORBAImplementations::Controller::ballVelocity(Octet ballNum, CORBATypes::Velocity& velocity) {
    // Returns the ball velocity
    _worldMap->ballVelocity(ballNum).toCORBA(&velocity);
}


/*** 'playerPosition' function
  ** Description: Gets the player position
  ** Receives:    [teamNum]   The team number
                  [playerNum] The player number
                  [position]  The player position
  ** Returns:     Nothing
  ***/
void CORBAImplementations::Controller::playerPosition(Octet teamNum, Octet playerNum, CORBATypes::Position& position){
    // Returns the player position
    _worldMap->playerPosition(teamNum, playerNum).toCORBA(&position);
}

/*** 'playerOrientation' function
  ** Description: Gets the player orientation
  ** Receives:    [teamNum]     The team number
                  [playerNum]   The player number
                  [orientation] The player orientation
  ** Returns:     Nothing
  ***/
void CORBAImplementations::Controller::playerOrientation(Octet teamNum, Octet playerNum, CORBATypes::Angle& orientation) {
    // Returns the player orientation
    _worldMap->playerOrientation(teamNum, playerNum).toCORBA(&orientation);
}

/*** 'playerVelocity' function
  ** Description: Gets the player velocity
  ** Receives:    [teamNum]   The team number
                  [playerNum] The player number
                  [velocity]  The player velocity
  ** Returns:     Nothing
  ***/
void CORBAImplementations::Controller::playerVelocity(Octet teamNum, Octet playerNum, CORBATypes::Velocity& velocity) {
    // Returns the player velocity
    _worldMap->playerVelocity(teamNum, playerNum).toCORBA(&velocity);
}

/*** 'playerAngularSpeed' function
  ** Description: Gets the player angular speed
  ** Receives:    [teamNum]      The team number
                  [playerNum]    The player number
                  [angularSpeed] The player angular speed
  ** Returns:     Nothing
  ***/
void CORBAImplementations::Controller::playerAngularSpeed(Octet teamNum, Octet playerNum, CORBATypes::AngularSpeed& angularSpeed) {
    // Returns the player angular speed
    _worldMap->playerAngularSpeed(teamNum, playerNum).toCORBA(&angularSpeed);
}


/*** 'ballPossession' function
  ** Description: Indicates if the player possesses a ball
  ** Receives:    [teamNum]    The team number
                  [playerNum]  The player number
                  [possession] 'true' if the player has the ball, 'false' otherwise
  ** Returns:     Nothing
  ***/
void CORBAImplementations::Controller::ballPossession(Octet teamNum, Octet playerNum, bool& possession) {
    // Returns the flag
    possession = _worldMap->ballPossession(teamNum, playerNum);
}


/*** 'fatigue' function
  ** Description: Indicates the player's fatigue
  ** Receives:    [teamNum]    The team number
                  [playerNum]  The player number
                  [fatigue] float value indicating the player fatigue
  ** Returns:     Nothing
  ***/
void CORBAImplementations::Controller::fatigue(Octet teamNum, Octet playerNum, float& fatigue) {
    // Returns the flag
    fatigue = _worldMap->fatigue(teamNum, playerNum);
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
void CORBAImplementations::Controller::setSpeed(Octet teamNum, Octet playerNum, Float x, Float y, Float theta) {
    // Sends the command
    _commandBus->setSpeed(teamNum, playerNum, x, y, theta);
}

/*** 'kick'
  ** Description: Activates the player kicking device
  ** Receives:    [teamNum]   The team number
                  [playerNum] The team number
                  [power]     The kick power
  ** Returns:     Nothing
  ***/
void CORBAImplementations::Controller::kick(Octet teamNum, Octet playerNum, Float power) {
    // Sends the command
    _commandBus->kick(teamNum, playerNum, power);
}

/*** 'chipKick'
  ** Description: Activates the player chip-kicking device
  ** Receives:    [teamNum]   The team number
                  [playerNum] The team number
                  [power]     The kick power
  ** Returns:     Nothing
  ***/
void CORBAImplementations::Controller::chipKick(Octet teamNum, Octet playerNum, Float power) {
    // Sends the command
    _commandBus->chipKick(teamNum, playerNum, power);
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
void CORBAImplementations::Controller::kickOnTouch(Octet teamNum, Octet playerNum, Boolean enable, Float power) {
    // Sends the command via the actuator
    _commandBus->kickOnTouch(teamNum, playerNum, enable, power);
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
void CORBAImplementations::Controller::chipKickOnTouch(Octet teamNum, Octet playerNum, Boolean enable, Float power) {
    // Sends the command via the actuator
    _commandBus->chipKickOnTouch(teamNum, playerNum, enable, power);
}

/*** 'holdBall'
  ** Description: Activates the player ball holding device
  ** Receives:    [teamNum]   The team number
                  [playerNum] The team number
                  [enable]    'true' if the player must hold the ball,
                              'false' otherwise
  ** Returns:     Nothing
  ***/
void CORBAImplementations::Controller::holdBall(Octet teamNum, Octet playerNum, Boolean enable) {
    // Sends the command
    _commandBus->holdBall(teamNum, playerNum, enable);
}


/*** Field handling functions
  ** Description: Handles field info
  ***/
void CORBAImplementations::Controller::fieldTopRightCorner(CORBATypes::Position& position) {
    // Returns the corner
    _worldMap->fieldTopRightCorner().toCORBA(&position);
}

void CORBAImplementations::Controller::fieldTopLeftCorner(CORBATypes::Position& position) {
    // Returns the corner
    _worldMap->fieldTopLeftCorner().toCORBA(&position);
}

void CORBAImplementations::Controller::fieldBottomLeftCorner(CORBATypes::Position& position) {
    // Returns the corner
    _worldMap->fieldBottomLeftCorner().toCORBA(&position);
}

void CORBAImplementations::Controller::fieldBottomRightCorner(CORBATypes::Position& position) {
    // Returns the corner
    _worldMap->fieldBottomRightCorner().toCORBA(&position);
}

void CORBAImplementations::Controller::fieldCenter(CORBATypes::Position& position)
{
   // Returns the corner
   _worldMap->fieldCenter().toCORBA(&position);
}

void CORBAImplementations::Controller::leftGoal(CORBATypes::Position &left, CORBATypes::Position &right, CORBA::Float &depth, CORBA::Float &areaLength, CORBA::Float &areaWidth, CORBA::Float &areaRoundedRadius) {
    // Returns the posts
    Goal goal;
    goal = _worldMap->leftGoal();
    goal.leftPost().toCORBA(&left);
    goal.rightPost().toCORBA(&right);
    depth = goal.getDepth();
    areaLength = goal.getAreaLength();
    areaWidth = goal.getAreaWidth();
    areaRoundedRadius = goal.getAreaRoundedRadius();
}

void CORBAImplementations::Controller::rightGoal(CORBATypes::Position &left, CORBATypes::Position &right, CORBA::Float &depth, CORBA::Float &areaLength, CORBA::Float &areaWidth, CORBA::Float &areaRoundedRadius) {
    // Returns the posts
    Goal goal;
    goal = _worldMap->rightGoal();
    goal.leftPost().toCORBA(&left);
    goal.rightPost().toCORBA(&right);
    depth = goal.getDepth();
    areaLength = goal.getAreaLength();
    areaWidth = goal.getAreaWidth();
    areaRoundedRadius = goal.getAreaRoundedRadius();
}

void CORBAImplementations::Controller::leftPenaltyMark(CORBATypes::Position& position) {
    // Returns the mark
    _worldMap->leftPenaltyMark().toCORBA(&position);
}

void CORBAImplementations::Controller::rightPenaltyMark(CORBATypes::Position& position) {
    // Returns the mark
    _worldMap->rightPenaltyMark().toCORBA(&position);
}

void CORBAImplementations::Controller::fieldCenterRadius(CORBA::Float &centerRadius) {
    // Returns field center radius
    centerRadius = _worldMap->fieldCenterRadius();
}
