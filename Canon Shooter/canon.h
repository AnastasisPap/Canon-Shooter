#pragma once
#include "config.h"
#include "GameObject.h"

class Canon : public GameObject
{
	float pos_x = CANVAS_WIDTH / 2;
	float pos_y = CANVAS_HEIGHT;
	const float centerY = CANVAS_HEIGHT;
	const float centerX = CANVAS_WIDTH / 2;
	bool hasFired = false;
	float angle;
public:
	void update() override;
	void draw() override;
	void init() override;
	float find_angle(float x, float y);
	float get_angle() { return angle; }
	void set_fired(bool hasFired) { this->hasFired = hasFired; }
};