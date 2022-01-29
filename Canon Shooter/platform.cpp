#include "platform.h"
#include "sgg\graphics.h"
#include "config.h"

void Platform::update()
{
	float change = speed * graphics::getDeltaTime() / 10.0f;
	if (getKeyState(graphics::SCANCODE_LEFT))
		pos_x -= change;
	if (getKeyState(graphics::SCANCODE_RIGHT))
		pos_x += change;

	if (pos_x <= 0) pos_x = 0;
	if (pos_x >= CANVAS_WIDTH) pos_x = CANVAS_WIDTH;
}

void Platform::draw()
{
	graphics::Brush br;

	br.fill_color[0] = 0.0f;
	br.fill_color[1] = 0.0f;
	br.fill_color[2] = 0.0f;
	br.outline_opacity = 0.0f;

	graphics::resetPose();
	drawRect(pos_x, pos_y, PLATFORM_WIDTH, PLATFORM_HEIGHT, br);
}

void Platform::init()
{

}

void Platform::reset_coords()
{
	pos_x = CANVAS_WIDTH / 2;
	pos_y = CANVAS_HEIGHT - 20;
}

Coords Platform::get_coords()
{
	Coords coords;
	coords.x = pos_x;
	coords.y = pos_y;

	return coords;
}
