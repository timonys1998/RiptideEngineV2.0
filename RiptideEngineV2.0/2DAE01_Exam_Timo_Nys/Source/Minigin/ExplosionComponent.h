#pragma once
#include "BaseComponent.h"

enum class Direction;

class ExplosionComponent final : public BaseComponent
{
public:
	explicit ExplosionComponent(int propagationRange,Direction propagationDirection);
	~ExplosionComponent();

	void Update(float deltaTime) override;
	void Propagate()const;

	int GetRange()const { return m_PropagationRange; }

	void Clear()const;

	ExplosionComponent(const ExplosionComponent& other) = delete;
	ExplosionComponent(const ExplosionComponent&& other) = delete;
	ExplosionComponent& operator=(const ExplosionComponent& other) = delete;
	ExplosionComponent& operator=(const ExplosionComponent&& other) = delete;

private:
	int m_PropagationRange;
	float m_LastingTime = 1.0f;
	float m_Timer = 0.0f;
	Direction m_PropagationDirection;

	
};

