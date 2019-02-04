/*** GEARSystem - Field class
  ** GEAR - Grupo de Estudos Avancados em Robotica
  ** Department of Electrical Engineering, University of Sao Paulo
  ** http://www.sel.eesc.usp.br/gear
  ** This file is part of the GEARSystem project
  ***/


// Prevents multiple definitions
#ifndef GSFIELD
#define GSFIELD


// Includes GEARSystem
#include <GEARSystem/namespace.hh>
//#include <GEARSystem/Types/types.hh>  // TODO: Fix includes conflict
#include <GEARSystem/Types/position.hh>
#include <GEARSystem/Types/goal.hh>


// Inlcudes Qt library
#include <QtCore/QtCore>


// Selects namespace
using namespace GEARSystem;


/*** 'Field' class
  ** Description: This class handles information about all field elements
  ** Comments:    This class is reentrant and thread-safe
  ***/
class GEARSystem::Field {
    private:
        // Goals info
        Goal _leftGoal;
        Goal _rightGoal;

        // Corners positions
        Position _topRightCorner;
        Position _topLeftCorner;
        Position _bottomLeftCorner;
        Position _bottomRightCorner;
        Position _center;

        // Penalty marks
        Position _leftPenaltyMark;
        Position _rightPenaltyMark;

        // Center radius
        float _centerRadius;

        // Locks
        #ifdef GSTHREADSAFE
        mutable QReadWriteLock* _goalsLock;
        mutable QReadWriteLock* _cornersLock;
        mutable QReadWriteLock* _penaltyLock;
        #endif


    public:
        /*** Constructor
          ** Description: Creates an empty field
          ** Receives:    Nothing
          ***/
        Field();

        /*** Destructor
          ** Description: Destroys the field
          ** Receives:    Nothing
          ***/
        ~Field();


    public:
        /*** Set/get functions
          ** Description: Handles field data
          ***/
        void setTopRightCorner(const Position& position);
        void setTopLeftCorner(const Position& position);
        void setBottomLeftCorner(const Position& position);
        void setBottomRightCorner(const Position& position);
        void setCenter(const Position& position);

        void setLeftGoalPosts(const Position& leftPost, const Position& rightPost);
        void setRightGoalPosts(const Position& leftPost, const Position& rightPost);

        void setGoalArea(float length, float width, float roundedRadius);
        void setGoalDepth(float depth);

        void setLeftPenaltyMark(const Position& position);
        void setRightPenaltyMark(const Position& position);

        void setCenterRadius(float centerRadius);

        const Position& topRightCorner()    const;
        const Position& topLeftCorner()     const;
        const Position& bottomLeftCorner()  const;
        const Position& bottomRightCorner() const;
        const Position& center()            const;

        const Goal& leftGoal()  const;
        const Goal& rightGoal() const;

        const Position& leftPenaltyMark()  const;
        const Position& rightPenaltyMark() const;

        float centerRadius() const;
};


#endif
