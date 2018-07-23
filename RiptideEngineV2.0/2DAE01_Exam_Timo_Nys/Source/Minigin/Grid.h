#pragma once
#include "Tile.h"

class Grid : public GameObject
{
public:
	explicit Grid(const std::string& levelName,int width,std::vector<std::shared_ptr<GameObject>> objectsOnGrid);
	virtual ~Grid();
	void Init()override;
	std::vector<std::shared_ptr<Tile>> GetTiles() const { return mTiles; }
	int GetTileIdx(std::shared_ptr<GameObject> toTrack)const;
	int GetTileLeftIdx(std::shared_ptr<GameObject> toTrack)const;
	int GetTileRightIdx(std::shared_ptr<GameObject> toTrack)const;
	int GetTileUpIdx(std::shared_ptr<GameObject> toTrack)const;
	int GetTileDownIdx(std::shared_ptr<GameObject> toTrack)const;

private:
	void Parse(const std::string& line);
	int GetRow(std::shared_ptr<GameObject> toTrack) const;
	int GetColumn(std::shared_ptr<GameObject> toTrack) const;
	int mGridWidth;
	int mAmtOfRows = mGridWidth / 32;
	int mCurrentLineHeight = 0;
	int mCurrentXPos = 0;
	std::vector<std::shared_ptr<Tile>> mTiles;
	std::string mLevelName;
	std::string mLevelPath = "../Levels/";
	std::vector<std::shared_ptr<GameObject>> mObjectsOnGrid;
};

