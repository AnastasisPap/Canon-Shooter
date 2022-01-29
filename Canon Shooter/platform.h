#pragma once
#include "gameObject.h"
#include "config.h"
#include "utils.h"

class Platform : public GameObject
{
	float pos_x = CANVAS_WIDTH / 2;
	float pos_y = CANVAS_HEIGHT - 20;
	float angle;
	float speed = 9;
public:
	void update() override;
	void draw() override;
	void init() override;
	Coords get_coords();
	void reset_coords();
};