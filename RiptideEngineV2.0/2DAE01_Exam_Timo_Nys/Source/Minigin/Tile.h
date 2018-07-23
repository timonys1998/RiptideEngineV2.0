#pragma once
#include "GameObject.h"
#define TILESIZE 32
class Tile : public GameObject
{
public:
	enum Type
	{
		SmallPill = 0,
		Wall = 1,
		BigPill = 2,
		GhostWall = 3
	};
	explicit Tile(int xPos, int yPos, const Type& type);
	virtual ~Tile();
	void Init()override ;
	Type GetType()const { return mType; }
private:
	Type mType;
	glm::vec2 mPos;

};

