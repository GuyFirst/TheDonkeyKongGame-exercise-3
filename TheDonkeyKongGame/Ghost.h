#pragma once
#include <vector>
#include "Point.h"
#include "Map.h"
#include "gameConfig.h"
#include <iostream>
#include "Entity.h"

class Ghost : public Entity {
public:
    Ghost(Map* map, int m_id, Point startingPosition, char me)
        : Entity(startingPosition, me,
            (int)gameConfig::Direction::POSITIVE, (int)gameConfig::Direction::STAY, map), 
        m_id(m_id), 
        startingPosition(startingPosition) {
    } 
    
    virtual ~Ghost() = default;  // Virtual destructor

    void move(std::vector<Ghost*>& Ghosts);
    void reset() { position = startingPosition; };
 

private:
    int m_id; 
    Point startingPosition; 
    void handleCollision(std::vector<Ghost*>& Ghosts);
   virtual void handleDirectionChange() { if (((std::rand() + m_id) % 100) + 1 <= 5 || !isOnFloor()) { m_diff_x = -m_diff_x; }}
   virtual bool isNearOtherGhosts() const { return map->currentMap[position.getY()][position.getX() + m_diff_x] == 'x'; }
   virtual bool isOnAir() const { return map->originalMap[position.getY() + 1][position.getX() + m_diff_x] == ' '; }
};
