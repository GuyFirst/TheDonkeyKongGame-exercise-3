#include "Ghost.h"
#include <cstdlib> // std::rand
#include <ctime>   // std::time
#include <iostream>
#include <vector>
#include "gameConfig.h"
#include "typeinfo"
#include "UniqueGhost.h"


//ok here me out
// i want all the ghosts to reach the move function.
// 
// but before the handleCollision and handleDirectionChange, ill ask
// if this is a regular ghost.
// a regular ghost will go inside annd unique ghost will not.
// in addition, need to implement some "follow mario" algorithm that only Unique ghost could follow.
// and also climb the ladder...for that i gave the Entity the enum class for States to implement at the unique ghost
// 
//


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








