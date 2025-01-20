#include <iostream>
#include <Windows.h>
#include "Mario.h"
#include "gameConfig.h"



void Mario::draw(char ch) const
{
    gotoxy(position.getX(), position.getY());
    std::cout << ch;
}

void Mario::move(gameConfig::eKeys key) {
    // Erase Mario from the current position
    draw(map->originalMap[position.getY()][position.getX()]);


    // Check for collision with barrels before moving
    if (checkForCollisions((int)key)) {  return; }

    handleInput(key);

    executeStateAction();

    handleFalling();
    
    // Check for collision with barrels and ghosts after moving
    if (checkForCollisions((int)key)) 
        return;

    // Determine the character to draw
    char marioChar;
    if (map->currentMap[position.getY()][position.getX()] == 'H') { marioChar = '#'; } // Mario is climbing 

    else if (isWithPatish) {  marioChar = 'P'; }// Mario has the hammer
    
    else { marioChar = '@'; }// Default Mario

    // Draw Mario at the new position
    draw(marioChar);
 
}


bool Mario::checkForCollisions(int key) {
    if (m_isNearExplosion) {
        lives--;
        Sleep((int)gameConfig::Sleep::SCREEN_SLEEP);
        resetMario();
        return true;
    }
    if ((isBarrelHere() || isGhostHere()) && !(isWithPatish && key == 'p')) {
        lives--;
        Sleep((int)gameConfig::Sleep::SCREEN_SLEEP);
        resetMario();
        return true;
    }
    return false;
 
}

void Mario::handleInput(gameConfig::eKeys key) {
    if (isFalling) {
        return;
    }

    if (key != gameConfig::eKeys::NONE) {
        switch (key) {
        case gameConfig::eKeys::LEFT:
            setState(State::WALKING, (int)gameConfig::Direction::NEGATIVE, 0);
            break;
        case gameConfig::eKeys::RIGHT:
            setState(State::WALKING, (int)gameConfig::Direction::POSITIVE, 0);
            break;
        case gameConfig::eKeys::UP:
            handleUpKey();
            break;
        case gameConfig::eKeys::DOWN:
            handleDownKey();
            break;
        case gameConfig::eKeys::STAY:
            if (isOnFloor()) {
                setState(State::STANDING, 0, 0);
            }
            return;
        }
    }
}


void Mario::handleUpKey() {
    if (isUnderFloor() && !isOnLadder()) {
        return;
    }
    else if (isUnderLadder()) {
        state = State::CLIMBING_UP;
    }
    else if (isOnFloor()) {
        state = State::JUMPING;
    }
}

void Mario::handleDownKey() {
    if (isOnLadder()) {
        state = State::CLIMBING_DOWN;
    }
    if (!isOnFloor()) {
        m_diff_y = (int)gameConfig::Direction::POSITIVE;
    }
}



void Mario::setState(State newState, int diffX, int diffY) {
    if (state == State::FALLING) {
        m_diff_x = 0; 
    }
    else {
        m_diff_x = diffX;
    }
    m_diff_y = diffY;
    state = newState;
}


void Mario::executeStateAction() {
    switch (state) {
    case State::JUMPING:
        jump();
        break;
    case State::CLIMBING_UP:
        climb();
        break;
    case State::CLIMBING_DOWN:
        downLadder();
        break;
    case State::WALKING:
    case State::FALLING:
        walk();  // Handle both WALKING and FALLING states by calling walk()
        break;
    case State::STANDING:
        if (!isOnFloor())
            state = State::FALLING;
        break;
    }
}


void Mario::walk() {
    if (isNearBoundry()) {
        m_diff_x = 0; // Stop horizontal movement
        if (isOnFloor()) {
            state = State::STANDING; // Reset to STANDING if on the floor
        }
    }
    position.setX(position.getX() + m_diff_x);
    position.setY(position.getY() + m_diff_y);
}


void Mario::handleFalling() {
    if (!isOnFloor()) {
        
        m_diff_y = 1; 
        m_countHeight++;
        isFalling = true; 
    }
    else {
        if (isFalling && m_diff_x == 0)
            state = State::STANDING;
        m_diff_y = 0;
        checkFallHeight(); 
        m_countHeight = 0;
        isFalling = false;
    }
}


void Mario::jump() {
    // Add horizontal movement during the jump if not near a wall
    if (!isNearBoundry()) {
        position.setX(position.getX() + m_diff_x);
    }
    else {
        m_diff_x = 0; // Stop horizontal movement if Mario hits a wall
    }

    // Check for collision with ceiling
    if (isCeilingAbove()) {
        handleCeilingCollision();
        return;
    }

    // Jumping upwards phase (initial upward movement)
    if (jumpCounter < 2) {
        m_diff_y = -1; // Mario moves upwards
        position.setY(position.getY() + m_diff_y);
        jumpCounter++; // Track upward motion progress
    }
    // Falling phase (after peak)
    else if (jumpCounter < 2) {
        m_diff_y = 1; // Mario starts falling down
        position.setY(position.getY() + m_diff_y);
        jumpCounter++; // Track downward motion progress
    }

    // After falling, Mario lands and the jump ends
    if (jumpCounter >= 2) {
        state = State::WALKING;  // Switch to walking state
        m_diff_y = 0;            // Reset vertical movement
        jumpCounter = 0;         // Reset jump counter
    }
}




void Mario::handleCeilingCollision() {
    m_diff_y = (int)gameConfig::Direction::POSITIVE; // Begin falling
    position.setY(position.getY() + m_diff_y);

    // Update state to WALKING or STANDING depending on horizontal movement
    if (m_diff_x != 0 && !isNearBoundry()) 
        state = State::WALKING;
    
    else 
        state = State::STANDING;

    jumpCounter = 0; // Reset jump counter
}

void Mario::handleLanding() {
    if (isOnFloor()) {
        // Update state to WALKING or STANDING depending on horizontal movement
        if (m_diff_x != 0 && !isNearBoundry()) {
            state = State::WALKING;
        }
        else {
            state = State::STANDING;
        }
        m_diff_y = 0; // Reset vertical movement
        jumpCounter = 0; // Reset jump counter
    }
}

void Mario::climb() {
    if (isUnderLadder()) {
        m_diff_y = (int)gameConfig::Direction::NEGATIVE;
        position.setY(position.getY() + m_diff_y);
        state = State::CLIMBING_UP;
    }

    // If Mario is done climbing
    if (!isUnderLadder()) {
        state = State::STANDING;
        m_diff_y = 0;
    }
}

void Mario::downLadder() {
    if (isOnLadder()) {
        m_diff_y = (int)gameConfig::Direction::POSITIVE;
        position.setY(position.getY() + m_diff_y);
        state = State::CLIMBING_DOWN;
    }

    // If he isn't on the ladder
    if (!isOnLadder()) {
        state = State::STANDING;
        m_diff_y = 0;
    }
}



void Mario::resetMario() {
    isWithPatish = false;
	position = map->getMarioStartPos();
    m_diff_x = m_diff_y = m_countHeight = m_isNearExplosion = 0;
}



bool Mario::isOnFloor() const            { return map->currentMap[position.getY() + 1][position.getX()] != ' ' && map->currentMap[position.getY() + 1][position.getX()] != 'O' && map->currentMap[position.getY() + 1][position.getX()] != 'x'; }


bool Mario::isUnderFloor() const {
    if (state == State::STANDING) 
        return map->currentMap[position.getY() - 1][position.getX()] != ' ' &&
               map->currentMap[position.getY() - 1][position.getX()] != 'H' &&
               map->currentMap[position.getY() - 1][position.getX()] != 'p';
    else 
        return isUnderFloorWhileMoving(); 
}

bool Mario::isUnderFloorWhileMoving() const {
    if (m_diff_x == (int)gameConfig::Direction::POSITIVE)                                // going right
        return isObstacleAbove(position.getX()) || isObstacleAbove(position.getX() + 1);
    else if (m_diff_x == (int)gameConfig::Direction::NEGATIVE)                           // going left
        return isObstacleAbove(position.getX()) || isObstacleAbove(position.getX() - 1);
    
    return false;
}

bool Mario::isNearWall(int dirX) const {     
    if (dirX == (int)gameConfig::Direction::POSITIVE)
        return position.getX() >= gameConfig::GAME_WIDTH - 2;
    else
		return (position.getX() <= 0);

}

    


