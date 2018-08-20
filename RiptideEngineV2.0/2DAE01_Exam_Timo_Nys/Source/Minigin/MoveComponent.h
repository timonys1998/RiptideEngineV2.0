#pragma once
#include "BaseComponent.h"
#include "Enums.h"
#include "Structs.h"

class MoveComponent : public BaseComponent
{
public:
	MoveComponent();
	~MoveComponent();

	void Update(float deltaTime) override;
	void SetDirection(Direction direction) { m_Direction = direction; }
	void SetTarget(FLOAT2 target) { m_TargetPos = target; }
	void DoMove(bool move) { m_ShouldMove = move; }
	bool ShouldMove()const { return m_ShouldMove; }

	MoveComponent(const MoveComponent& other) = delete;
	MoveComponent(const MoveComponent&& other) = delete;
	MoveComponent& operator=(const MoveComponent& other) = delete;
	MoveComponent& operator=(const MoveComponent&& other) = delete;
private:
	Direction m_Direction;
	FLOAT2 m_CurrPos;
	FLOAT2 m_TargetPos;
	float m_LerpTimer = 0.0f;
	float m_LerpScale = 0.5f;
	bool m_ShouldMove = false;

	bool IsInTile();
};

