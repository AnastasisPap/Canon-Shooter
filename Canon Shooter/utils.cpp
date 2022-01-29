#include "utils.h"
#include <iostream>
#include "config.h"
#include "random"
#include <ctime>

float degreesToRad(float degrees) { return abs(degrees) * PI / 180; }

int sgn(float x) { return (x >= 0 ? 1 : -1); }

float get_distance(Coords a, Coords b)
{
	return sqrt(pow((a.x - b.x), 2) + pow((a.y - b.y), 2));
}

bool collides(Coords ball, Rect_Information box_info)
{
	float max_distance_box = sqrt(pow((box_info.width / 2), 2) + pow((box_info.height/ 2), 2));
	float max_distance_ball = 5;
	if (get_distance(ball, box_info.coords) <= max_distance_ball + max_distance_box) return true;
	return false;
}

Coords get_random_coords()
{
	Coords coords;
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> dist_width(1, WINDOW_WIDTH);
	std::uniform_int_distribution<std::mt19937::result_type> dist_height(1, WINDOW_HEIGHT);
	coords.x = dist_width(rng);
	coords.y = dist_height(rng);

	return coords;
}

bool box_outside_window(Coords coords)
{
	float x = BOX_WIDTH / 2;
	float y = BOX_HEIGHT / 2;
	if (coords.x - x < 0 || coords.x + x > WINDOW_WIDTH) return true;
	if (coords.y - y < 50 || coords.y + y > WINDOW_HEIGHT - 128) return true;

	return false;
}

bool overlaps(Coords* a, Coords* b)
{
	Coords left_a = a[0];
	Coords right_a = a[1];
	Coords left_b = b[0];
	Coords right_b = b[1];

	if (left_a.x == right_a.x || left_a.y == right_a.y || left_b.x == right_b.x || left_b.y == right_b.y) return false;

	if (left_a.x >= right_b.x || left_b.x >= right_a.x) return false;
	if (right_a.y >= left_b.y || right_b.y >= left_a.y) return false;

	return true;
}

Coords* get_corners(Coords center)
{
	Coords* corners = new Coords[2];

	for (int i = 0; i < 2; i++)
	{
		corners[i].x = center.x - BOX_WIDTH / 2 * pow(-1, i);
		corners[i].y = center.y - BOX_HEIGHT / 2 * pow(-1, i);
	}

	return corners;
}