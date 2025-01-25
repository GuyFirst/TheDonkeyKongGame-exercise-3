#include "Entity.h"
#include "Map.h"
#include <iostream>
#include <Windows.h>
#include "gameConfig.h"

bool Entity::isNearBoundry() const {
    if (m_diff_x == (int)gameConfig::Direction::POSITIVE)
        return map->originalMap[getPoint().getY()][getPoint().getX() + 1] == 'Q' || 
        map->originalMap[getPoint().getY()][getPoint().getX() + 1] == '=' ||
        map->originalMap[getPoint().getY()][getPoint().getX() + 1] == '>' ||
        map->originalMap[getPoint().getY()][getPoint().getX() + 1] == '<' ||
        position.getX() >= gameConfig::GAME_WIDTH - 2;
    else
        return map->originalMap[getPoint().getY()][getPoint().getX() - 1] == 'Q'  ||
        map->originalMap[getPoint().getY()][getPoint().getX() - 1] == '=' ||
        map->originalMap[getPoint().getY()][getPoint().getX() - 1] == '>' ||
        map->originalMap[getPoint().getY()][getPoint().getX() - 1] == '<' || (position.getX() <= 0);
}

bool Entity::isOnFloor() const {
    return this->map->currentMap[position.getY() + 1][position.getX()] != ' ' &&
        this->map->currentMap[position.getY() + 1][position.getX()] != 'O' &&
        this->map->currentMap[position.getY() + 1][position.getX()] != 'x';
}

void Entity::draw(char ch, bool isLoad, bool isSave, bool isSilent) const {
    if (!isSilent)
    {
        gotoxy(position.getX(), position.getY());
        std::cout << ch;
    }
    map->currentMap[position.getY()][position.getX()] = ch;
}

void Entity::climb() {
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

void Entity::downLadder() {
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

void Entity::followMario()
{
    //need implimentation
}
