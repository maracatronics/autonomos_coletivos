/*** GEARSystem - Actuator class
  ** GEAR - Grupo de Estudos Avancados em Robotica
  ** Department of Electrical Engineering, University of Sao Paulo
  ** http://www.sel.eesc.usp.br/gear
  ** This file is part of the GEARSystem project
  ***/


// Prevents multiple definitions
#ifndef GSACTUATOR
#define GSACTUATOR


// Includes GEARSystem
#include <GEARSystem/namespace.hh>
#include <GEARSystem/Types/types.hh>
#include <GEARSystem/CORBAImplementations/corbaactuator.hh>
#include <GEARSystem/CORBAImplementations/corbainterfaces.hh>


// Includes Qt library
#include <QtCore/QtCore>

// Includes omniORB 4
#include <omniORB4/CORBA.h>


// Selects namespace
using namespace GEARSystem;


/*** 'Actuator' abstract class
  ** Description: This class encapsulates an implementation of the Actuator CORBA interface
                  and must be inherited when implementing an actuator
  ** Comments:
  ***/
class GEARSystem::Actuator {
    protected:
        // CORBA Actuator
        CORBAImplementations::Actuator* _corbaActuator;
        CORBAInterfaces::CommandBus_var _corbaCommandBus;
        QString _name;

        // CORBA objects
        CORBA::ORB_var               _orb;
        PortableServer::POA_var      _poa;
        CosNaming::NamingContext_var _nameService;

        // Connection info
        QString _serverAddress;
        uint32  _serverPort;
        bool    _isConnected;


    public:
        /*** Constructor
          ** Description: Creates the actuator
          ** Receives:    [name] The actuator name
          ***/
        Actuator(const QString& name);

        /*** Destructor
          ** Description: Destroys the actuator
          ** Receives:    Nothing
          ***/
        ~Actuator();


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
          ** Description: Verifies if the actuator is connected to the server
          ** Receives:    Nothing
          ** Returns:     'true' if the connection was established, 'false' otherwise
          ***/
        bool isConnected() const;


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
        virtual void setSpeed(uint8 teamNum, uint8 playerNum, float x, float y, float theta) = 0;

        /*** 'kick'
          ** Description: Activates the player kicking device
          ** Receives:    [teamNum]   The team number
                          [playerNum] The team number
                          [power]     The kick power
          ** Returns:     Nothing
          ***/
        virtual void kick(uint8 teamNum, uint8 playerNum, float power) = 0;

        /*** 'chipKick'
          ** Description: Activates the player chip-kicking device
          ** Receives:    [teamNum]   The team number
                          [playerNum] The team number
                          [power]     The kick power
          ** Returns:     Nothing
          ***/
        virtual void chipKick(uint8 teamNum, uint8 playerNum, float power) = 0;

        /*** 'kickOnTouch'
          ** Description: Activates the player kicking device when the ball touches it
          ** Receives:    [teamNum]   The team number
                          [playerNum] The team number
                          [enable]    'true' if the player must kick on touch,
                                      'false' otherwise
                          [power]     The kick power
          ** Returns:     Nothing
          ***/
        virtual void kickOnTouch(uint8 teamNum, uint8 playerNum, bool enable, float power) = 0;

        /*** 'chipKickOnTouch'
          ** Description: Activates the player chip-kicking device when the ball touches it
          ** Receives:    [teamNum]   The team number
                          [playerNum] The team number
                          [enable]    'true' if the player must kick on touch,
                                      'false' otherwise
                          [power]     The kick power
          ** Returns:     Nothing
          ***/
        virtual void chipKickOnTouch(uint8 teamNum, uint8 playerNum, bool enable, float power) = 0;

        /*** 'holdBall'
          ** Description: Activates the player ball holding device
          ** Receives:    [teamNum]   The team number
                          [playerNum] The team number
                          [enable]    'true' if the player must hold the ball,
                                      'false' otherwise
          ** Returns:     Nothing
          ***/
        virtual void holdBall(uint8 teamNum, uint8 playerNum, bool enable) = 0;


    private:
        /*** 'bindToServer' function
          ** Description: Binds the actuator at the name service
          ** Receives:    Nothing
          ** Returns:     'true' if everything went OK, 'false' otherwise
          ***/
        bool bindToServer();

        /*** 'getCommandBus' function
          ** Description: Connects to the remote command bus
          ** Receives:    [address] The server address
                          [port]    The server port
          ** Returns:     'true' if everything went OK, 'false' otherwise
          ***/
        bool getCommandBus(const QString& address, uint16 port);
};


#endif
