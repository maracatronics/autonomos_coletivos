/*** GEARSystem - Velocity implementation
  ** GEAR - Grupo de Estudos Avancados em Robotica
  ** Department of Electrical Engineering, University of Sao Paulo
  ** http://www.sel.eesc.usp.br/gear
  ** This file is part of the GEARSystem project
  ***/


// Includes the class header
#include <GEARSystem/Types/velocity.hh>


// Includes math library
#include <cmath>


// Selects namespace
using namespace GEARSystem;


/*** Constructor
  ** Description: Creates an invalid velocity
  ** Recieves:    Nothing
  ***/
Velocity::Velocity() {
    setInvalid();
}


/*** Constructor
  ** Description: Creates a valid velocity
  ** Recieves:    [known] Indicates if the velocity is known.
                            If not, 'x' and 'y' are ignored
                  [newX]  The x component
                  [newY]  The y component
  ***/
Velocity::Velocity(bool known, float newX, float newY) {
    (known == true) ? setVelocity(newX, newY) : setUnknown();
}


/*** Constructor
  ** Description: Creates a valid velocity
  ** Recieves:    [known]  Indicates if the velocity is known.
                             If not, 'x' and 'y' are ignored
                  [newAbs] The velocity absolute value
                  [newArg] The velocity argument
  ***/
Velocity::Velocity(bool known, float newAbs, const Angle& newArg) {
    (known == true) ? setVelocity(newAbs, newArg) : setUnknown();
}


/*** Constructor
  ** Description: Creates a position from a CORBA Velocity
  ** Recieves:    [velocity] The CORBA Velocity
  ***/
Velocity::Velocity(const CORBATypes::Velocity& velocity) {
    // Sets as invalid
    if (!velocity.isValid) {
        setInvalid();
    }

    // Sets as unknown
    else if (velocity.isUnknown) {
        setUnknown();
    }

    // Sets as known
    else {
        setVelocity(velocity.x, velocity.y);
    }
}


/*** 'toCORBA' function
  ** Description: Copies the velocity to a CORBA Velocity
  ** Receives:    [other] The CORBA Velocity
  ** Returns:     Nothing
  ***/
void Velocity::toCORBA(CORBATypes::Velocity* other) const {
    // Sets as invalid
    if (!isValid()) {
        other->isValid = false;
    }

    // Sets as unknown
    else if (isUnknown()) {
        other->isValid   = true;
        other->isUnknown = true;
    }

    // Sets as known
    else {
        other->isValid   = true;
        other->isUnknown = false;
        other->x         = x();
        other->y         = y();
    }
}


/*** '=' operator
  ** Description: Copies a velocity
  ** Receives:    [other] The velocity that will be copied
  ** Returns:     This velocity
  ***/
Velocity& Velocity::operator =(const Velocity& other) {
    // Valid velocity
    if (other.isValid()) {
        // Unknown velocity
        if (other.isUnknown()) {
            setUnknown();
        }
        // Known velocity
        else {
            setVelocity(other.x(), other.y());
        }
    }
    // Invalid velocity
    else {
        setInvalid();
    }

    // Returns this velocity
    return(*this);
}


// Set/get functions
float Velocity::x() const { return(_x); }
float Velocity::y() const { return(_y); }
float Velocity::abs() const { return(_abs); }
const Angle& Velocity::arg() const { return(_arg); }

void Velocity::setVelocity(float newX, float newY) {
    // Sets the components
    _x = newX;
    _y = newY;

    // Calculates abs and arg
    setPolarComponents();

    // Sets as a valid known velocity
    _valid   = true;
    _unknown = false;
}

void Velocity::setVelocity(float newAbs, const Angle& newArg) {
    // Sets the values
    _abs = newAbs;
    _arg = newArg;

    // Calculates x and y
    setCartesianComponents();

    // Sets as a valid known velocity
    _valid   = true;
    _unknown = false;
}


// Info functions
bool Velocity::isUnknown() const { return(_unknown); }
bool Velocity::isValid()   const { return(_valid);   }
void Velocity::setInvalid() { _valid = false; }
void Velocity::setUnknown() {
    _unknown = true;
    _valid   = true;
}


/*** 'setCartesianComponents' function
  ** Description: Sets the velocity cartesian components (x and y)
  ** Receives:    Nothing
  ** Returns:     Nothing
  ***/
void Velocity::setCartesianComponents() {
    // Sets the components
    _x = _abs*cos(_arg.value());
    _y = _abs*sin(_arg.value());
}

/*** 'setPolarComponents' function
  ** Description: Sets the velocity polar components (abs and arg)
  ** Receives:    Nothing
  ** Returns:     Nothing
  ***/
void Velocity::setPolarComponents() {
    // Sets the components
    _abs = sqrt(pow(_x, 2) + pow(_y, 2));
    _arg = atan2(_y, _x);
}
