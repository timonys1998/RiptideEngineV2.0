#pragma once
#include "GameObject.h"

class Pill : public GameObject
{
public:
	explicit Pill(const glm::vec2& pos, bool isBig);
	virtual ~Pill();

	void Init() override;
	int GetCount()const { return mCount; }
private:
	static int mCount;
	bool mIsBig;
};

