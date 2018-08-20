#pragma once
#include "Singleton.h"
#include "GameObject.h"

class CollisionSystem final : public Singleton<CollisionSystem>
{
public:

	void LateUpdate();

private:
	void CheckCollisionWithEnemies(std::shared_ptr<GameObject> player);
	void CheckCollisionWithExplosions(std::shared_ptr<GameObject> entity);
	void CheckCollisionWithPowerups(std::shared_ptr<GameObject> entity);
	void CheckCollisionWithDoor(std::shared_ptr<GameObject> player);
};

