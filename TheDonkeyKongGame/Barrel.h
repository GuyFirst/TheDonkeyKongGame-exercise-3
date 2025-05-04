#pragma once
#include "gameConfig.h"
#include "Map.h"
#include "Point.h"
#include <vector>
#include "Entity.h"
class Mario;

class Barrel : public Entity {
    int m_prev_diff_x = 0;
    int m_fallCounter = 0;

    // Helper methods
    void updatePosition();
    void handleExplosion(std::vector<Barrel>& barrels,Mario* mario, bool isLoad, bool isSave, bool isSilent);
    bool isOnAir(char& refFloor);
    bool isNearWall(int dirX) const;
    bool checkFallHeight();
    bool isMarioNearMe(Point marioPos) const;

public:
    std::vector<Point> explosionPattern = {
       {0, 0}, {0, -1}, {1, 0},
       {-1, 0}, {-1, -1}, {1, -1},
       {2, 0}, {2, -1}, {2, -1},
       {-2, 0 }, {-2, -1}, {-2, -1},
    };
    static int barrelCurr;
    static int barrelSpawnCounter;

    Barrel(Map* map, Point startingPosition)
        : Entity(startingPosition, 'O', (int)gameConfig::Direction::POSITIVE, (int)gameConfig::Direction::STAY, map) {}

    Barrel() : Entity(Point(0, 0), 'O', (int)gameConfig::Direction::POSITIVE, (int)gameConfig::Direction::STAY, nullptr) {}

    void move(std::vector<Barrel>& barrels,Mario* mario, bool isLoad, bool isSave, bool isSilent);
    void reset();
    void addBarrel(std::vector<Barrel>& barrels, Map* map);  
    void drawExplosion(const std::vector<Point>& pattern, char explosionChar, bool isSilent);
   
    static int getBarrelCurr() {  return barrelCurr;  }
    static int getBarrelSpawnCounter() { return barrelSpawnCounter; }

    static void incrementBarrelCurr() {barrelCurr++; }
    static void decrementBarrelCurr() { barrelCurr--; }
    static void resetBarrelSpawnCounter() { barrelSpawnCounter = 0; }

    bool operator==(const Barrel& other) const { return position == other.position; }
    bool operator!=(const Barrel& other) const {return !(*this == other);}

    char getMapChar() const { return this->getMap()->originalMap[position.getY()][position.getX()]; }
};
