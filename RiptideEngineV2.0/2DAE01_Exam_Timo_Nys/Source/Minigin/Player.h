#pragma once
#include "GameObject.h"

class Player : public GameObject
{
public:
	static std::shared_ptr<Player> Instantiate(const FLOAT2& position = { 0.0f,0.0f },ControlType controlsType = ControlType::Keyboard,bool isEnemy = false);
	Player() = default;
	~Player();

	Player(const Player& other) = delete;
	Player(const Player&& other) = delete;
	Player& operator=(const Player& other) = delete;
	Player& operator=(const Player&& other) = delete;
	
private:
	
	static int m_PlayerCount;
};

