/*** GEARSystem - Position class
  ** GEAR - Grupo de Estudos Avancados em Robotica
  ** Department of Electrical Engineering, University of Sao Paulo
  ** http://www.sel.eesc.usp.br/gear
  ** This file is part of the GEARSystem project
  ***/


// Prevents multiple definitions
#ifndef GSPOSITION
#define GSPOSITION


// Includes GEARSystem
#include <GEARSystem/namespace.hh>
#include <GEARSystem/CORBAImplementations/corbainterfaces.hh>


/*** 'Position' class
  ** Description: This class handles a 3D coordinate
  ** Comments:    This class is reentrant, but it isn't thread-safe
  ***/
class GEARSystem::Position {
    private:
        // Position coordinates
        float _x;
        float _y;
        float _z;

        // Info flags
        bool _unknown;
        bool _valid;


    public:
        /*** Constructor
          ** Description: Creates an invalid position
          ** Recieves:    Nothing
          ***/
        Position();

        /*** Constructor
          ** Description: Creates a valid position
          ** Recieves:    [known] Indicates if the position is known.
                                    If not, 'x', 'y' and 'z' are ignored
                          [x]     The x coordinate
                          [y]     The y coordinate
                          [z]     The z coordinate
          ***/
        Position(bool known, float x, float y, float z);

        /*** Constructor
          ** Description: Creates a position from a CORBA Position
          ** Recieves:    [position] The CORBA Position
          ***/
        Position(const CORBATypes::Position& position);


    public:
        /*** '=' operator
          ** Description: Copies a position
          ** Receives:    [other] The position that will be copied
          ** Returns:     This position
          ***/
        Position& operator =(const Position& other);


    public:
        /*** 'toCORBA' function
          ** Description: Copies the position to a CORBA Position
          ** Receives:    [other] The CORBA Position
          ** Returns:     Nothing
          ***/
        void toCORBA(CORBATypes::Position* other) const;


    public:
        /*** 'setPosition' function
          ** Description: Validates the position and sets its coordinates
          ** Receives:    [x] The x coordinate
                          [y] The y coordinate
                          [z] The z coordinate
          ** Returns:     Nothing
          ***/
        void setPosition(float x, float y, float z);

        /*** Get functions
          ** Description: Gets the position coordinates
          ** Receives:    Nothing
          ** Returns:     The wanted coordinate
          ***/
        float x() const;
        float y() const;
        float z() const;


    public:
        /*** 'isUnknown' function
          ** Description: Verifies if the position is unknown
          ** Receives:    Nothing
          ** Returns:     'false' if the position value is known, 'true' otherwise
          ***/
        bool isUnknown() const;

        /*** 'isValid' function
          ** Description: Verifies if the position is valid
          ** Receives:    Nothing
          ** Returns:     'false' if the position is invalid, 'true' otherwise
          ***/
        bool isValid() const;

        /*** 'setUnknown' function
          ** Description: Sets the position as unknown
          ** Receives:    Nothing
          ** Returns:     Nothing
          ***/
        void setUnknown();

        /*** 'setInvalid' function
          ** Description: Sets the position as invalid
          ** Receives:    Nothing
          ** Returns:     Nothing
          ***/
        void setInvalid();
};


#endif
