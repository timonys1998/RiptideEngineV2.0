#pragma once
#include "Enums.h"

struct FLOAT2
{
	
	FLOAT2(float x ,float y) : xVal(x), yVal(y) {};
    FLOAT2() : FLOAT2(0.0f, 0.0f) {};
	float xVal, yVal;

	//We need operator + overloaded to be able to add two FLOAT2
	FLOAT2 operator+(FLOAT2& other)
	{
		return FLOAT2(this->xVal + other.xVal,this->yVal + other.yVal);
	}
	FLOAT2& operator+=(FLOAT2 other)
	{
		this->xVal += other.xVal;
		this->yVal += other.yVal;
		return *this;
	}
	FLOAT2 operator+(FLOAT2 other)
	{
		return FLOAT2(this->xVal + other.xVal, this->yVal + other.yVal);
	}
	FLOAT2 operator-(FLOAT2 other)
	{
		return FLOAT2(this->xVal - other.xVal, this->yVal - other.yVal);
	}
	FLOAT2 operator*(float other)
	{
		return FLOAT2(this->xVal * other, this->yVal * other);
	}
	bool operator==(FLOAT2 other)
	{
		return (this->xVal == other.xVal && this->yVal == other.yVal);
	}
};

struct Tile
{
	Tile(){};
	FLOAT2 pos{0.0f,0.0f};
	TileType type;
};