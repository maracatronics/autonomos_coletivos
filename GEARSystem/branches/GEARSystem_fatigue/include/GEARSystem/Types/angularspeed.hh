/*** GEARSystem - Angular Speed class
  ** GEAR - Grupo de Estudos Avancados em Robotica
  ** Department of Electrical Engineering, University of Sao Paulo
  ** http://www.sel.eesc.usp.br/gear
  ** This file is part of the GEARSystem project
  ***/


// Prevents multiple definitions
#ifndef GSANGULARSPEED
#define GSANGULARSPEED


// Includes GEARSystem
#include <GEARSystem/namespace.hh>
#include <GEARSystem/CORBAImplementations/corbainterfaces.hh>


/*** 'AngularSpeed' class
  ** Description: This class handles an angular speed measured in radians per second
  ** Comments:    This class is reentrant, but it isn't thread-safe
  ***/
class GEARSystem::AngularSpeed {
    private:
        // Angle value
        float _value;

        // Info flags
        bool _unknown;
        bool _valid;


    public:
        /*** Constructor
          ** Description: Creates an invalid speed
          ** Receives:    Nothing
          ***/
        AngularSpeed();

        /*** Constructor
          ** Description: Creates a valid speed
          ** Receives:    [known] Indicates if the speed is known.
                                    If not, 'value' is ignored
                          [value] The speed value
          ***/
        AngularSpeed(bool known, float value);

        /*** Constructor
          ** Description: Creates a angular speed from a CORBA AngularSpeed
          ** Recieves:    [position] The CORBA AngularSpeed
          ***/
        AngularSpeed(const CORBATypes::AngularSpeed& angularSpeed);


    public:
        /*** '=' operator
          ** Description: Copies an angular speed
          ** Receives:    [other] The speed that will be copied
          ** Returns:     This speed
          ***/
        AngularSpeed& operator =(const AngularSpeed& other);

        /*** '=' operator
          ** Description: Sets the speed value
          ** Receives:    [value] The new speed value
          ** Returns:     This angle
          ***/
        AngularSpeed& operator =(const float value);


    public:
        /*** 'toCORBA' function
          ** Description: Copies the angular speed to a CORBA AngularSpeed
          ** Receives:    [other] The CORBA AngularSpeed
          ** Returns:     Nothing
          ***/
        void toCORBA(CORBATypes::AngularSpeed* other) const;


    public:
        /*** 'setValue' function
          ** Description: Sets the speed value
          ** Receives:    [value] The speed value
          ** Returns:     Nothing
          ***/
        void setValue(float value);

        /*** 'value' function
          ** Description: Gets the angular speed value
          ** Receives:    Nothing
          ** Returns:     The speed value
          ***/
        float value() const;


    public:
        /*** 'isUnknown' function
          ** Description: Verifies if the speed is unknown
          ** Receives:    Nothing
          ** Returns:     'false' if the speed value is known, 'true' otherwise
          ***/
        bool isUnknown() const;

        /*** 'isValid' function
          ** Description: Verifies if the speed is valid
          ** Receives:    Nothing
          ** Returns:     'false' if the speed is invalid, 'true' otherwise
          ***/
        bool isValid() const;

        /*** 'setUnknown' function
          ** Description: Sets the speed as unknown
          ** Receives:    Nothing
          ** Returns:     Nothing
          ***/
        void setUnknown();

        /*** 'setInvalid' function
          ** Description: Sets the speed as invalid
          ** Receives:    Nothing
          ** Returns:     Nothing
          ***/
        void setInvalid();
};


#endif
