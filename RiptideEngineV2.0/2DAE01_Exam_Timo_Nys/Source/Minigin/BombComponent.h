#pragma once
#include "BaseComponent.h"

class BombComponent final : public BaseComponent
{
public:
	explicit BombComponent(std::shared_ptr<GameObject> owningEntity,int tickCount);
	~BombComponent();

	BombComponent(const BombComponent& other) = delete;
	BombComponent(const BombComponent&& other) = delete;
	BombComponent& operator=(const BombComponent& other) = delete;
	BombComponent& operator=(const BombComponent&& other) = delete;

	void Update(float deltaTime) override;
	void Explode()const;
	std::shared_ptr<GameObject> GetOwning()const { return m_spOwningEntity; }
private:
	std::shared_ptr<GameObject> m_spOwningEntity;//Player that placed the bomb
	int m_TicksToExplode;
	float m_Timer = 0.0f;

};

