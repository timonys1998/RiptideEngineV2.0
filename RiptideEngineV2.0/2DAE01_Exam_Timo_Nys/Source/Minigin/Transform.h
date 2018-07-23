#pragma once
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec3.hpp>
#include <glm/mat3x3.hpp>
#include "../Minigin/BaseComponent.h"
#pragma warning(pop)

	class Transform final : public BaseComponent
	{
		glm::mat3x3 transform{1,0,0,
							  0,1,0,
							  0,0,1};
	public:
		glm::vec2 GetPosition() const { return glm::vec2{transform[0][2],transform[1][2]} ; }
		explicit Transform();
		 ~Transform();
		void Update(float deltaTime) override
		{
			UNREFERENCED_PARAMETER(deltaTime);
		};
		void SetPosition(float x, float y);
		void translate(float x, float y);
	};

