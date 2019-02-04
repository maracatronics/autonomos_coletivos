/*** GEARSystem - Position implementation
  ** GEAR - Grupo de Estudos Avancados em Robotica
  ** Department of Electrical Engineering, University of Sao Paulo
  ** http://www.sel.eesc.usp.br/gear
  ** This file is part of the GEARSystem project
  ***/


// Includes the class header
#include <GEARSystem/Types/position.hh>


// Selects namespace
using namespace GEARSystem;


/*** Constructor
  ** Description: Creates an invalid position
  ** Recieves:    Nothing
  ***/
Position::Position() {
    setInvalid();
}


/*** Constructor
  ** Description: Creates a valid position
  ** Recieves:    [known] Indicates if the position is known.
                            If not, 'x', 'y' and 'z' are ignored
                  [newX]  The x coordinate
                  [newY]  The y coordinate
                  [newZ]  The z coordinate
  ***/
Position::Position(bool known, float newX, float newY, float newZ) {
    (known == true) ? setPosition(newX, newY, newZ) : setUnknown();
}


/*** Constructor
  ** Description: Creates a position from a CORBA Position
  ** Recieves:    [position] The CORBA Position
  ***/
Position::Position(const CORBATypes::Position& position) {
    // Sets as invalid
    if (!position.isValid) {
        setInvalid();
    }

    // Sets as unknown
    else if (position.isUnknown) {
        setUnknown();
    }

    // Sets as known
    else {
        setPosition(position.x, position.y, position.z);
    }
}


/*** 'toCORBA' function
  ** Description: Copies the position to a CORBA Position
  ** Receives:    [other] The CORBA Position
  ** Returns:     Nothing
  ***/
void Position::toCORBA(CORBATypes::Position* other) const {
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
        other->z         = z();
    }
}


/*** '=' operator
  ** Description: Copies a position
  ** Receives:    [other] The position that will be copied
  ** Returns:     This position
  ***/
Position& Position::operator =(const Position& other) {
    // Valid position
    if (other.isValid()) {
        // Unknown position
        if (other.isUnknown()) {
            setUnknown();
        }
        // Known position
        else {
            setPosition(other.x(), other.y(), other.z());
        }
    }
    // Invalid position
    else {
        setInvalid();
    }

    // Returns this position
    return(*this);
}


// Set/get functions
float Position::x() const { return(_x); }
float Position::y() const { return(_y); }
float Position::z() const { return(_z); }
void  Position::setPosition(float newX, float newY, float newZ) {
    // Sets the coordinates
    _x = newX;
    _y = newY;
    _z = newZ;

    // Sets as a valid known position
    _valid   = true;
    _unknown = false;
}


// Info functions
bool Position::isUnknown() const { return(_unknown); }
bool Position::isValid()   const { return(_valid);   }
void Position::setInvalid() { _valid = false; }
void Position::setUnknown() {
    _unknown = true;
    _valid   = true;
}
