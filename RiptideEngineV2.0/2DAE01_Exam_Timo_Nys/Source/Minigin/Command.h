#pragma once
#include "Player.h"

class Command
{
public:
	Command() = default;
	virtual ~Command() = default;

	virtual void Execute() = 0;
};

class SetDir : public Command
{
public:
	SetDir() = default;
	SetDir(Player::Dir direction,std::shared_ptr<Player> player);
	void Execute() override;
private:
	std::shared_ptr<Player> mPlayer;
	Player::Dir mDirection;
};

class SelectMode : public Command
{
public:
	SelectMode() = default;
	SelectMode(const std::string& levelName);
	void Execute() override;
private:
	const std::string mLevelToLoad;
};







