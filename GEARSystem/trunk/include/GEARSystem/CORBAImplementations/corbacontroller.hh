/*** GEARSystem - CORBA Controller class
  ** GEAR - Grupo de Estudos Avancados em Robotica
  ** Department of Electrical Engineering, University of Sao Paulo
  ** http://www.sel.eesc.usp.br/gear
  ** This file is part of the GEARSystem project
  ***/


// Prevents multiple definitions
#ifndef GSCORBACONTROLLER
#define GSCORBACONTROLLER


// Includes GEARSystem
#include <GEARSystem/namespace.hh>
#include <GEARSystem/Types/types.hh>
#include <GEARSystem/commandbus.hh>
#include <GEARSystem/worldmap.hh>
#include <GEARSystem/CORBAImplementations/corbainterfaces.hh>


// Includes omniORB 4
#include <omniORB4/CORBA.h>


// Selects namespace
using namespace GEARSystem;
using CORBA::Boolean;
using CORBA::Float;
using CORBA::Octet;
using CORBA::String_out;


/*** 'Controller' class
  ** Description: This class implements the Controller CORBA interface
  ** Comments:
  ***/
class GEARSystem::CORBAImplementations::Controller : public POA_GEARSystem::CORBAInterfaces::Controller {
    private:
        // World map
        const WorldMap*   _worldMap;
        const GEARSystem::CommandBus* _commandBus;


    public:
        /*** Constructor
          ** Description: Creates the controller
          ** Receives:    [worldMap]   The world map the controller will read from
                          [commandBus] The command bus the controller will write into
          ***/
        Controller(const WorldMap* worldMap, const GEARSystem::CommandBus* commandBus);


    public:
        /*** 'teamName' function
          ** Description: Gets a team name
          ** Receives:    [teamNum]  The team number
                          [teamName] A reference to where the name will be stored
          ** Returns:     Nothing
          ***/
        virtual void teamName(Octet teamNum, String_out teamName);

        /*** 'teamNumber' function
          ** Description: Gets a team name
          ** Receives:    [teamName] The team name
                          [teamNum]  A reference to where the number will be stored
          ** Returns:     Nothing
          ***/
        virtual void teamNumber(const char* teamName, Octet& teamNum);

        /*** 'teams' function
          ** Description: Gets the created teams
          ** Receives:    [teamsStr] A reference to where the stringfied teams list will be stored
                          [nTeams]   A reference to where the number of teams will be stored
                          [hasTeam0] A reference to where the Team #0 flag will be stored
          ** Returns:     Nothing
          ***/
        virtual void teams(String_out teamsStr, Octet& nTeams, Boolean& hasTeam0);


    public:
        /*** 'players' function
          ** Description: Gets the created players
          ** Receives:    [teamNum]    The team number
                          [playersStr] A reference to where the stringfied players list will be stored
                          [nPlayers]   A reference to where the number of players will be stored
                          [hasPlayer0] A reference to where the Player #0 flag will be stored
          ** Returns:     Nothing
          ***/
        virtual void players(Octet teamNum, String_out playersStr, Octet& nPlayers, Boolean& hasPlayer0);


    public:
        /*** 'balls' function
          ** Description: Gets the created balls
          ** Receives:    [ballsStr] A reference to where the stringfied balls list will be stored
                          [nBalls]   A reference to where the number of balls will be stored
                          [hasBall0] A reference to where the Ball #0 flag will be stored
          ** Returns:     Nothing
          ***/
        virtual void balls(String_out ballsStr, Octet& nBalls, Boolean& hasBall0);

        /*** 'ballPosition' function
          ** Description: Gets the ball position
          ** Receives:    [ballNum]  The ball number
                          [position] The ball position
          ** Returns:     Nothing
          ***/
        virtual void ballPosition(Octet ballNum, CORBATypes::Position& position);

        /*** 'ballVelocity' function
          ** Description: Gets the ball velocity
          ** Receives:    [ballNum]  The ball number
                          [velocity] The ball velocity
          ** Returns:     Nothing
          ***/
        virtual void ballVelocity(Octet ballNum, CORBATypes::Velocity& velocity);


    public:
        /*** 'playerPosition' function
          ** Description: Gets the player position
          ** Receives:    [teamNum]   The team number
                          [playerNum] The player number
                          [position]  The player position
          ** Returns:     Nothing
          ***/
        virtual void playerPosition(Octet teamNum, Octet playerNum, CORBATypes::Position& position);

        /*** 'playerOrientation' function
          ** Description: Gets the player orientation
          ** Receives:    [teamNum]     The team number
                          [playerNum]   The player number
                          [orientation] The player orientation
          ** Returns:     Nothing
          ***/
        virtual void playerOrientation(Octet teamNum, Octet playerNum, CORBATypes::Angle& orientation);

        /*** 'playerVelocity' function
          ** Description: Gets the player velocity
          ** Receives:    [teamNum]   The team number
                          [playerNum] The player number
                          [velocity]  The player velocity
          ** Returns:     Nothing
          ***/
        virtual void playerVelocity(Octet teamNum, Octet playerNum, CORBATypes::Velocity& velocity);

        /*** 'playerAngularSpeed' function
          ** Description: Gets the player angular speed
          ** Receives:    [teamNum]      The team number
                          [playerNum]    The player number
                          [angularSpeed] The player angular speed
          ** Returns:     Nothing
          ***/
        virtual void playerAngularSpeed(Octet teamNum, Octet playerNum, CORBATypes::AngularSpeed& angularSpeed);


    public:
        /*** 'ballPossession' function
          ** Description: Indicates if the player possesses a ball
          ** Receives:    [teamNum]    The team number
                          [playerNum]  The player number
                          [possession] 'true' if the player has the ball, 'false' otherwise
          ** Returns:     Nothing
          ***/
        void ballPossession(Octet teamNum, Octet playerNum, bool& possession);


    public:
        /*** 'setSpeed'
          ** Description: Sets a player speed
          ** Receives:    [teamNum]   The team number
                          [playerNum] The team number
                          [x]         The x speed component
                          [y]         The y speed component
                          [theta]     The angular speed
          ** Returns:     Nothing
          ***/
        virtual void setSpeed(Octet teamNum, Octet playerNum, Float x, Float y, Float theta);

        /*** 'kick'
          ** Description: Activates the player kicking device
          ** Receives:    [teamNum]   The team number
                          [playerNum] The team number
                          [power]     The kick power
          ** Returns:     Nothing
          ***/
        virtual void kick(Octet teamNum, Octet playerNum, Float power);

        /*** 'chipKick'
          ** Description: Activates the player chip-kicking device
          ** Receives:    [teamNum]   The team number
                          [playerNum] The team number
                          [power]     The kick power
          ** Returns:     Nothing
          ***/
        virtual void chipKick(Octet teamNum, Octet playerNum, Float power);

        /*** 'kickOnTouch'
          ** Description: Activates the player kicking device when the ball touches it
          ** Receives:    [teamNum]   The team number
                          [playerNum] The team number
                          [enable]    'true' if the player must kick on touch,
                                      'false' otherwise
                          [power]     The kick power
          ** Returns:     Nothing
          ***/
        virtual void kickOnTouch(Octet teamNum, Octet playerNum, Boolean enable, Float power);

        /*** 'chipKickOnTouch'
          ** Description: Activates the player chip-kicking device when the ball touches it
          ** Receives:    [teamNum]   The team number
                          [playerNum] The team number
                          [enable]    'true' if the player must kick on touch,
                                      'false' otherwise
                          [power]     The kick power
          ** Returns:     Nothing
          ***/
        virtual void chipKickOnTouch(Octet teamNum, Octet playerNum, Boolean enable, Float power);

        /*** 'holdBall'
          ** Description: Activates the player ball holding device
          ** Receives:    [teamNum]   The team number
                          [playerNum] The team number
                          [enable]    'true' if the player must hold the ball,
                                      'false' otherwise
          ** Returns:     Nothing
          ***/
        virtual void holdBall(Octet teamNum, Octet playerNum, Boolean enable);


    public:
        /*** Field handling functions
          ** Description: Handles field info
          ***/
        virtual void fieldTopRightCorner(CORBATypes::Position& position);
        virtual void fieldTopLeftCorner(CORBATypes::Position& position);
        virtual void fieldBottomLeftCorner(CORBATypes::Position& position);
        virtual void fieldBottomRightCorner(CORBATypes::Position& position);
        virtual void fieldCenter(CORBATypes::Position& position);

        virtual void leftGoal(CORBATypes::Position& left, CORBATypes::Position& right, CORBA::Float& depth, CORBA::Float& areaLength, CORBA::Float& areaWidth, CORBA::Float& areaRoundedRadius);
        virtual void rightGoal(CORBATypes::Position& left, CORBATypes::Position& right, CORBA::Float& depth, CORBA::Float& areaLength, CORBA::Float& areaWidth, CORBA::Float& areaRoundedRadius);

        virtual void leftPenaltyMark(CORBATypes::Position& position);
        virtual void rightPenaltyMark(CORBATypes::Position& position);

        virtual void fieldCenterRadius(CORBA::Float& centerRadius);
};


#endif
