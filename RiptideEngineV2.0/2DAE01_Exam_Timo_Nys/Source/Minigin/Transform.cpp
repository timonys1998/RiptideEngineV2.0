#include "MiniginPCH.h"
#include "Transform.h"

Transform::Transform()
{
	
}

Transform::~Transform()
{
}

void Transform::SetPosition(const float x, const float y)
{
	transform[0][2] = x;
	transform[1][2] = y;
}

void Transform::translate(float x, float y)
{
	transform[0][2] += x;
	transform[1][2] += y;
}
