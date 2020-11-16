#pragma once
#include "Ghost.h"
class BossGhost : public Ghost
{
public:
	BossGhost(Image &image, float X, float Y, int W, int H, String Name);
	void update(float, Map &, float, float);
	void BossGhost::check_collision(float dx, float dy, Map & map);
	void reduse();
	virtual ~BossGhost() = default;
};


