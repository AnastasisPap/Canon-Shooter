#pragma once
#include "canon.h"
#include "box.h"
#include "ball.h"
#include "platform.h"

class Game
{
	Canon* canon = nullptr;
	Box** boxes = nullptr;
	Ball* ball = nullptr;
	Platform* platform = nullptr;
	bool canon_initialized = false;
	void create_boxes();
	bool checkCollision(int index);
	bool ballThrown = false;
	int box_count = 0;
	bool initializedBoxes = false;
	bool* destroyed_boxes = nullptr;
	int lives = 3;
	int total_boxes = 50;
	Coords make_coords();
	bool check_if_hit_platform();
	void draw_lives();
	bool play_again = false;
	void reset_game();
	void store_data(int nums[]);
	std::tuple<int, int, int> read_data();
	int index = 0;
public:
	void update();
	void draw();
	void init();
	bool isBallThrown() { return ballThrown; }
	void set_lives(int lives) { this->lives = lives; }
	void set_box_number(int boxes) { total_boxes = boxes; box_count = boxes; }
	bool get_play_again() { return play_again; }
	void will_play_again() { play_again = false; }
	void set_index(int index) { this->index = index; }
	Game();
	~Game();
};