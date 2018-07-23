#pragma once
#include <glm/detail/type_vec2.hpp>

inline glm::vec2 Lerp(glm::vec2 beginPos,glm::vec2 endPos,float percent)
{
	return (beginPos + percent * (endPos - beginPos));
}
