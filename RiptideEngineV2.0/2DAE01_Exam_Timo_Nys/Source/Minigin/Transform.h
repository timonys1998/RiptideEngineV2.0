#pragma once
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec3.hpp>
#include <glm/mat3x3.hpp>
#include "../Minigin/BaseComponent.h"
#include "Structs.h"
#pragma warning(pop)

	class Transform final : public BaseComponent
	{
		FLOAT2 m_Position;
		FLOAT2 m_StartPosition;

	public:
		
		explicit Transform();
		explicit Transform(FLOAT2 pos);
		explicit Transform(float x, float y);
		 ~Transform();

		 Transform(const Transform& other) = delete;
		 Transform(const Transform&& other) = delete;
		 Transform& operator=(const Transform& other) = delete;
		 Transform& operator=(const Transform&& other) = delete;

		void Update(float deltaTime) override
		{
			UNREFERENCED_PARAMETER(deltaTime);
		};
		FLOAT2 GetPosition() const { return m_Position; }
		void SetPosition(float x, float y);
		void SetPosition(FLOAT2 pos);
		void Translate(float x, float y);
		void Translate(FLOAT2 translation);
		void ResetPosition() { m_Position = m_StartPosition; }
	};

