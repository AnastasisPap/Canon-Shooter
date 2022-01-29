#pragma once
#include "gameObject.h"
#include "config.h"
#include "utils.h"

class Ball : public GameObject
{
	float ball_x = CANVAS_WIDTH / 2;
	float ball_y = CANVAS_HEIGHT;
	float angle;
	float speed = 2;
	bool inverse = false;
public:
	void update() override;
	void init() override;
	void draw() override;
	void set_angle(float angle);
	Coords get_coords();
	void set_coords(Coords coords) { ball_x = coords.x; ball_y = coords.y; }
	void checkWall();
	void invert_direction() { inverse = !inverse; }
	bool upwards() { return !inverse; }
};