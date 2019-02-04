/*** GEARSystem - WorldMap class
  ** GEAR - Grupo de Estudos Avancados em Robotica
  ** Department of Electrical Engineering, University of Sao Paulo
  ** http://www.sel.eesc.usp.br/gear
  ** This file is part of the GEARSystem project
  ***/


// Prevents multiple definitions
#ifndef GSWORLDMAP
#define GSWORLDMAP


// Includes GEARSystem
#include <GEARSystem/namespace.hh>
#include <GEARSystem/Types/types.hh>


// Inlcudes Qt library
#include <QtCore/QtCore>


// Selects namespace
using namespace GEARSystem;


/*** 'WorldMap' class
  ** Description: This class handles info about the game world
  ** Comments:    This class is reentrat and thread-safe
  ***/
class GEARSystem::WorldMap {
    private:
        // Teams info
        uint8 _nTeams;
        QHash<uint8,bool> _validTeams;
        QHash<uint8,Team> _teams;

        // Balls info
        uint8 _nBalls;
        QHash<uint8,bool>      _validBalls;
        QHash<uint8,Position*> _ballsPositions;
        QHash<uint8,Velocity*> _ballsVelocities;

        // Invalid types
        Angle        _invalidAngle;
        AngularSpeed _invalidAngularSpeed;
        Position     _invalidPosition;
        Velocity     _invalidVelocity;
        QString      _invalidName;
        static const uint8 _invalidNumber = -1;

        // Field info
        Field _field;

        // Locks
        //#ifdef GSTHREADSAFE
        mutable QReadWriteLock* _ballsLock;
        mutable QReadWriteLock* _teamsLock;
        //#endif


    public:
        /*** Constructor
          ** Description: Creates the world map
          ** Receives:    Nothing
          ***/
        WorldMap();
        ~WorldMap();


    public:
        /*** Teams handling functions
          ** Description: Handles the teams
          ** Receives:    [teamNum]  The team number
                          [teamName] The team name
          ** Returns:     Nothing
          ***/
        void addTeam(uint8 teamNum, const QString& teamName);
        void delTeam(uint8 teamNum);
        QList<uint8> teams() const;

        /*** 'teamName'
          ** Description: Gets the team name
          ** Receives:    [teamNum] The team number
          ** Returns:     The team name
          ***/
        const QString teamName(uint8 teamNum) const;

        /*** 'teamNumber'
          ** Description: Gets the team number
          ** Receives:    [name] The team name
          ** Returns:     The team number
          ***/
         uint8 teamNumber(const QString& name) const;


    public:
        /*** Balls handling functions
          ** Description: Handles the balls
          ** Receives:    [ballNum] The ball number
          ** Returns:     Nothing
          ***/
        void addBall(uint8 ballNum);
        void delBall(uint8 ballNum);
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
                          [position] The ball velocity
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
        QList<uint8> players(uint8 teamNum) const;

        /*** Gets functions
          ** Description: Gets the player pose, velocity and angular speed
          ** Receives:    [teamNum]   The team number
                          [playerNum] The player number
          ** Returns:     The player position, orientation, velocity or angular speed
          ***/
        const Position&     playerPosition(uint8 teamNum, uint8 playerNum)     const;
        const Angle&        playerOrientation(uint8 teamNum, uint8 playerNum)  const;
        const Velocity&     playerVelocity(uint8 teamNum, uint8 playerNum)     const;
        const AngularSpeed& playerAngularSpeed(uint8 teamNum, uint8 playerNum) const;
        bool                ballPossession(uint8 teamNum, uint8 playerNum)     const;

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

        /*** 'setBallPossession' function
          ** Description: Indicates if the player possesses a ball
          ** Receives:    [teamNum]    The team number
                          [playerNum]  The player number
                          [possession] 'true' if the player has the ball, 'false' otherwise
          ** Returns:     Nothing
          ***/
        void setBallPossession(uint8 teamNum, uint8 playerNum, bool possession);


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

        void setFieldCenterRadius(float fieldCenterRadius);

        const Position& fieldTopRightCorner()    const;
        const Position& fieldTopLeftCorner()     const;
        const Position& fieldBottomLeftCorner()  const;
        const Position& fieldBottomRightCorner() const;
        const Position& fieldCenter()            const;

        const Goal& leftGoal()  const;
        const Goal& rightGoal() const;

        const Position& leftPenaltyMark()  const;
        const Position& rightPenaltyMark() const;

        float fieldCenterRadius() const;
};


#endif
