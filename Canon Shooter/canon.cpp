#include "canon.h"
#include <iostream>
#include "sgg\graphics.h"
#include "utils.h"
#include "config.h"

void Canon::update()
{
}

void Canon::draw()
{
	graphics::Brush br;

	br.fill_color[0] = 0.0f;
	br.fill_color[1] = 0.0f;
	br.fill_color[2] = 0.0f;
	br.outline_opacity = 0.0f;

	graphics::drawDisk(pos_x, pos_y, 20, br);

	graphics::MouseState mouse;
	graphics::getMouseState(mouse);

	float x_coord = graphics::windowToCanvasX(mouse.cur_pos_x);
	float y_coord = graphics::windowToCanvasY(mouse.cur_pos_y);

	if (!hasFired) angle = find_angle(x_coord, y_coord);
	graphics::setOrientation(angle);

	drawRect(pos_x, pos_y, CANON_WIDTH, CANON_HEIGHT, br);
}

void Canon::init() {}

float Canon::find_angle(float x, float y)
{
	float origin_x = x - centerX;
	float origin_y = centerY - y;
	float res_tan = origin_y / origin_x;

	float rads = atan(origin_y / origin_x);
	float degs = rads * (180 / PI);

	if (abs(degs) < 12) degs = 13 * sgn(degs);
	return degs - 90;
}
