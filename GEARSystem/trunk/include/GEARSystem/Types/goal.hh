/*** GEARSystem - Goal class
  ** GEAR - Grupo de Estudos Avancados em Robotica
  ** Department of Electrical Engineering, University of Sao Paulo
  ** http://www.sel.eesc.usp.br/gear
  ** This file is part of the GEARSystem project
  ***/


// Prevents multiple definitions
#ifndef GSGOAL
#define GSGOAL


// Includes GEARSystem
#include <GEARSystem/namespace.hh>
//#include <GEARSystem/Types/types.hh>  // TODO: Fix includes conflict
#include <GEARSystem/Types/position.hh>


// Selects namespace
using namespace GEARSystem;


/*** 'Goal' class
  ** Description: This class contains information about the goal position
  ** Comments:    This class is reentrant, but it isn't thread-safe
  ***/
class GEARSystem::Goal {
    private:
        // Posts positions
        Position _leftPost;
        Position _rightPost;

        // Goal depth
        float _depth;

        // Goal area information
        float _areaLength;
        float _areaWidth;
        float _areaRoundedRadius;


    public:
        /*** Constructor
          ** Description: Creates an invalid goal
          ** Receives:    Nothing
          ***/
        Goal();

        /*** Constructor
          ** Description: Creates a valid goal
          ** Receives:    [leftPost] The left post position
                          [rightPost] The right post position
                          [depth] The goal depth
                          [areaLength] The goal area length
                          [areaWidth] The goal area width
                          [areaRoundedRadius] The goal area rounded radius
          ***/
        Goal(const Position& leftPost, const Position& rightPost, float depth, float areaLength, float areaWidth, float areaRoundedRadius);


    public:
        /*** Positions handling function
          ** Description: Sets/gets the posts positions
          ***/
        void  setLeftPost(const Position& position);
        void  setRightPost(const Position& position);
        const Position& leftPost()  const;
        const Position& rightPost() const;

        /*** Goal depth handling function
          ** Description: Sets/gets the goal depth
          ***/
        void setDepth(float depth);
        float getDepth() const;

        /*** Goal area handling function
          ** Description: Sets/gets the goal area information
          ***/
        void setAreaLength(float length);
        void setAreaWidth(float width);
        void setAreaRoundedRadius(float roundedRadius);
        float getAreaLength() const;
        float getAreaWidth() const;
        float getAreaRoundedRadius() const;
};


#endif
