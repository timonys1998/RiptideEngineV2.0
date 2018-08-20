#include "MiniginPCH.h"
#include "AIComponent.h"
#include "MoveComponent.h"
#include "GameObject.h"
#include "Grid.h"
#include "RenderComponent.h"


AIComponent::AIComponent(const std::string& name)
	:m_Name(name)
{
	m_PreviousDirection = m_Direction;
}


AIComponent::~AIComponent()
{
}

void AIComponent::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
	auto owner = GetOwner().lock();
	auto moveComp = owner->GetComponent<MoveComponent>();
	int idx = Grid::GetInstance().GetIndex(owner);
	int idxNextTile = Grid::GetInstance().GetIndexInDirection(owner, m_Direction);
	if (moveComp)
	{
		if (!moveComp->ShouldMove())
		{
			auto type = Grid::GetInstance().GetTileTypeInDirection(owner, m_Direction);
			if (type != TileType::HardWall && type != TileType::SoftWall && !Grid::GetInstance().TileHasBomb(idxNextTile))
			{
				if (Grid::GetInstance().TileHasExplosion(idxNextTile) && type != TileType::HardWall)
				{
					GoOppositeDirection();
				}
				owner->GetComponent<MoveComponent>()->SetDirection(m_Direction);
				moveComp->SetTarget(Grid::GetInstance().GetPosInDirection(owner, m_Direction));
				owner->GetComponent<MoveComponent>()->DoMove(true);
			}
			else if(type == TileType::SoftWall)
			{
				if(CanPlaceBomb() && !Grid::GetInstance().TileHasBomb(idx))
				{
					IncreaseBombsPlaced();
					GoOppositeDirection();
					Grid::GetInstance().AddBomb(owner);
				}
				else
				{
					if (Grid::GetInstance().TileHasBomb(idx) || Grid::GetInstance().TileHasExplosion(idx))
					{
						GenerateNewDirection();
					}
				}
			}
			else
			{
				GenerateNewDirection();
			}
		}
		
	}
}

void AIComponent::GenerateNewDirection()
{
	int directionIdx = rand() % 4;

	//Make sure we dont get same direction again
	while (directionIdx == int(m_PreviousDirection))
	{
		directionIdx = rand() % 4;
	}
	m_PreviousDirection = m_Direction;
	switch(directionIdx)
	{
	case 0:
		m_Direction = Direction::UP;
		break;
	case 1:
		m_Direction = Direction::DOWN;
		break;
	case 2:
		m_Direction = Direction::LEFT;
		break;
	case 3:
		m_Direction = Direction::RIGHT;
		break;
	}
}



void AIComponent::GoOppositeDirection()
{
	switch (m_Direction)
	{
	case Direction::UP:
		if (IsValidPath(Direction::DOWN))
			m_Direction = Direction::DOWN;
		else
			GenerateNewDirection();
		break;
	case Direction::RIGHT:
	if (IsValidPath(Direction::LEFT))
		m_Direction = Direction::LEFT;
	else
		GenerateNewDirection();
		break;
	case Direction::DOWN:
	if (IsValidPath(Direction::UP))
		m_Direction = Direction::UP;
	else
		GenerateNewDirection();
		break;
	case Direction::LEFT:
	if (IsValidPath(Direction::RIGHT))
		m_Direction = Direction::RIGHT;
	else
		GenerateNewDirection();
		break;
	}
}

bool AIComponent::IsValidPath(Direction direction)const
{
	auto owner = GetOwner().lock();
	TileType typeInDir;
	typeInDir = Grid::GetInstance().GetTileTypeInDirection(owner, direction);
	return typeInDir != TileType::HardWall && typeInDir != TileType::SoftWall ;
}


