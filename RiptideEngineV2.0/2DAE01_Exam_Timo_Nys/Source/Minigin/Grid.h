#pragma once
#include "Singleton.h"
#include "Scene.h"
#include <map>
#include "Structs.h"

class Grid final : public Singleton<Grid>
{
public:
	void GenerateLevel(std::shared_ptr<Scene> levelScene, const std::string& levelName);

	TileType GetTileTypeInDirection(std::shared_ptr<GameObject> toTrack, Direction direction);
	FLOAT2 GetPosInDirection(std::shared_ptr<GameObject> toTrack, Direction direction);
	Tile GetTile(std::shared_ptr<GameObject> toTrack);
	int GetIndex(std::shared_ptr<GameObject> toTrack)const;
	int GetIndexInDirection(std::shared_ptr<GameObject> toTrack, Direction direction)const;
	int GetPlayerAmount()const { return m_PlayerAmount; }
	std::map<std::string, std::shared_ptr<GameObject>> GetEntities()const;
	std::map<int, std::shared_ptr<GameObject>> GetExplosions()const;
	std::map<int, std::shared_ptr<GameObject>> GetBombs()const;
	std::map<int, std::shared_ptr<GameObject>> GetPowerups()const;
	std::pair<int, std::shared_ptr<GameObject>> GetDoor()const;


	void AddPlayerAtTile(int idx,const std::string& name,ControlType controlType = ControlType::Keyboard);
	void AddEnemyAtTile(int idx, const std::string& name);
	void AddExplosions(std::shared_ptr<GameObject> bomb,int range);
	void AddExplosionInDirection(int idx,Direction direction);
	void AddBomb(std::shared_ptr<GameObject> owningEntity);
	void AddPowerup(int idx);

	void RemoveBomb(int idx);
	void RemoveExplosion(int idx);
	void RemovePickup(int idx);
	void RemoveEntity(std::string name);
	
	bool TileHasBomb(int idx)const;
	bool TileHasExplosion(int idx)const;

	bool GameIsOver()const { return m_IsGameOver; }
	void CheckGameOver();
	
private:
	
	int m_PlayerAmount = 0;
	int m_EnemyAmount = 0;
	int m_ObstructionsAmount = 0;
	int m_PickupAmount = 0;
	int m_MaxPickups = 15;

	int m_CurrentIndex = 0;
	int m_GridSize = 480;
	int m_TileSize = 32;
	int m_AmtOfRows = m_GridSize / m_TileSize;
	int m_AmtOfCols = m_GridSize / m_TileSize;
	FLOAT2 m_CurrPos = { 0.0f,0.0f };
	bool m_IsGameOver = false;

	std::string mLevelPath = "../Levels/";
	std::shared_ptr<Scene> m_spLevelScene;
	std::pair<int, std::shared_ptr<GameObject>> m_Door;

	std::map<std::string, std::shared_ptr<GameObject>> m_MovingEntitiesOnGrid; //Name = key eg bomberman
	std::map<int, Tile> m_Tiles; //Contains position + type of a tile
	std::map<int, std::shared_ptr<GameObject>> m_BreakableBlocks;
	std::map<int, std::shared_ptr<GameObject>> m_Bombs; //All the bombs on the grid;
	std::map<int, std::shared_ptr<GameObject>> m_Explosions; //All explosions on the grid
	std::map<int, std::shared_ptr<GameObject>> m_Powerups;
	
	void Parse(const std::string& line);
	int GetRow(std::shared_ptr<GameObject>toTrack)const;
	int GetCol(std::shared_ptr<GameObject>toTrack)const;

	void CreateExplosion(int idx,Direction direction);
	void PlaceDoor(int tileIdx);
	bool ShouldPlaceDoor()const;
};
