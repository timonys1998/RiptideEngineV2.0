#pragma once

enum class Event : int
{
	DetonatorPickup,
	BombUpPickup,
	RangeUpPickup,
	HeartPickup
};

enum class GameMode
{
	None,
	Singleplayer,
	COOP,
	Versus
};

enum class TileType
{
	None = 0,
	HardWall = 1,
	SoftWall = 2,
};

enum class Direction
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
	NONE
};

enum class ControlType
{
	Keyboard,
	Controller
};

enum class PickupType
{
	IncreaseRange,
	IncreaseMaxBombs,
	Detonator,
	Heart
};
