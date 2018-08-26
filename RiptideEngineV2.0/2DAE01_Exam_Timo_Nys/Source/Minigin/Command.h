#pragma once

#include "Enums.h"
#include "GameObject.h"

class Command
{
public:
	Command() = default;
	virtual ~Command() = default;

	virtual void Execute(std::shared_ptr<GameObject> obj) = 0;
};



class SetDir : public Command
{
public:
	SetDir() = default;
	SetDir(Direction direction);
	void Execute(std::shared_ptr<GameObject> Mobj) override;
private:
	Direction m_Direction;
};

class SelectMode : public Command
{
public:
	SelectMode(GameMode mode) : m_GameMode(mode){};
	void Execute(std::shared_ptr<GameObject> ModeSelector) override;
private:
	GameMode m_GameMode;
};

class PlaceBomb : public Command
{
public:
	PlaceBomb() = default;
	void Execute(std::shared_ptr<GameObject> obj) override;
};

class Detonate : public Command
{
public:
	Detonate() = default;
	void Execute(std::shared_ptr<GameObject> obj) override;
};







