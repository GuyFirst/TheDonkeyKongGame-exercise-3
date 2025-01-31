#pragma once
#include "Ghost.h"


class UniqueGhost : public Ghost
{
private:
	bool shouldClimbLadder();

public:
	UniqueGhost(Map* map, int m_id, Point startingPosition, char me) : Ghost(map, m_id, startingPosition, me) {}
	//void followMario();
	virtual void move(std::vector<std::unique_ptr<Ghost>>& ghosts, bool isLoad, bool isSave, bool isSilent) override;
};

