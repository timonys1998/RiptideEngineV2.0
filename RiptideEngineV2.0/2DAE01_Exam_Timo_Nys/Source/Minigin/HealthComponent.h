#pragma once
#include "BaseComponent.h"

class HealthComponent : public BaseComponent
	{
	public:
		HealthComponent(int health);
		~HealthComponent();

		void Update(float deltaTime) override { UNREFERENCED_PARAMETER(deltaTime); };

		int GetLives()const { return m_Lives; }
		void SetHealth(int health) { m_Lives = health; }
		void Increase(int amount) { m_Lives += amount; }
		void Decrease(int amount) { m_Lives -= amount; }
		

		HealthComponent(const HealthComponent& other) = delete;
		HealthComponent(const HealthComponent&& other) = delete;
		HealthComponent& operator=(const HealthComponent& other) = delete;
		HealthComponent& operator=(const HealthComponent&& other) = delete;

	private:
		int m_Lives;
	};


