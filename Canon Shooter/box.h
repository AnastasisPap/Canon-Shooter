#pragma once
#include "gameObject.h"
#include "utils.h"

class Box : public GameObject
{
	float pos_x, pos_y;
public:
	void update() override;
	void draw() override;
	void init() override;
	Coords get_coords() const;
	void set_coords(Coords coords) { pos_x = coords.x; pos_y = coords.y; }
	Box();
	~Box();
};