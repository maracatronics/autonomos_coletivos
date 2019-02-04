/*** GEARSystem - Goal implementation
  ** GEAR - Grupo de Estudos Avancados em Robotica
  ** Department of Electrical Engineering, University of Sao Paulo
  ** http://www.sel.eesc.usp.br/gear
  ** This file is part of the GEARSystem project
  ***/


// Includes the class header
#include <GEARSystem/Types/goal.hh>


// Selects namespace
using namespace GEARSystem;


/*** Constructor
  ** Description: Creates an invalid goal
  ** Receives:    Nothing
  ***/
Goal::Goal() {
    // Sets the posts positions as unknown
    _leftPost.setUnknown();
    _rightPost.setUnknown();

    // Initialize other infos
    _depth = 0.0f;
    _areaLength = 0.0f;
    _areaWidth = 0.0f;
    _areaRoundedRadius = 0.0f;
}

/*** Constructor
  ** Description: Creates a valid goal
  ** Receives:    [leftPost] The left post position
                  [rightPost] The right post position
                  [depth] The goal depth
                  [areaLength] The goal area length
                  [areaWidth] The goal area width
                  [areaRoundedRadius] The goal area rounded radius
  ***/
Goal::Goal(const Position& left, const Position& right, float depth, float areaLength, float areaWidth, float areaRoundedRadius) {
    // Sets the positions if both values are known
    if (!left.isUnknown() && !right.isUnknown()) {
        _leftPost  = left;
        _rightPost = right;
    }

    // Sets unknown positions otherwise
    else {
        _leftPost.setUnknown();
        _rightPost.setUnknown();
    }

    // Set depth
    _depth = depth;

    // Set goal area
    _areaLength = areaLength;
    _areaWidth = areaWidth;
    _areaRoundedRadius = areaRoundedRadius;
}


/*** Positions handling function
  ** Description: Sets/gets the posts positions
  ***/
void  Goal::setLeftPost(const Position& position) {
    // Sets the position if it's known
    if (!position.isUnknown()) {
        _leftPost = position;
    }

    // Sets unknown positions otherwise
    else {
        _leftPost.setUnknown();
        _rightPost.setUnknown();
    }
}

void  Goal::setRightPost(const Position& position) {
    // Sets the position if it's known
    if (!position.isUnknown()) {
        _rightPost = position;
    }

    // Sets unknown positions otherwise
    else {
        _leftPost.setUnknown();
        _rightPost.setUnknown();
    }
}

const Position& Goal::leftPost()  const { return(_leftPost); }
const Position& Goal::rightPost() const { return(_rightPost); }

/*** Goal depth handling function
  ** Description: Sets/gets the goal depth
  ***/
void Goal::setDepth(float depth) {
    _depth = depth;
}

float Goal::getDepth() const { return _depth; }

/*** Goal area handling function
  ** Description: Sets/gets the goal area information
  ***/
void Goal::setAreaLength(float length) {
    _areaLength = length;
}

void Goal::setAreaWidth(float width) {
    _areaWidth = width;
}

void Goal::setAreaRoundedRadius(float roundedRadius) {
    _areaRoundedRadius = roundedRadius;
}

float Goal::getAreaLength() const { return _areaLength; }
float Goal::getAreaWidth() const { return _areaWidth; }
float Goal::getAreaRoundedRadius() const { return _areaRoundedRadius; }
