#pragma once
#include "config.h"

class Difficulty
{
	int difficulty = -1;
	int get_selection();
	bool finished = false;
public:
	Difficulty();
	void draw();
	int get_difficulty() { return difficulty; }
	bool has_finished() { return finished; }
};