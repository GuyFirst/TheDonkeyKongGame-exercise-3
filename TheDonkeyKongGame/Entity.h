#pragma once
#include "Point.h"
#include "gameConfig.h"
#include "Map.h"

class Entity {
protected: 
    enum class State {
        STANDING,
        WALKING,
        JUMPING,
        CLIMBING_UP,
        CLIMBING_DOWN,
        FALLING
    };

    Point startingPosition;
    Point position;
    char me;
    State state = State::WALKING;
    int m_diff_x;
    int m_diff_y;
    Map* map;
   
    virtual void climb();
    virtual void downLadder();
    virtual void followMario();
    bool isNearBoundry() const;
    bool isOnFloor()     const;
    bool isUnderLadder() const {
        return map->currentMap[position.getY() - 1][position.getX()] == 'H' ||
            map->currentMap[position.getY()][position.getX()] == 'H' ||
            map->currentMap[position.getY() + 1][position.getX()] == 'H';
    }

    bool isOnLadder() const {
        return map->currentMap[position.getY() + 2][position.getX()] == 'H' ||
            map->currentMap[position.getY() + 1][position.getX()] == 'H';}

public:
    Entity(Point startingPosition, char me, int m_diff_x, int m_diff_y, Map* map)
        : startingPosition(startingPosition), position(startingPosition), me(me), m_diff_x(m_diff_x), m_diff_y(m_diff_y), map(map) {}

    virtual ~Entity() = default;
    virtual void draw(char ch, bool isLoad, bool isSave, bool isSilent) const;
    
    Point getPoint() const { return position; }
    int getX() const { return position.getX(); }
    int getY() const { return position.getY(); }
    Map* getMap() const { return map; }
};
