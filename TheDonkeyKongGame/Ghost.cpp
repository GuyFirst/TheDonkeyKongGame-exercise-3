#include "Ghost.h"
#include <cstdlib> // std::rand
#include <ctime>   // std::time
#include <iostream>
#include <vector>
#include "gameConfig.h"
#include "typeinfo"
#include "UniqueGhost.h"

void Ghost::move(std::vector<std::unique_ptr<Ghost>>& ghosts, bool isLoad, bool isSave, bool isSilent) {
    draw(map->originalMap[position.getY()][position.getX()], isLoad, isSave, isSilent);
    
        handleCollision(ghosts);
        handleDirectionChange();
   
      
    // Update position 
    if (isOnAir() || isNearBoundry()) {
        m_diff_x = -m_diff_x;
    }

    position.setX(position.getX() + m_diff_x);
    // Draw ghost at the new position
    draw(me, isLoad, isSave, isSilent);
}


void Ghost::handleCollision(std::vector<std::unique_ptr<Ghost>>& ghosts) {
    for (auto& other : ghosts) {
        // Skip checking collision with itself
        if (other.get() == this) {
            continue;
        }

        if (this->isNearOtherGhosts(*other)) {
            this->m_diff_x = -(this->m_diff_x);
            other->m_diff_x = -(other->m_diff_x);
        }
    }
}








