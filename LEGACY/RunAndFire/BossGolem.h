#pragma once
#include "Golem.h"
class BossGolem : public Golem
{
public:
	BossGolem(Image &image, float X, float Y, int W, int H, String Name);
	void update(float time, Map & map);
	virtual ~BossGolem() = default;
};


