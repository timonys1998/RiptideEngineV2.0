#include "MiniginPCH.h"
#include "Tile.h"
#include "TextureComponent.h"
#include "RenderComponent.h"
#include <SDL.h>
#include "Renderer.h"


Tile::Tile(int xPos, int yPos, const Type& type)
	:mType(type),
	mPos(xPos,yPos)
{
	
}


Tile::~Tile()
{
}

void Tile::Init()
{
	std::string textureName = "";
	switch(mType)
	{
	case SmallPill:
		textureName = "SmallPill.png";
		break;
	case Wall:
		textureName = "Wall.png";
		break;
	case BigPill:
		textureName = "BigPill.png";
		break;
	case GhostWall:
		textureName = "GhostWall.png";
		break;
	}

	AddComponent(std::make_shared<TextureComponent>(textureName));
	AddComponent(std::make_shared<RenderComponent>(GetComponent<TextureComponent>()->GetTexture()));
	GetComponent<Transform>()->SetPosition(mPos.x, mPos.y);
}
