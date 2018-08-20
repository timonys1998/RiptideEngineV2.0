#pragma once
#include "Structs.h"

//LERP calculation
inline FLOAT2 Lerp(FLOAT2 beginPos,FLOAT2 endPos,float percent)
{
	return beginPos + (endPos - beginPos) * percent;
}
