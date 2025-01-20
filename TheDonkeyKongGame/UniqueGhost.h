#pragma once
#include "Ghost.h"
class UniqueGhost : public Ghost
{
public:
	UniqueGhost(Map* map, int m_id, Point startingPosition, char me) : Ghost(map, m_id, startingPosition, me) {}
};

