#include "MiniginPCH.h"
#include "Grid.h"
#include "fstream"
#include "Pill.h"


Grid::Grid(const std::string& levelName,int width, std::vector<std::shared_ptr<GameObject>> objectsOnGrid)
	:mLevelName(levelName)
	,mGridWidth(width)
	,mObjectsOnGrid(objectsOnGrid)
{
	Init();
	
}


Grid::~Grid()
{
}

void Grid::Init()
{
	std::ifstream inputStream{ mLevelPath + mLevelName };
	std::string tileType;
	if(inputStream.good())
	{
		while (std::getline(inputStream, tileType))
		{
			Parse(tileType);
		}
	}

	for (auto t : mTiles)
	{
		t->Init();
		AddChild(t);
		if(t->GetType() == Tile::SmallPill)
		{
			auto pill = std::make_shared<Pill>(t->GetComponent<Transform>()->GetPosition(), false);
			pill->Init();
			AddChild(pill);
		}
		else if(t->GetType() == Tile::BigPill)
		{
			auto pill = std::make_shared<Pill>(t->GetComponent<Transform>()->GetPosition(), true);
			pill->Init();
			AddChild(pill);
		}
	}

	
	for(auto o : mObjectsOnGrid)
	{
		o->Init();
		AddChild(o);
	}
	

}

int Grid::GetRow(std::shared_ptr<GameObject> toTrack) const
{
	return int(toTrack->GetComponent<Transform>()->GetPosition().y) / TILESIZE;
}

int Grid::GetColumn(std::shared_ptr<GameObject> toTrack) const
{
	return int(toTrack->GetComponent<Transform>()->GetPosition().x) / TILESIZE;
}

int Grid::GetTileIdx(std::shared_ptr<GameObject> toTrack) const
{
	return GetRow(toTrack) * mAmtOfRows + GetColumn(toTrack);
}

int Grid::GetTileLeftIdx(std::shared_ptr<GameObject> toTrack) const
{
	return GetRow(toTrack) * mAmtOfRows + (GetColumn(toTrack) - 1);
}

int Grid::GetTileRightIdx(std::shared_ptr<GameObject> toTrack) const
{
	return GetRow(toTrack) * mAmtOfRows + (GetColumn(toTrack) + 1);
}

int Grid::GetTileUpIdx(std::shared_ptr<GameObject> toTrack) const
{
	return (GetRow(toTrack) - 1) * mAmtOfRows + GetColumn(toTrack);
}

int Grid::GetTileDownIdx(std::shared_ptr<GameObject> toTrack) const
{
	return (GetRow(toTrack) + 1) * mAmtOfRows + GetColumn(toTrack);
}

void Grid::Parse(const std::string& line)
{
	
	for (auto it = line.begin(); it < line.end(); ++it)
	{
		auto type = (*it);
		if(type == '0')
		{
			mTiles.push_back(std::make_shared<Tile>(mCurrentXPos, mCurrentLineHeight,Tile::Type(0) ));
		}
		else if (type == '1')
		{
			mTiles.push_back(std::make_shared<Tile>(mCurrentXPos, mCurrentLineHeight, Tile::Type(1)));
		}
		else if (type == '2')
		{
			mTiles.push_back(std::make_shared<Tile>(mCurrentXPos, mCurrentLineHeight, Tile::Type(2)));
		}
		else if (type == '3')
		{
			mTiles.push_back(std::make_shared<Tile>(mCurrentXPos, mCurrentLineHeight, Tile::Type(3)));
		}
		mCurrentXPos += TILESIZE;
		
	}
	mCurrentLineHeight += TILESIZE;
	mCurrentXPos = 0;
}

