#include "MiniginPCH.h"
#include "Grid.h"
#include "fstream"
#include "TextureComponent.h"
#include "RenderComponent.h"
#include "Player.h"
#include "InstantiateEntities.h"
#include "Game.h"


void Grid::GenerateLevel(std::shared_ptr<Scene> levelScene,const std::string& levelName)
{
	m_spLevelScene = levelScene;
	std::shared_ptr<GameObject> spBaseMap = GameObject::Instantiate(FLOAT2(0.0f, 0.0f)); //Small offset so we have some space at top for UI
	spBaseMap->AddComponent(std::make_shared<TextureComponent>("level.png"));
	spBaseMap->AddComponent(std::make_shared<RenderComponent>());
	levelScene->Add(spBaseMap);

	//Load in tile information
	std::ifstream inputStream{ mLevelPath + levelName };
	std::string tileType;

	if (inputStream.good())
	{
		while (std::getline(inputStream, tileType))
		{
			m_CurrPos.xVal = 0.0f;
			Parse(tileType);
		}
	}
}

std::map<int, std::shared_ptr<GameObject>> Grid::GetPowerups() const
{
	return m_Powerups;
}

std::pair<int, std::shared_ptr<GameObject>> Grid::GetDoor() const
{
	return m_Door;
}


TileType Grid::GetTileTypeInDirection(std::shared_ptr<GameObject> toTrack, Direction direction) 
{
	int idx = GetIndexInDirection(toTrack, direction);
	Tile tile = m_Tiles[idx];
	return tile.type;
}

FLOAT2 Grid::GetPosInDirection(std::shared_ptr<GameObject> toTrack, Direction direction)
{
	int idx = GetIndexInDirection(toTrack, direction);
	return m_Tiles[idx].pos;
}

Tile Grid::GetTile(std::shared_ptr<GameObject> toTrack)
{
	int idx = GetIndex(toTrack);
	return m_Tiles[idx];
}



void Grid::AddPlayerAtTile(int idx, const std::string& name, ControlType controlType)
{
	auto pos = m_Tiles[idx].pos;
	m_PlayerAmount++;
	std::shared_ptr<GameObject> playerObj = InstantiatePlayer(pos, controlType,name);
	m_MovingEntitiesOnGrid[name] = playerObj;
	m_spLevelScene->Add(playerObj);
}

void Grid::AddEnemyAtTile(int idx, const std::string& name)
{
	auto pos = m_Tiles[idx].pos;
	++m_EnemyAmount;
	std::shared_ptr<GameObject> enemyObj = InstantiateEnemy(pos,name);
	m_MovingEntitiesOnGrid[name] = enemyObj;
	m_spLevelScene->Add(enemyObj);
}

void Grid::AddExplosions(std::shared_ptr<GameObject> bomb,int range)
{
	int tempRange = range;

	//Create explosion North
	auto northIdx = GetIndexInDirection(bomb, Direction::UP);
	auto northPos = m_Tiles[northIdx].pos;
	if (GetTileTypeInDirection(bomb, Direction::UP) != TileType::HardWall) {
		if (GetTileTypeInDirection(bomb, Direction::UP) == TileType::SoftWall) {
			int indexOfSoftWall = GetIndexInDirection(bomb, Direction::UP);
			m_BreakableBlocks[indexOfSoftWall]->GetComponent<RenderComponent>()->EnableRendering(false);
			m_BreakableBlocks.erase(indexOfSoftWall);
			--m_ObstructionsAmount;
			if (ShouldPlaceDoor()) PlaceDoor(indexOfSoftWall);
			m_Tiles[indexOfSoftWall].type = TileType::None;
			AddPowerup(indexOfSoftWall);
		}
		else
		{
			std::shared_ptr<GameObject> explosionObj = InstantiateExplosion(northPos, tempRange, Direction::UP);
			m_Explosions[northIdx] = explosionObj;
			m_spLevelScene->Add(explosionObj);
			explosionObj->GetComponent<ExplosionComponent>()->Propagate();
		}
		
	}

	//Create Explosion East
	auto eastIdx = GetIndexInDirection(bomb, Direction::RIGHT);
	auto eastPos = m_Tiles[eastIdx].pos;
	if (GetTileTypeInDirection(bomb, Direction::RIGHT) != TileType::HardWall) {
		if (GetTileTypeInDirection(bomb, Direction::RIGHT) == TileType::SoftWall) {
			int indexOfSoftWall = GetIndexInDirection(bomb, Direction::RIGHT);
			m_BreakableBlocks[indexOfSoftWall]->GetComponent<RenderComponent>()->EnableRendering(false);
			m_BreakableBlocks.erase(indexOfSoftWall);
			--m_ObstructionsAmount;
			if (ShouldPlaceDoor()) PlaceDoor(indexOfSoftWall);
			m_Tiles[indexOfSoftWall].type = TileType::None;
			AddPowerup(indexOfSoftWall);
		}
		else
		{
			std::shared_ptr<GameObject> explosionObj2 = InstantiateExplosion(eastPos, tempRange, Direction::RIGHT);
			m_Explosions[eastIdx] = explosionObj2;
			m_spLevelScene->Add(explosionObj2);
			explosionObj2->GetComponent<ExplosionComponent>()->Propagate();
		}
		
	}

	//Create Explosion South
	auto southIdx = GetIndexInDirection(bomb, Direction::DOWN);
	auto southPos = m_Tiles[southIdx].pos;
	if (GetTileTypeInDirection(bomb, Direction::DOWN) != TileType::HardWall) {
		if (GetTileTypeInDirection(bomb, Direction::DOWN) == TileType::SoftWall) {
			int indexOfSoftWall = GetIndexInDirection(bomb, Direction::DOWN);
			m_BreakableBlocks[indexOfSoftWall]->GetComponent<RenderComponent>()->EnableRendering(false);
			m_BreakableBlocks.erase(indexOfSoftWall);
			--m_ObstructionsAmount;
			if (ShouldPlaceDoor()) PlaceDoor(indexOfSoftWall);
			m_Tiles[indexOfSoftWall].type = TileType::None;
			AddPowerup(indexOfSoftWall);
		}
		else
		{
			std::shared_ptr<GameObject> explosionObj3 = InstantiateExplosion(southPos, tempRange, Direction::DOWN);
			m_Explosions[southIdx] = explosionObj3;
			m_spLevelScene->Add(explosionObj3);
			explosionObj3->GetComponent<ExplosionComponent>()->Propagate();
		}
		
	}

	//Create Explosion West
	auto westIdx = GetIndexInDirection(bomb, Direction::LEFT);
	auto westPos = m_Tiles[westIdx].pos;
	if (GetTileTypeInDirection(bomb, Direction::LEFT) != TileType::HardWall) {
		if (GetTileTypeInDirection(bomb, Direction::LEFT) == TileType::SoftWall) {
			int indexOfSoftWall = GetIndexInDirection(bomb, Direction::LEFT);
			m_BreakableBlocks[indexOfSoftWall]->GetComponent<RenderComponent>()->EnableRendering(false);
			m_BreakableBlocks.erase(indexOfSoftWall);
			--m_ObstructionsAmount;
			if (ShouldPlaceDoor()) PlaceDoor(indexOfSoftWall);
			m_Tiles[indexOfSoftWall].type = TileType::None;
			AddPowerup(indexOfSoftWall);
		}
		else
		{
			std::shared_ptr<GameObject> explosionObj4 = InstantiateExplosion(westPos, tempRange, Direction::LEFT);
			m_Explosions[westIdx] = explosionObj4;
			m_spLevelScene->Add(explosionObj4);
			explosionObj4->GetComponent<ExplosionComponent>()->Propagate();
		}
		
	}
	
}

void Grid::AddExplosionInDirection(int idx,Direction direction)
{
	CreateExplosion(idx, direction);
}

void Grid::RemoveExplosion(int idx)
{
	m_Explosions.erase(idx);
}

void Grid::RemovePickup(int idx)
{
	auto obj = m_Powerups[idx];
	m_Powerups.erase(idx);
	SceneManager::GetInstance().GetActiveScene()->Remove(obj); 
	--m_PickupAmount;

}

void Grid::RemoveEntity(std::string name)
{
	auto temp = m_MovingEntitiesOnGrid.find(name);
	if (temp->second->GetComponent<PlayerInfoComponent>()) {
		auto playerObs = temp->second->GetComponent<PlayerObserverComponent>();
		for (auto p : m_Powerups)
		{
			p.second->GetComponent<SubjectComponent>()->Detach(playerObs);
		}
		--m_PlayerAmount;
	}
	else
		--m_EnemyAmount;
	m_MovingEntitiesOnGrid.erase(name);
}

void Grid::AddBomb(std::shared_ptr<GameObject> owningEntity)
{
	auto tile = GetTile(owningEntity);
	std::shared_ptr<GameObject> bombObj;
	if(owningEntity->HasComponent<PlayerInfoComponent>() && owningEntity->GetComponent<PlayerInfoComponent>()->HasDetonator())
		bombObj = InstantiateBomb(tile.pos, std::numeric_limits<int>::max(), owningEntity);
	else
		bombObj = InstantiateBomb(tile.pos, 2, owningEntity);
	int idx = GetIndex(owningEntity);
	m_Bombs[idx] = bombObj;
	m_spLevelScene->Add(bombObj);
}

void Grid::RemoveBomb(int idx)
{
	m_Bombs.erase(idx);
}

std::map<std::string, std::shared_ptr<GameObject>> Grid::GetEntities() const
{
	return m_MovingEntitiesOnGrid;
}

std::map<int, std::shared_ptr<GameObject>> Grid::GetExplosions() const
{
	return m_Explosions;
}

std::map<int, std::shared_ptr<GameObject>> Grid::GetBombs() const
{
	return m_Bombs;
}

bool Grid::TileHasBomb(int idx)const
{
	auto index = m_Bombs.find(idx);
	return !(index == m_Bombs.end());
}

bool Grid::TileHasExplosion(int idx) const
{
	auto index = m_Explosions.find(idx);
	return !(index == m_Explosions.end());
}

void Grid::CheckGameOver()
{
	if(Game::GetGameMode() == GameMode::Singleplayer || Game::GetGameMode() == GameMode::COOP)
	{
		if (m_EnemyAmount == 0 || m_PlayerAmount == 0) m_IsGameOver = true;
		
	}
	else
	{
		if (m_PlayerAmount == 1) m_IsGameOver = true;
	}
}


void Grid::Parse(const std::string& line)
{
	for(auto it = line.begin();it < line.end();++it)
	{
		Tile gridTile;
		gridTile.pos = m_CurrPos;
		if((*it) == '0')
		{
			gridTile.type = TileType::None;
			m_Tiles[m_CurrentIndex] = gridTile;
		}
		else if((*it) == '1')
		{
			gridTile.type = TileType::HardWall;
			m_Tiles[m_CurrentIndex] = gridTile;
		}
		else if ((*it) == '2')
		{
			auto BreakableBrickObj = GameObject::Instantiate(m_CurrPos);
			BreakableBrickObj->AddComponent(std::make_shared<TextureComponent>("BreakableWall.png"));
			BreakableBrickObj->AddComponent(std::make_shared<RenderComponent>());
			++m_ObstructionsAmount;

			m_spLevelScene->Add(BreakableBrickObj);
			m_BreakableBlocks[m_CurrentIndex] = BreakableBrickObj;
			gridTile.type = TileType::SoftWall;
			m_Tiles[m_CurrentIndex] = gridTile;
		}
		m_CurrPos.xVal += 32.0f;
		++m_CurrentIndex;

	}
	m_CurrPos.yVal += 32.0f;
}

int Grid::GetRow(std::shared_ptr<GameObject> toTrack) const
{
	return int(toTrack->GetComponent<Transform>()->GetPosition().yVal  / m_TileSize);
}

int Grid::GetCol(std::shared_ptr<GameObject> toTrack) const
{
	return int(toTrack->GetComponent<Transform>()->GetPosition().xVal / m_TileSize);
}

int Grid::GetIndex(std::shared_ptr<GameObject> toTrack) const
{
	int row = GetRow(toTrack);
	int col = GetCol(toTrack);

	//Formula to calculate an index on our grid = (row * amtofrows + col)
	int idx = row * m_AmtOfRows + col;
	return idx;

}

int Grid::GetIndexInDirection(std::shared_ptr<GameObject> toTrack, Direction direction)const
{
	int row = GetRow(toTrack);
	int col = GetCol(toTrack);

	switch (direction) //We want tile in a direction so we need to increment or decrement the row or column
	{
	case Direction::UP:
		--row;
		break;
	case Direction::DOWN:
		++row;
		break;
	case Direction::LEFT:
		--col;
		break;
	case Direction::RIGHT:
		++col;
		break;
	}

	//Formula to calculate an index on our grid = (row * amtofrows + col)
	int idx = row * m_AmtOfRows + col;
	return idx;
}

void Grid::CreateExplosion(int idx,Direction direction)
{
	auto explosionOrigin = m_Explosions[idx];
	auto pos = GetPosInDirection(explosionOrigin,direction);
	if (GetTileTypeInDirection(explosionOrigin, direction) != TileType::HardWall) {
		if (GetTileTypeInDirection(explosionOrigin, direction) == TileType::SoftWall) {
			int indexOfSoftWall = GetIndexInDirection(explosionOrigin, direction);
			m_BreakableBlocks[indexOfSoftWall]->GetComponent<RenderComponent>()->EnableRendering(false);
			m_BreakableBlocks.erase(indexOfSoftWall);
			--m_ObstructionsAmount;
			if (ShouldPlaceDoor()) PlaceDoor(indexOfSoftWall);
			m_Tiles[indexOfSoftWall].type = TileType::None;
			int range = 0;
			std::shared_ptr<GameObject> explosionObj = InstantiateExplosion(pos, range, direction);
			m_Explosions[idx] = explosionObj;
			m_spLevelScene->Add(explosionObj);
			explosionObj->GetComponent<ExplosionComponent>()->Clear();
			AddPowerup(indexOfSoftWall);
		}
		else
		{
			int range = explosionOrigin->GetComponent<ExplosionComponent>()->GetRange();
			std::shared_ptr<GameObject> explosionObj = InstantiateExplosion(pos, range, direction);
			m_Explosions[idx] = explosionObj;
			m_spLevelScene->Add(explosionObj);
		}
		
	}
}

void Grid::PlaceDoor(int tileIdx)
{
	auto pos = m_Tiles[tileIdx].pos;
	m_Door.first = tileIdx;
	m_Door.second = InstantiateDoor(pos);
	m_spLevelScene->Add(m_Door.second);
}

bool Grid::ShouldPlaceDoor()const
{
	if(m_Door.second == nullptr)
	{
		if(m_ObstructionsAmount == 0)
		{
			return true;
		}
			
		int random = rand() % 100;
		return random >= 90;
	}
	return false;
}

void Grid::AddPowerup(int idx)
{
	//Generate random type
	int typeIdx = rand() % 6;
	if (typeIdx <= 3 && m_PickupAmount < m_MaxPickups) {

		auto pos = m_Tiles[idx].pos;
		std::shared_ptr<GameObject> powerupObj = InstantiatePickup(pos, PickupType(typeIdx));

		m_Powerups[idx] = powerupObj;
		m_spLevelScene->Add(powerupObj);
		++m_PickupAmount;
	}
}
