/*** GEARSystem - CORBA Sensor class
  ** GEAR - Grupo de Estudos Avancados em Robotica
  ** Department of Electrical Engineering, University of Sao Paulo
  ** http://www.sel.eesc.usp.br/gear
  ** This file is part of the GEARSystem project
  ***/


// Prevents multiple definitions
#ifndef GSCORBASENSOR
#define GSCORBASENSOR


// Includes GEARSystem
#include <GEARSystem/namespace.hh>
#include <GEARSystem/Types/types.hh>
#include <GEARSystem/worldmap.hh>
#include <GEARSystem/CORBAImplementations/corbainterfaces.hh>


// Includes omniORB 4
#include <omniORB4/CORBA.h>


// Selects namespace
using namespace GEARSystem;
using CORBA::Boolean;
using CORBA::Float;
using CORBA::Octet;


/*** 'Sensor' class
  ** Description: This class implements the Sensor CORBA interface
  ** Comments:
  ***/
class GEARSystem::CORBAImplementations::Sensor : public POA_GEARSystem::CORBAInterfaces::Sensor {
    private:
        // World map
        WorldMap* _worldMap;


    public:
        /*** Constructor
          ** Description: Creates the sensor
          ** Receives:    [worldMap] The world map the sensor will control
          ***/
        Sensor(WorldMap* worldMap);


    public:
        /*** Teams handling functions
          ** Description: Handles the teams
          ** Receives:    [teamNum]  The team number
                          [teamName] The team name
          ** Returns:     Nothing
          ***/
        virtual void addTeam(Octet teamNum, const char* teamName);
        virtual void delTeam(Octet teamNum);


    public:
        /*** Balls handling functions
          ** Description: Handles the balls
          ** Receives:    [ballNum] The ball number
          ** Returns:     Nothing
          ***/
        virtual void addBall(Octet ballNum);
        virtual void delBall(Octet ballNum);

        /*** 'setBallPosition' function
          ** Description: Sets the ball position
          ** Receives:    [ballNum]  The ball number
                          [position] The ball position
          ** Returns:     Nothing
          ***/
        virtual void setBallPosition(Octet ballNum, const CORBATypes::Position& position);

        /*** 'setBallVelocity' function
          ** Description: Sets the ball velocity
          ** Receives:    [ballNum]  The ball number
                          [velocity] The ball velocity
          ** Returns:     Nothing
          ***/
        virtual void setBallVelocity(Octet ballNum, const CORBATypes::Velocity& velocity);


    public:
        /*** Players handling functions
          ** Description: Handles the teams players
          ** Receives:    [teamNum]   The team number
                          [playerNum] The player number
          ** Returns:     Nothing
          ***/
        virtual void addPlayer(Octet teamNum, Octet playerNum);
        virtual void delPlayer(Octet teamNum, Octet playerNum);

        /*** 'setPlayerPosition' function
          ** Description: Sets the player position
          ** Receives:    [teamNum]   The team number
                          [playerNum] The player number
                          [position]  The player position
          ** Returns:     Nothing
          ***/
        virtual void setPlayerPosition(Octet teamNum, Octet playerNum, const CORBATypes::Position& position);

        /*** 'setPlayerOrientation' function
          ** Description: Sets the player orientation
          ** Receives:    [teamNum]     The team number
                          [playerNum]   The player number
                          [orientation] The player orientation
          ** Returns:     Nothing
          ***/
        virtual void setPlayerOrientation(Octet teamNum, Octet playerNum, const CORBATypes::Angle& orientation);

        /*** 'setPlayerVelocity' function
          ** Description: Sets the player velocity
          ** Receives:    [teamNum]   The team number
                          [playerNum] The player number
                          [velocity]  The player velocity
          ** Returns:     Nothing
          ***/
        virtual void setPlayerVelocity(Octet teamNum, Octet playerNum, const CORBATypes::Velocity& velocity);

        /*** 'setPlayerAngularSpeed' function
          ** Description: Sets the player angular speed
          ** Receives:    [teamNum]      The team number
                          [playerNum]    The player number
                          [angularSpeed] The player angular speed
          ** Returns:     Nothing
          ***/
        virtual void setPlayerAngularSpeed(Octet teamNum, Octet playerNum, const CORBATypes::AngularSpeed& angularSpeed);


    public:
        /*** 'setBallPossession' function
          ** Description: Indicates if the player possesses a ball
          ** Receives:    [teamNum]    The team number
                          [playerNum]  The player number
                          [possession] 'true' if the player has the ball, 'false' otherwise
          ** Returns:     Nothing
          ***/
        void setBallPossession(Octet teamNum, Octet playerNum, bool possession);


    public:
        /*** Field handling functions
          ** Description: Handles field info
          ***/
        virtual void setFieldTopRightCorner(const CORBATypes::Position& position);
        virtual void setFieldTopLeftCorner(const CORBATypes::Position& position);
        virtual void setFieldBottomLeftCorner(const CORBATypes::Position& position);
        virtual void setFieldBottomRightCorner(const CORBATypes::Position& position);
        virtual void setFieldCenter(const CORBATypes::Position& position);

        virtual void setLeftGoalPosts(const CORBATypes::Position& left, const CORBATypes::Position& right);
        virtual void setRightGoalPosts(const CORBATypes::Position& left, const CORBATypes::Position& right);

        virtual void setGoalArea(float length, float width, float roundedRadius);
        virtual void setGoalDepth(float depth);

        virtual void setLeftPenaltyMark(const CORBATypes::Position& position);
        virtual void setRightPenaltyMark(const CORBATypes::Position& position);

        virtual void setFieldCenterRadius(float centerRadius);
};


#endif
