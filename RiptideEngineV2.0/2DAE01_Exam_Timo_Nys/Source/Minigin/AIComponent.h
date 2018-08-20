#pragma once
#include "BaseComponent.h"
#include "Enums.h"

class AIComponent final : public BaseComponent
{
	
public:
	
	explicit AIComponent(const std::string& name);
	~AIComponent();

	void Update(float deltaTime) override;
	void GenerateNewDirection();
	void DecreaseBombsPlaced()
	{
		m_BombsPlaced -= 1;
	}
	

	std::string GetName()const { return m_Name; }

private:
	Direction m_Direction = Direction::UP;
	Direction m_PreviousDirection;

	int m_MaxBombs = 1;
	int m_BombsPlaced = 0;

	void IncreaseBombsPlaced()
	{
		m_BombsPlaced += 1;
	}
	std::string m_Name;
	bool CanPlaceBomb()const { return m_BombsPlaced < m_MaxBombs; }
	int GetBombsAvailable()const { return m_MaxBombs - m_BombsPlaced; }
	void GoOppositeDirection();
	bool IsValidPath(Direction direction)const;
};

