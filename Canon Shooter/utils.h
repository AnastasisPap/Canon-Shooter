#pragma once

float degreesToRad(float degrees);

int sgn(float x);

struct Coords
{
	int x;
	int y;
};

struct Rect_Information
{
	int height;
	int width;
	Coords coords;
};

float get_distance(Coords a, Coords b);
Coords get_random_coords();
bool box_outside_window(Coords coords);
Coords* get_corners(Coords center);
bool overlaps(Coords* a, Coords* b);
bool collides(Coords ball, Rect_Information);
void wait_seconds(float seconds);