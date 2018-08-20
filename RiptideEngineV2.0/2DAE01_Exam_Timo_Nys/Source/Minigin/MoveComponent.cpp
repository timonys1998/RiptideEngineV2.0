#include "MiniginPCH.h"
#include "MoveComponent.h"
#include "Structs.h"
#include "GameObject.h"
#include <algorithm>
#include "Maths.h"
#include "Grid.h"


MoveComponent::MoveComponent()
{
}

MoveComponent::~MoveComponent()
{
}

void MoveComponent::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	m_CurrPos = GetOwner().lock()->GetComponent<Transform>()->GetPosition();
	
		if (m_ShouldMove)
		{
			if (IsInTile())
			{
				m_LerpTimer = 0.0f;
				DoMove(false);
				GetOwner().lock()->GetComponent<Transform>()->SetPosition(m_TargetPos.xVal, m_TargetPos.yVal);
			}
			auto lerpedPos = Lerp(m_CurrPos, m_TargetPos, m_LerpTimer / m_LerpScale);
			GetOwner().lock()->GetComponent<Transform>()->SetPosition(lerpedPos.xVal, lerpedPos.yVal);
			
			m_LerpTimer += deltaTime;
			if (m_LerpTimer >= m_LerpScale) m_LerpTimer = 0.0f;
		}

}

bool MoveComponent::IsInTile()
{
	switch (m_Direction)
	{
	case Direction::LEFT:
		if (m_CurrPos.xVal <= m_TargetPos.xVal )
			return true;
		break;
	case Direction::UP:
		if (m_CurrPos.yVal <= m_TargetPos.yVal)
			return true;
		break;
	case Direction::DOWN: 
		if (m_CurrPos.yVal >= m_TargetPos.yVal)
			return true;
		break;
	case Direction::RIGHT:
		if (m_CurrPos.xVal >= m_TargetPos.xVal)
			return true;
		break;
	}
	return false;
}
																																																																																																				