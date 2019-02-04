/*** GEARSystem - CommandBus class
  ** GEAR - Grupo de Estudos Avancados em Robotica
  ** Department of Electrical Engineering, University of Sao Paulo
  ** http://www.sel.eesc.usp.br/gear
  ** This file is part of the GEARSystem project
  ***/


// Prevents multiple definitions
#ifndef GSCOMMANDBUS
#define GSCOMMANDBUS


// Includes GEARSystem
#include <GEARSystem/namespace.hh>
#include <GEARSystem/Types/types.hh>
#include <GEARSystem/CORBAImplementations/corbainterfaces.hh>


// Inlcudes Qt library
#include <QtCore/QtCore>


// Selects namespace
using namespace GEARSystem;


/*** 'CommandBus' class
  ** Description: This class sends commands to actuators
  ** Comments:    This class is reentrat and thread-safe
  ***/
class GEARSystem::CommandBus {
    private:
        // Actuators info
        uint8 _nActuators;
        QHash<QString,bool> _validActuators;
        QHash<QString,CORBAInterfaces::Actuator_var> _actuators;

        // Locks
        #ifdef GSTHREADSAFE
        mutable QReadWriteLock* _actuatorsLock;
        #endif


    public:
        /*** Constructor
          ** Description: Creates the bus
          ** Receives:    Nothing
          ***/
        CommandBus();


    public:
        /*** Actuators handling functions
          ** Description: Handles the actuators
          ** Receives:    [name]    The actuator name
                          [address] The actuator address
          ** Returns:     Nothing
          ***/
        void addActuator(const QString& name, const QString& address);
        void delActuator(const QString& name);


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
        void setSpeed(uint8 teamNum, uint8 playerNum, float x, float y, float theta) const;

        /*** 'kick'
          ** Description: Activates the player kicking device
          ** Receives:    [teamNum]   The team number
                          [playerNum] The team number
                          [power]     The kick power
          ** Returns:     Nothing
          ***/
        void kick(uint8 teamNum, uint8 playerNum, float power) const;

        /*** 'chipKick'
          ** Description: Activates the player chip-kicking device
          ** Receives:    [teamNum]   The team number
                          [playerNum] The team number
                          [power]     The kick power
          ** Returns:     Nothing
          ***/
        void chipKick(uint8 teamNum, uint8 playerNum, float power) const;

        /*** 'kickOnTouch'
          ** Description: Activates the player kicking device when the ball touches it
          ** Receives:    [teamNum]   The team number
                          [playerNum] The team number
                          [enable]    'true' if the player must kick on touch,
                                      'false' otherwise
                          [power]     The kick power
          ** Returns:     Nothing
          ***/
        void kickOnTouch(uint8 teamNum, uint8 playerNum, bool enable, float power) const;

        /*** 'chipKickOnTouch'
          ** Description: Activates the player chip-kicking device when the ball touches it
          ** Receives:    [teamNum]   The team number
                          [playerNum] The team number
                          [enable]    'true' if the player must kick on touch,
                                      'false' otherwise
                          [power]     The kick power
          ** Returns:     Nothing
          ***/
        void chipKickOnTouch(uint8 teamNum, uint8 playerNum, bool enable, float power) const;

        /*** 'holdBall'
          ** Description: Activates the player ball holding device
          ** Receives:    [teamNum]   The team number
                          [playerNum] The team number
                          [enable]    'true' if the player must hold the ball,
                                      'false' otherwise
          ** Returns:     Nothing
          ***/
        void holdBall(uint8 teamNum, uint8 playerNum, bool enable) const;


    private:
        /*** 'connectToActuator'
          ** Description: Connects to a given actuator address
          ** Receives:    [address] The actuator address
          ** Returns:     The connected actuator
          ***/
        CORBAInterfaces::Actuator_var connectToActuator(const QString& address) const;
};


#endif
