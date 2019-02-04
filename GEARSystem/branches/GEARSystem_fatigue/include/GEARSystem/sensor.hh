/*** GEARSystem - Sensor class
  ** GEAR - Grupo de Estudos Avancados em Robotica
  ** Department of Electrical Engineering, University of Sao Paulo
  ** http://www.sel.eesc.usp.br/gear
  ** This file is part of the GEARSystem project
  ***/


// Prevents multiple definitions
#ifndef GSSENSOR
#define GSSENSOR


// Includes GEARSystem
#include <GEARSystem/namespace.hh>
#include <GEARSystem/Types/types.hh>
#include <GEARSystem/CORBAImplementations/corbainterfaces.hh>


// Includes Qt library
#include <QtCore/QtCore>


// Selects namespace
using namespace GEARSystem;


/*** 'Sensor' class
  ** Description: This class encapsulates an implementation of the Sensor CORBA interface
  ** Comments:
  ***/
class GEARSystem::Sensor {
    private:
        // CORBA Sensor
        CORBAInterfaces::Sensor_var _corbaSensor;

        // Connection info
        QString _serverAddress;
        uint32  _serverPort;
        bool    _isConnected;


    public:
        /*** Constructor
          ** Description: Creates the sensor
          ** Receives:    Nothing
          ***/
        Sensor();


    public:
        /*** 'connect' function
          ** Description: Connects to the server
          ** Receives:    [address] The server address
                          [port]    The server port
          ** Returns:     'true' if the connection was established, 'false' otherwise
          ***/
        bool connect(const QString& address, uint16 port);

        /*** 'disconnect' function
          ** Description: Disconnects from the server
          ** Receives:    Nothing
          ** Returns:     Nothing
          ***/
        void disconnect();

        /*** 'isConnected' function
          ** Description: Verifies if the sensor is connected to the server
          ** Receives:    Nothing
          ** Returns:     'true' if the connection was established, 'false' otherwise
          ***/
        bool isConnected() const;


    public:
        /*** Teams handling functions
          ** Description: Handles the teams
          ** Receives:    [teamNum]  The team number
                          [teamName] The team name
          ** Returns:     Nothing
          ***/
        void addTeam(uint8 teamNum, const QString& teamName);
        void delTeam(uint8 teamNum);


    public:
        /*** Balls handling functions
          ** Description: Handles the balls
          ** Receives:    [ballNum] The ball number
          ** Returns:     Nothing
          ***/
        void addBall(uint8 ballNum);
        void delBall(uint8 ballNum);

        /*** 'setBallPosition' function
          ** Description: Sets the ball position
          ** Receives:    [ballNum]  The ball number
                          [position] The ball position
          ** Returns:     Nothing
          ***/
        void setBallPosition(uint8 ballNum, const Position& position);

        /*** 'setBallVelocity' function
          ** Description: Sets the ball velocity
          ** Receives:    [ballNum]  The ball number
                          [velocity] The ball velocity
          ** Returns:     Nothing
          ***/
        void setBallVelocity(uint8 ballNum, const Velocity& velocity);


    public:
        /*** Players handling functions
          ** Description: Handles the teams players
          ** Receives:    [teamNum]   The team number
                          [playerNum] The player number
          ** Returns:     Nothing
          ***/
        void addPlayer(uint8 teamNum, uint8 playerNum);
        void delPlayer(uint8 teamNum, uint8 playerNum);

        /*** 'setPlayerPosition' function
          ** Description: Sets the player position
          ** Receives:    [teamNum]   The team number
                          [playerNum] The player number
                          [position]  The player position
          ** Returns:     Nothing
          ***/
        void setPlayerPosition(uint8 teamNum, uint8 playerNum, const Position& position);

        /*** 'setPlayerOrientation' function
          ** Description: Sets the player orientation
          ** Receives:    [teamNum]     The team number
                          [playerNum]   The player number
                          [orientation] The player orientation
          ** Returns:     Nothing
          ***/
        void setPlayerOrientation(uint8 teamNum, uint8 playerNum, const Angle& orientation);

        /*** 'setPlayerVelocity' function
          ** Description: Sets the player velocity
          ** Receives:    [teamNum]   The team number
                          [playerNum] The player number
                          [velocity]  The player velocity
          ** Returns:     Nothing
          ***/
        void setPlayerVelocity(uint8 teamNum, uint8 playerNum, const Velocity& velocity);

        /*** 'setPlayerAngularSpeed' function
          ** Description: Sets the player angular speed
          ** Receives:    [teamNum]      The team number
                          [playerNum]    The player number
                          [angularSpeed] The player angular speed
          ** Returns:     Nothing
          ***/
        void setPlayerAngularSpeed(uint8 teamNum, uint8 playerNum, const AngularSpeed& angularSpeed);

    public:
        /*** 'setBallPossession' function
          ** Description: Indicates if the player possesses a ball
          ** Receives:    [teamNum]    The team number
                          [playerNum]  The player number
                          [possession] 'true' if the player has the ball, 'false' otherwise
          ** Returns:     Nothing
          ***/
        void setBallPossession(uint8 teamNum, uint8 playerNum, bool possession);

        /*** 'setFatigue' function
          ** Description: Indicates the player's fatigue
          ** Receives:    [teamNum]    The team number
                          [playerNum]  The player number
                          [fatigue] float value indicating the player fatigue
          ** Returns:     Nothing
          ***/
        void setFatigue(uint8 teamNum, uint8 playerNum, float fatigue);

    public:
        /*** Field handling functions
          ** Description: Handles field info
          ***/
        void setFieldTopRightCorner(const Position& position);
        void setFieldTopLeftCorner(const Position& position);
        void setFieldBottomLeftCorner(const Position& position);
        void setFieldBottomRightCorner(const Position& position);
        void setFieldCenter(const Position& position);

        void setLeftGoalPosts(const Position& leftPost, const Position& rightPost);
        void setRightGoalPosts(const Position& leftPost, const Position& rightPost);

        void setGoalArea(float length, float width, float roundedRadius);
        void setGoalDepth(float depth);

        void setLeftPenaltyMark(const Position& position);
        void setRightPenaltyMark(const Position& position);

        void setFieldCenterRadius(float centerRadius);
};


#endif
