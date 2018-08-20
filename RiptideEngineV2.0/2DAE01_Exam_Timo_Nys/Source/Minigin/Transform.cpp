#include "MiniginPCH.h"
#include "Transform.h"

Transform::Transform()
	:Transform(0.0f,0.0f)
{
	
}

Transform::Transform(FLOAT2 pos)
	:m_Position(pos)
	,m_StartPosition(pos)
{
}

Transform::Transform(float x, float y)
	:Transform(FLOAT2(x,y))
{
}

Transform::~Transform()
{
}

void Transform::SetPosition(const float x, const float y)
{
	m_Position.xVal = x;
	m_Position.yVal = y;
}

void Transform::SetPosition(FLOAT2 pos)
{
	SetPosition(pos.xVal, pos.yVal);
}

void Transform::Translate(float x, float y)
{
	m_Position.xVal += x;
	m_Position.yVal += y;
}

void Transform::Translate(FLOAT2 translation)
{
	Translate(translation.xVal, translation.yVal);
}
