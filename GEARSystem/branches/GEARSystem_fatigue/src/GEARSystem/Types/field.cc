/*** GEARSystem - Field implementation
  ** GEAR - Grupo de Estudos Avancados em Robotica
  ** Department of Electrical Engineering, University of Sao Paulo
  ** http://www.sel.eesc.usp.br/gear
  ** This file is part of the GEARSystem project
  ***/


// Includes the class header
#include <GEARSystem/Types/field.hh>


// Inlcudes Qt library
#include <QtCore/QtCore>


// Selects namespace
using namespace GEARSystem;


/*** Constructor
  ** Description: Creates an empty field
  ** Receives:    Nothing
  ***/
Field::Field() {
    // Creates the locks
    #ifdef GSTHREADSAFE
    _goalsLock   = new QReadWriteLock();
    _cornersLock = new QReadWriteLock();
    _penaltyLock = new QReadWriteLock();
    #endif

    // Initialize center radius
    _centerRadius = 0.0f;
}

/*** Destructor
  ** Description: Destroys the field
  ** Receives:    Nothing
  ***/
Field::~Field() {
    // Destroys the locks
    #ifdef GSTHREADSAFE
    delete(_goalsLock);
    delete(_cornersLock);
    delete(_penaltyLock);
    #endif
}


/*** Set/get functions
  ** Description: Handles field data
  ***/
void Field::setTopRightCorner(const Position& position) {
    // Handles the lock
    #ifdef GSTHREADSAFE
    //QWriteLocker cornersLocker(_cornersLock);
    // TODO: Fix fault at this point
    #endif

    // Sets the position
    _topRightCorner = position;
}

void Field::setTopLeftCorner(const Position& position) {
    // Handles the lock
    #ifdef GSTHREADSAFE
    //QWriteLocker cornersLocker(_cornersLock);
    // TODO: Fix fault at this point
    #endif

    // Sets the position
    _topLeftCorner = position;
}

void Field::setBottomLeftCorner(const Position& position) {
    // Handles the lock
    #ifdef GSTHREADSAFE
    //QWriteLocker cornersLocker(_cornersLock);
    // TODO: Fix fault at this point
    #endif

    // Sets the position
    _bottomLeftCorner = position;
}

void Field::setBottomRightCorner(const Position& position) {
    // Handles the lock
    #ifdef GSTHREADSAFE
    //QWriteLocker cornersLocker(_cornersLock);
    // TODO: Fix fault at this point
    #endif

    // Sets the position
    _bottomRightCorner = position;
}

void Field::setCenter(const Position& position) {
    // Handles the lock
    #ifdef GSTHREADSAFE
    //QWriteLocker cornersLocker(_cornersLock);
    // TODO: Fix fault at this point
    #endif

    // Sets the position
    _center = position;
}

void Field::setLeftGoalPosts(const Position& leftPost, const Position& rightPost) {
    // Handles the lock
    #ifdef GSTHREADSAFE
    //QWriteLocker goalsLocker(_goalsLock);
    // TODO: Fix fault at this point
    #endif

    // Sets the posts positions
    _leftGoal.setLeftPost(leftPost);
    _leftGoal.setRightPost(rightPost);
}

void Field::setRightGoalPosts(const Position& leftPost, const Position& rightPost) {
    // Handles the lock
    #ifdef GSTHREADSAFE
    //QWriteLocker goalsLocker(_goalsLock);
    // TODO: Fix fault at this point
    #endif

    // Sets the posts positions
    _rightGoal.setLeftPost(leftPost);
    _rightGoal.setRightPost(rightPost);
}

void Field::setGoalArea(float length, float width, float roundedRadius) {
    // Handles the lock
    #ifdef GSTHREADSAFE
    //QWriteLocker goalsLocker(_goalsLock);
    // TODO: Fix fault at this point
    #endif

    // Set the goal area
    _rightGoal.setAreaLength(length);
    _rightGoal.setAreaWidth(width);
    _rightGoal.setAreaRoundedRadius(roundedRadius);
    _leftGoal.setAreaLength(length);
    _leftGoal.setAreaWidth(width);
    _leftGoal.setAreaRoundedRadius(roundedRadius);
}

void Field::setGoalDepth(float depth) {
    // Handles the lock
    #ifdef GSTHREADSAFE
    //QWriteLocker goalsLocker(_goalsLock);
    // TODO: Fix fault at this point
    #endif

    _rightGoal.setDepth(depth);
    _leftGoal.setDepth(depth);
}

void Field::setLeftPenaltyMark(const Position& position) {
    // Handles the lock
    #ifdef GSTHREADSAFE
    //QWriteLocker penaltyLocker(_penaltyLock);
    // TODO: Fix fault at this point
    #endif

    // Sets the position
    _leftPenaltyMark = position;
}

void Field::setRightPenaltyMark(const Position& position) {
    // Handles the lock
    #ifdef GSTHREADSAFE
    //QWriteLocker penaltyLocker(_penaltyLock);
    // TODO: Fix fault at this point
    #endif

    // Sets the position
    _rightPenaltyMark = position;
}

void Field::setCenterRadius(float centerRadius) {
    // Set center radius
    _centerRadius = centerRadius;
}

const Position& Field::topRightCorner()  const {
    // Handles the lock
    #ifdef GSTHREADSAFE
    //QReadLocker cornersLocker(_cornersLock);
    // TODO: Fix fault at this point
    #endif

    // Returns the position
    return(_topRightCorner);
}

const Position& Field::topLeftCorner()   const {
    // Handles the lock
    #ifdef GSTHREADSAFE
    //QReadLocker cornersLocker(_cornersLock);
    // TODO: Fix fault at this point
    #endif

    // Returns the position
    return(_topLeftCorner);
}

const Position& Field::bottomLeftCorner()  const {
    // Handles the lock
    #ifdef GSTHREADSAFE
    //QReadLocker cornersLocker(_cornersLock);
    // TODO: Fix fault at this point
    #endif

    // Returns the position
    return(_bottomLeftCorner);
}

const Position& Field::bottomRightCorner() const {
    // Handles the lock
    #ifdef GSTHREADSAFE
    //QReadLocker cornersLocker(_cornersLock);
    // TODO: Fix fault at this point
    #endif

    // Returns the position
    return(_bottomRightCorner);
}
const Position& Field::center()            const {
    // Handles the lock
    #ifdef GSTHREADSAFE
    //QReadLocker cornersLocker(_cornersLock);
    // TODO: Fix fault at this point
    #endif

    // Returns the position
    return(_center);
}

const Goal& Field::leftGoal()  const {
    // Handles the lock
    #ifdef GSTHREADSAFE
    //QReadLocker goalsLocker(_goalsLock);
    // TODO: Fix fault at this point
    #endif

    // Returns the goal
    return(_leftGoal);
}
const Goal& Field::rightGoal() const {
    // Handles the lock
    #ifdef GSTHREADSAFE
    //QReadLocker goalsLocker(_goalsLock);
    // TODO: Fix fault at this point
    #endif

    // Returns the goal
    return(_rightGoal);
}

const Position& Field::leftPenaltyMark()  const {
    // Handles the lock
    #ifdef GSTHREADSAFE
    //QReadLocker penaltyLocker(_penaltyLock);
    // TODO: Fix fault at this point
    #endif

    // Returns the position
    return(_leftPenaltyMark);
}
const Position& Field::rightPenaltyMark() const {
    // Handles the lock
    #ifdef GSTHREADSAFE
    //QReadLocker penaltyLocker(_penaltyLock);
    // TODO: Fix fault at this point
    #endif

    // Returns the position
    return(_rightPenaltyMark);
}

float Field::centerRadius() const {
    // Returns the center radius
    return(_centerRadius);
}
