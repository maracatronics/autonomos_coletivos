/*** GEARSystem - Angular Speed implementation
  ** GEAR - Grupo de Estudos Avancados em Robotica
  ** Department of Electrical Engineering, University of Sao Paulo
  ** http://www.sel.eesc.usp.br/gear
  ** This file is part of the GEARSystem project
  ***/


// Includes the class header
#include <GEARSystem/Types/angularspeed.hh>


// Selects namespace
using namespace GEARSystem;


/*** Constructor
  ** Description: Creates an invalid speed
  ** Receives:    Nothing
  ***/
AngularSpeed::AngularSpeed() {
    setInvalid();
}


/*** Constructor
  ** Description: Creates a valid speed
  ** Receives:    [known] Indicates if the speed is known.
                            If not, 'value' is ignored
                  [theValue] The speed value
  ***/
AngularSpeed::AngularSpeed(bool known, float theValue) {
    (known == true) ? setValue(theValue) : setUnknown();
}


/*** Constructor
  ** Description: Creates a angular speed from a CORBA AngularSpeed
  ** Recieves:    [angularSpeed] The CORBA AngularSpeed
  ***/
AngularSpeed::AngularSpeed(const CORBATypes::AngularSpeed& angularSpeed) {
    // Sets as invalid
    if (!angularSpeed.isValid) {
        setInvalid();
    }

    // Sets as unknown
    else if (angularSpeed.isUnknown) {
        setUnknown();
    }

    // Sets as known
    else {
        setValue(angularSpeed.value);
    }
}


/*** 'toCORBA' function
  ** Description: Copies the angular speed to a CORBA AngularSpeed
  ** Receives:    [other] The CORBA AngularSpeed
  ** Returns:     Nothing
  ***/
void AngularSpeed::toCORBA(CORBATypes::AngularSpeed* other) const {
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


/*** '=' operator
  ** Description: Copies an angular speed
  ** Receives:    [other] The speed that will be copied
  ** Returns:     This speed
  ***/
AngularSpeed& AngularSpeed::operator =(const AngularSpeed& other) {
    // Valid speed
    if (other.isValid()) {
        // Unknown speed
        if (other.isUnknown()) {
            setUnknown();
        }
        // Known speed
        else {
            setValue(other.value());
        }
    }
    // Invalid speed
    else {
        setInvalid();
    }

    // Returns this speed
    return(*this);
}

/*** '=' operator
  ** Description: Sets the speed value
  ** Receives:    [theValue] The new speed value
  ** Returns:     This angle
  ***/
AngularSpeed& AngularSpeed::operator =(const float theValue) {
    // Sets the speed value
    setValue(theValue);

    // Returns this speed
    return(*this);
}


// Set/get functions
float AngularSpeed::value() const { return(_value); }
void  AngularSpeed::setValue(float theValue) {
    // Sets the speed
    _value = theValue;

    // Sets as a valid known speed
    _valid   = true;
    _unknown = false;
}


// Info functions
bool AngularSpeed::isUnknown() const { return(_unknown); }
bool AngularSpeed::isValid()   const { return(_valid);   }
void AngularSpeed::setInvalid() { _valid = false; }
void AngularSpeed::setUnknown() {
    _unknown = true;
    _valid   = true;
}
