#include "box.h"
#include "sgg\graphics.h"
#include "config.h"

void Box::update() {}

void Box::draw()
{
	graphics::Brush br;
	br.texture = std::string(ASSET_PATH) + "box.png";
	graphics::resetPose();
	graphics::drawRect(pos_x, pos_y, BOX_WIDTH, BOX_HEIGHT, br);
}

Coords Box::get_coords() const
{
	Coords coords;
	coords.x = pos_x;
	coords.y = pos_y;

	return coords;
}

void Box::init() {}
Box::~Box() {}
Box::Box() { init(); }