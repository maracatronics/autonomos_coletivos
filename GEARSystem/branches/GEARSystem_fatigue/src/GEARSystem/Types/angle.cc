/*** GEARSystem - Angle implementation
  ** GEAR - Grupo de Estudos Avancados em Robotica
  ** Department of Electrical Engineering, University of Sao Paulo
  ** http://www.sel.eesc.usp.br/gear
  ** This file is part of the GEARSystem project
  ***/


// Includes the class header
#include <GEARSystem/Types/angle.hh>


// Includes math library
#include <cmath>


// Selects namespace
using namespace GEARSystem;


/*** 'toRadians' function
  ** Description: Converts an angle from degrees to radians
  ** Receives:    [angle] The angle that will be converted
  ** Returns:     The angle value in radians
  ***/
float Angle::toRadians(float angle) {
    // Returns the converted value
    return(angle*toRad);
}

/*** 'toDegrees' function
  ** Description: Converts an angle from radians to degrees
  ** Receives:    [angle] The angle that will be converted
  ** Returns:     The angle value in degrees
  ***/
float Angle::toDegrees(const Angle& angle) {
    // Returns the converted value
    return(angle.value()*toDeg);
}

/*** 'toDegrees' function
  ** Description: Converts an angle from radians to degrees
  ** Receives:    [angle] The angle that will be converted
  ** Returns:     The angle value in degrees
  ***/
float Angle::toDegrees(float angle) {
    // Returns the converted value
    return(angle*toDeg);
}


/*** 'difference' function
  ** Description: Calculates the difference of two angles
  ** Receives:    [a] The first angle
                  [b] The second angle
  ** Returns:     The difference of the angles (positive if a > b or negative if a < b)
  ***/
float Angle::difference(const Angle& a, const Angle& b) {
    // Calculates the difference
    float difference = a.value()-b.value();

    // Verifies if the difference is the absolute smallest
    if (difference > Angle::pi) {
        difference -= Angle::twoPi;
    }
    else if (difference < -Angle::pi) {
        difference += Angle::twoPi;
    }

    // Returns the difference
    return(difference);
}


/*** Constructor
  ** Description: Creates an invalid angle
  ** Receives:    Nothing
  ***/
Angle::Angle() {
    setInvalid();
}


/*** Constructor
  ** Description: Creates a valid angle
  ** Receives:    [known] Indicates if the angle is known.
                            If not, 'value' is ignored
                  [theValue] The angle value
  ***/
Angle::Angle(bool known, float theValue) {
    (known == true) ? setValue(theValue) : setUnknown();
}


/*** Constructor
  ** Description: Creates an angle from a CORBA Angle
  ** Recieves:    [position] The CORBA Angle
  ***/
Angle::Angle(const CORBATypes::Angle& angle) {
    // Sets as invalid
    if (!angle.isValid) {
        setInvalid();
    }

    // Sets as unknown
    else if (angle.isUnknown) {
        setUnknown();
    }

    // Sets as known
    else {
        setValue(angle.value);
    }
}


/*** '=' operator
  ** Description: Copies an angle
  ** Receives:    [other] The angle that will be copied
  ** Returns:     This angle
  ***/
Angle& Angle::operator =(const Angle& other) {
    // Valid angle
    if (other.isValid()) {
        // Unknown angle
        if (other.isUnknown()) {
            setUnknown();
        }
        // Known angle
        else {
            setValue(other.value());
        }
    }
    // Invalid angle
    else {
        setInvalid();
    }

    // Returns this angle
    return(*this);
}

/*** '=' operator
  ** Description: Sets the angle value
  ** Receives:    [theValue] The new angle value
  ** Returns:     This angle
  ***/
Angle& Angle::operator =(const float theValue) {
    // Sets the angle value
    setValue(theValue);

    // Returns this angle
    return(*this);
}


/*** 'toCORBA' function
  ** Description: Copies the angle to a CORBA Angle
  ** Receives:    [other] The CORBA Position
  ** Returns:     Nothing
  ***/
void Angle::toCORBA(CORBATypes::Angle* other) const {
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
        other->value     = value();
    }
}


// Set/get functions
float Angle::value() const { return(_value); }
void  Angle::setValue(float theValue) {
    // Sets the angle in the range 0 <= angle < 2*Pi
    _value = fmod(theValue, Angle::twoPi);
    if (_value < 0.0) {
        _value += Angle::twoPi;
    }

    // Sets as a valid known angle
    _valid   = true;
    _unknown = false;
}


// Info functions
bool Angle::isUnknown() const { return(_unknown); }
bool Angle::isValid()   const { return(_valid);   }
void Angle::setInvalid() { _valid = false; }
void Angle::setUnknown() {
    _unknown = true;
    _valid   = true;
}
