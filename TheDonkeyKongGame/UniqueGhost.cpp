#include "UniqueGhost.h"

bool UniqueGhost::shouldClimbLadder() {
	return (std::rand() % 2 == 0); // 50% probability to return true
}


void UniqueGhost::move(std::vector<Ghost*>& ghosts) {
    draw(map->originalMap[position.getY()][position.getX()]);

      // Check if the ghost is at a ladder and should climb
    if (state == State::CLIMBING_UP || state == State::CLIMBING_DOWN) {
        if (state == State::CLIMBING_UP) {
            climb();
        }
        else if (state == State::CLIMBING_DOWN) {
            downLadder();
        }
    }
    else {
        if (shouldClimbLadder() && isUnderLadder()) {
            state = State::CLIMBING_UP;
            climb();
        }
        else if (shouldClimbLadder() && isOnLadder()) {
            state = State::CLIMBING_DOWN;
            downLadder();
        }
    }

   
        handleCollision(ghosts);
   //     handleDirectionChange();

    // Update position
    if (isOnAir() || isNearBoundry()) {
        m_diff_x = -m_diff_x;
    }

    if(state != State::CLIMBING_UP && state != State::CLIMBING_DOWN)
        position.setX(position.getX() + m_diff_x);

    draw(me);
}
