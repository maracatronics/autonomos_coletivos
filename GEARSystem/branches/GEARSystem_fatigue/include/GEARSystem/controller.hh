/*** GEARSystem - Controller class
  ** GEAR - Grupo de Estudos Avancados em Robotica
  ** Department of Electrical Engineering, University of Sao Paulo
  ** http://www.sel.eesc.usp.br/gear
  ** This file is part of the GEARSystem project
  ***/


// Prevents multiple definitions
#ifndef GSCONTROLLER
#define GSCONTROLLER


// Includes GEARSystem
#include <GEARSystem/namespace.hh>
#include <GEARSystem/Types/types.hh>
#include <GEARSystem/CORBAImplementations/corbainterfaces.hh>


// Includes Qt library
#include <QtCore/QtCore>


// Selects namespace
using namespace GEARSystem;


/*** 'Controller' class
  ** Description: This class encapsulates an implementation of the Controller CORBA interface
  ** Comments:
  ***/
class GEARSystem::Controller {
    private:
        // CORBA Controller
        CORBAInterfaces::Controller_var _corbaController;

        // Connection info
        QString _serverAddress;
        uint32  _serverPort;
        bool    _isConnected;

        // Invalid types
        Angle        _invalidAngle;
        Position     _invalidPosition;
        Velocity     _invalidVelocity;
        AngularSpeed _invalidAngularSpeed;
        QString      _invalidName;
        Goal         _invalidGoal;
        static const uint8 _invalidNumber = -1;


    public:
        /*** Constructor
          ** Description: Creates the controller
          ** Receives:    Nothing
          ***/
        Controller();


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
          ** Description: Verifies if the controller is connected to the server
          ** Receives:    Nothing
          ** Returns:     'true' if the connection was established, 'false' otherwise
          ***/
        bool isConnected() const;


    public:
        /*** 'teamName' function
          ** Description: Gets the team name
          ** Receives:    [teamNum] The team number
          ** Returns:     The team name
          ***/
        const QString teamName(uint8 teamNum) const;

        /*** 'teamNumber' function
          ** Description: Gets the team number
          ** Receives:    [name] The team name
          ** Returns:     The team number
          ***/
        uint8 teamNumber(const QString& name) const;

        /*** 'teams' function
          ** Description: Gets the created teams
          ** Receives:    Nothing
          ** Returns:     The teams list
          ***/
        QList<uint8> teams() const;


    public:
        /*** 'players' function
          ** Description: Gets the created players in a team
          ** Receives:    [teamNum] The team number
          ** Returns:     The players list
          ***/
        QList<uint8> players(uint8 teamNum) const;


    public:
        /*** 'balls' function
          ** Description: Gets the created balls
          ** Receives:    Nothing
          ** Returns:     The balls list
          ***/
        QList<uint8> balls() const;

        /*** 'ballPosition' function
          ** Description: Gets the ball position
          ** Receives:    [ballNum] The ball number
          ** Returns:     The ball position
          ***/
        const Position ballPosition(uint8 ballNum) const;

        /*** 'ballVelocity' function
          ** Description: Gets the ball velocity
          ** Receives:    [ballNum] The ball number
          ** Returns:     The ball velocity
          ***/
        const Velocity ballVelocity(uint8 ballNum) const;


    public:
        /*** Gets functions
          ** Description: Gets the player pose
          ** Receives:    [teamNum]   The team number
                          [playerNum] The player number
          ** Returns:     The player position, orientation, velocity or angular speed
          ***/
        const Position     playerPosition(uint8 teamNum, uint8 playerNum)     const;
        const Angle        playerOrientation(uint8 teamNum, uint8 playerNum)  const;
        const Velocity     playerVelocity(uint8 teamNum, uint8 playerNum)     const;
        const AngularSpeed playerAngularSpeed(uint8 teamNum, uint8 playerNum) const;


    public:
        /*** 'ballPossession' function
          ** Description: Indicates if the player possesses a ball
          ** Receives:    [teamNum]   The team number
                          [playerNum] The player number
          ** Returns:     'true' if the player has the ball, 'false' otherwise
          ***/
        bool ballPossession(uint8 teamNum, uint8 playerNum);

        /*** 'fatigue' function
          ** Description: Indicates the player's fatigue
          ** Receives:    [teamNum]    The team number
                          [playerNum]  The player number
          ** Returns:     float value indicating the player fatigue
          ***/
        float fatigue(uint8 teamNum, uint8 playerNum);

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
        void setSpeed(uint8 teamNum, uint8 playerNum, float x, float y, float theta);

        /*** 'kick'
          ** Description: Activates the player kicking device
          ** Receives:    [teamNum]   The team number
                          [playerNum] The team number
                          [power]     The kick power
          ** Returns:     Nothing
          ***/
        void kick(uint8 teamNum, uint8 playerNum, float power);

        /*** 'chipKick'
          ** Description: Activates the player chip-kicking device
          ** Receives:    [teamNum]   The team number
                          [playerNum] The team number
                          [power]     The kick power
          ** Returns:     Nothing
          ***/
        void chipKick(uint8 teamNum, uint8 playerNum, float power);

        /*** 'kickOnTouch'
          ** Description: Activates the player kicking device when the ball touches it
          ** Receives:    [teamNum]   The team number
                          [playerNum] The team number
                          [enable]    'true' if the player must kick on touch,
                                      'false' otherwise
                          [power]     The kick power
          ** Returns:     Nothing
          ***/
        void kickOnTouch(uint8 teamNum, uint8 playerNum, bool enable, float power);

        /*** 'chipKickOnTouch'
          ** Description: Activates the player chip-kicking device when the ball touches it
          ** Receives:    [teamNum]   The team number
                          [playerNum] The team number
                          [enable]    'true' if the player must kick on touch,
                                      'false' otherwise
                          [power]     The kick power
          ** Returns:     Nothing
          ***/
        void chipKickOnTouch(uint8 teamNum, uint8 playerNum, bool enable, float power);

        /*** 'holdBall'
          ** Description: Activates the player ball holding device
          ** Receives:    [teamNum]   The team number
                          [playerNum] The team number
                          [enable]    'true' if the player must hold the ball,
                                      'false' otherwise
          ** Returns:     Nothing
          ***/
        void holdBall(uint8 teamNum, uint8 playerNum, bool enable);


    public:
        /*** Field handling functions
          ** Description: Handles field info
          ***/
        const Position fieldTopRightCorner()    const;
        const Position fieldTopLeftCorner()     const;
        const Position fieldBottomLeftCorner()  const;
        const Position fieldBottomRightCorner() const;
        const Position fieldCenter()            const;

        const Goal leftGoal()  const;
        const Goal rightGoal() const;

        const Position leftPenaltyMark()  const;
        const Position rightPenaltyMark() const;

        float fieldCenterRadius() const;
};


#endif
