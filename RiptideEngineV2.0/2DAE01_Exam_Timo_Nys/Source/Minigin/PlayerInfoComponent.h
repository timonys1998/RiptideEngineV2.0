#pragma once
#include "BaseComponent.h"
#include "Enums.h"

class PlayerInfoComponent final : public BaseComponent
{
public:
	PlayerInfoComponent(const std::string& name,ControlType controlType = ControlType::Keyboard, int maxBombs = 2, int bombRange = 1);
	~PlayerInfoComponent();

	int GetID()const { return m_PlayerID; }

	void Update(float deltaTime) override
	{
		if(m_IsRespawning)
		{
			m_RespawnTimer += deltaTime;
			if (m_RespawnTimer >= m_RespawnTime)
				m_IsRespawning = false;
		}
	};

	void IncreaseBombCapacity() { m_MaxBombs++; }
	void IncreaseBombsPlaced(){ m_BombsPlaced += 1; }
	void DecreaseBombsPlaced(){ m_BombsPlaced -= 1; }
	void IncreaseBombRange() { ++m_BombRange; }
	void DecreaseBombRange() { --m_BombRange; }
	bool CanPlaceBomb()const { return m_BombsPlaced < m_MaxBombs; }
	int GetBombsAvailable()const { return m_MaxBombs - m_BombsPlaced; }

	
	int GetBombRange()const { return m_BombRange; }
	

	std::string GetName()const { return m_Name; }
	ControlType GetControls()const { return m_TypeOfControls; }

	void Respawn();
	bool IsRespawning()const { return m_IsRespawning; }

	void SetHasDetonator(bool value) { m_HasDetonator = value; }
	bool HasDetonator()const { return m_HasDetonator; }
	

	PlayerInfoComponent(const PlayerInfoComponent& other) = delete;
	PlayerInfoComponent(const PlayerInfoComponent&& other) = delete;
	PlayerInfoComponent& operator=(const PlayerInfoComponent& other) = delete;
	PlayerInfoComponent& operator=(const PlayerInfoComponent&& other) = delete;

private:
	std::string m_Name;
	float m_RespawnTimer = 0.0f;
	float m_RespawnTime = 1.5f;
	bool m_IsRespawning = false;
	bool m_HasDetonator = false;
	int m_PlayerID;
	int m_MaxBombs;
	int m_BombsPlaced = 0;
	int m_BombRange;

	ControlType m_TypeOfControls; //Defines if this player is controlled by keyboard or controller
	
};

