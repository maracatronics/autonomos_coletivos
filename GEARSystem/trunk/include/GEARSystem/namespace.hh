/*** GEARSystem - GEARSystem namespace
  ** GEAR - Grupo de Estudos Avancados em Robotica
  ** Department of Electrical Engineering, University of Sao Paulo
  ** http://www.sel.eesc.usp.br/gear
  ** This file is part of the GEARSystem project
  ***/


// Defines the GEARSystem namespace
namespace GEARSystem {
    // Basic classes
    class Angle;
    class AngularSpeed;
    class Field;
    class Goal;
    class Position;
    class Velocity;
    class Team;

    // Game classes
    class WorldMap;
    class CommandBus;

    // System elements
    class Actuator;
    class Controller;
    class Sensor;
    class Server;

    // CORBA Implementations
    namespace CORBAImplementations {
        class Actuator;
        class CommandBus;
        class Controller;
        class Sensor;
    }

    namespace CORBATypes {
        class Angle;
        class AngularSpeed;
        class Position;
        class Velocity;
    }
}
