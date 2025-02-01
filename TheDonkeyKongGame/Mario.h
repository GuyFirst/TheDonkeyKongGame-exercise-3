#pragma once

#include "Point.h"
#include "Map.h"
#include "gameConfig.h"
#include "Entity.h"

class Mario : public Entity {
public:
    
    Mario(Map* map, Point startingPoint, int lives)
        : Entity(startingPoint, '@',
           (int)gameConfig::Direction::STAY, (int)gameConfig::Direction::STAY, map),
        isWithPatish(false), lives(lives) {
    }  
	State getState() const     { return state; }
    bool isNearPaulina() const { return map->currentMap[position.getY()][position.getX() + m_diff_x] == '$'; }
    char getMapChar() const    { return map->originalMap[position.getY()][position.getX()]; }
    bool isBarrelHere() const  { return map->currentMap[position.getY()][position.getX()] == 'O'; }
    bool isGhostHere() const   { return map->currentMap[position.getY()][position.getX()] == 'x' ||
                                        map->currentMap[position.getY()][position.getX()] == 'X'; }
    bool isNearPatish() const  { return map->originalMap[position.getY()][position.getX()] == 'p'; }
    void setIsNearExplosion(bool isNear) { m_isNearExplosion = isNear; }



private:
    int m_countHeight = (int)gameConfig::Size::ZERO_SIZE;
    int jumpCounter = 0;
    int lives = (int)gameConfig::Size::START_LIVES;
    bool m_isNearExplosion = false;
    bool isWithPatish;
    bool isFalling = false;
    void draw(char ch) const;
    void move(gameConfig::eKeys key = gameConfig::eKeys::NONE, bool isSilent = false);
    void jump();
    void climb();
    void downLadder();
    void resetMario();
    void handleInput(gameConfig::eKeys key);
    void handleUpKey();
    void handleDownKey();
    void setState(State newState, int diffX, int diffY);
    void executeStateAction();
    void walk();
    void handleFalling();
    void handleCeilingCollision();
    void handleLanding();
    bool isNearWall(int dirX) const;
    bool isOnFloor() const;
    bool isUnderFloor() const;
    bool isUnderFloorWhileMoving() const;
    bool checkForCollisions(int key, bool isSilent);
    bool isObstacleAbove(int x) const { return map->currentMap[position.getY() - 1][x] != ' ' && map->currentMap[position.getY() - 1][x] != 'H' && map->currentMap[position.getY() - 1][x] != 'p'; }
    bool isCeilingAbove() const       { return map->currentMap[position.getY() - 1][position.getX()] != ' ' &&
                                               map->currentMap[position.getY() - 1][position.getX()] != 'H' &&
                                               map->currentMap[position.getY() - 1][position.getX()] != 'p';
    }
    void checkFallHeight() { if (m_countHeight >= 5) { lives--; } }

	friend class Game; //the game has the ability to change the mario's state
};

