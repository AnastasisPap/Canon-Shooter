#include <sgg\graphics.h>
#include "ball.h"
#include "utils.h"
#include <iostream>

void Ball::update()
{
	float invert_x = (inverse == true ? 180 : 0);
	int mult = inverse == true ? -1 : 1;
	ball_x += speed * cos(degreesToRad(angle + invert_x)) * sgn(angle) * mult;
	ball_y -= speed * sin(degreesToRad(angle)) * mult;


	if (ball_x < 0) ball_x = 0;
	if (ball_x > WINDOW_WIDTH) ball_x = WINDOW_WIDTH;

	if (ball_y < 0) ball_y = 0;
	checkWall();
}

void Ball::checkWall()
{
	if (ball_x == 0 || ball_x == WINDOW_WIDTH) angle = abs(angle) * -1 * sgn(angle);
}

void Ball::draw()
{
	graphics::Brush br;
	br.fill_color[0] = 0.0f;
	br.fill_color[1] = 0.0f;
	br.fill_color[2] = 0.0f;
	br.outline_opacity = 0.0f;
	graphics::resetPose();
	drawDisk(ball_x, ball_y, BALL_RADIUS, br);
}

void Ball::set_angle(float angle) { this->angle = angle; }

void Ball::init() {}

Coords Ball::get_coords()
{
	Coords coords;
	coords.x = ball_x;
	coords.y = ball_y;

	return coords;
}
