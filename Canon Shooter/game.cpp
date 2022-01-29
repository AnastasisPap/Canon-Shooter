#pragma warning(disable : 4996)
#include "sgg\graphics.h"
#include "config.h"
#include <string>
#include "game.h"
#include <iostream>
#include "stdio.h"
#include "utils.h"

void Game::create_boxes()
{
	if (!boxes && box_count <= 0)
	{
		boxes = new Box * [total_boxes];
		destroyed_boxes = new bool[total_boxes];

		for (int i = 0; i < total_boxes; i++)
		{
			boxes[i] = new Box();
			Coords coords = make_coords();
			boxes[i]->set_coords(coords);
			destroyed_boxes[i] = false;
			box_count += 1;
		}
	}
	initializedBoxes = true;
}

Coords Game::make_coords()
{
	Coords random_coords = get_random_coords();
	bool finished = false;
	while (!finished)
	{
		if (box_outside_window(random_coords)) {
			random_coords = get_random_coords();
			continue;
		}
		int i = 0;
		while (i < box_count)
		{
			if (overlaps(get_corners(boxes[i]->get_coords()), get_corners(random_coords)))
			{
				random_coords = get_random_coords();
				break;
			}
			i++;
		}
		if (i == box_count) finished = true;
		else random_coords = get_random_coords();
	}

	return random_coords;
}

bool Game::checkCollision(int index)
{
	if (!ball) return false;
	Coords ball_coords = ball->get_coords();

	Box* box = boxes[index];
	if (destroyed_boxes[index]) return false;
	Coords box_coords = box->get_coords();
	Rect_Information box_information;
	box_information.height = BOX_HEIGHT;
	box_information.width = BOX_WIDTH;
	box_information.coords = box_coords;
	if (collides(ball_coords, box_information)) return true;
	return false;
}

bool Game::check_if_hit_platform()
{
	Coords platform_coords = platform->get_coords();
	Coords ball_coords = ball->get_coords();
	Rect_Information box_information;
	box_information.height = PLATFORM_HEIGHT;
	box_information.width = PLATFORM_WIDTH;
	box_information.coords = platform_coords;
	if (collides(ball_coords, box_information) && ball_coords.y >= platform_coords.y) return true;

	return false;
}

void Game::update()
{
	if (!canon_initialized && graphics::getGlobalTime() > 500)
	{
		canon = new Canon();
		canon_initialized = true;
	}

	graphics::MouseState mouse;
	getMouseState(mouse);

	if (mouse.button_left_pressed && !ballThrown)
	{
		ball = new Ball();
		ball->set_angle(canon->get_angle() + 90);
		ballThrown = true;
		canon->set_fired(ballThrown);
	}

	if (box_count <= 0) create_boxes();
	if (boxes)
	{
		for (int i = 0; i < total_boxes; i++)
		{
			Box* box = *(boxes + i);
			if (box) box->update();
		}
	}

	if (ballThrown && ball)
	{
		if (platform == nullptr)
		{
			platform = new Platform();
		}
		platform->update();
		ball->update();
	}

	if (ball)
	{
		for (int i = 0; i < total_boxes; i++)
		{
			Coords ball_coords = ball->get_coords();
			if (ball_coords.y <= 0 || ball_coords.y >= WINDOW_HEIGHT)
			{
				ball->invert_direction();
				lives -= 1;
				this->~Game();
				break;
			}

			if (check_if_hit_platform() && !ball->upwards())
			{
				ball->invert_direction();
				break;
			}
			if (checkCollision(i))
			{
				graphics::playSound(std::string(ASSET_PATH) + "break.wav", 1.0f, false);
				ball->invert_direction();
				box_count -= 1;
				delete boxes[i];
				boxes[i] = nullptr;
				destroyed_boxes[i] = true;
				break;
			}
		}
	}
}

void Game::draw_lives()
{
	graphics::Brush br;
	br.outline_opacity = 0.0f;
	br.texture = std::string(ASSET_PATH) + "heart.png";

	for (int i = 0; i < lives; i++)
		drawRect(50 + 40 * i, CANVAS_HEIGHT - 50, 40, 40, br);
}

void Game::draw()
{
	graphics::Brush br;
	br.texture = std::string(ASSET_PATH) + "nebula.png";
	br.outline_opacity = 0.0f;

	float offset = CANVAS_HEIGHT * sinf(graphics::getGlobalTime() / 10000.0f) / 4;

	drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2 + offset, CANVAS_WIDTH, CANVAS_WIDTH, br);
	// Draw Player
	if (canon && box_count > 0 && !ballThrown && lives > 0)
	{
		draw_lives();
		canon->draw();
	}

	if (initializedBoxes && lives > 0)
	{
		for (int i = 0; i < total_boxes; i++)
		{
			Box* box = boxes[i];
			if (box != nullptr) box->draw();
		}
	}

	if (platform && ballThrown && lives > 0) platform->draw();

	if (ball && box_count > 0 && lives > 0) ball->draw();

	if (box_count == 0 || lives == 0)
	{
		graphics::setFont(std::string(ASSET_PATH) + "campus_a.ttf");
		const std::tuple<int, int, int> scores = read_data();
		graphics::resetPose();
		int nums[] = { std::get<0>(scores), std::get<1>(scores), std::get<2>(scores) };
		if (nums[index] < total_boxes - box_count)
		{
			if (nums[index] < total_boxes - box_count) nums[index] = total_boxes - box_count;
			drawText(100, CANVAS_HEIGHT / 2, 40, "NEW    RECORD!    You    destroyed    " + std::to_string(total_boxes - box_count) + "    boxes!", br);
		} else drawText(CANVAS_WIDTH / 3 - 100, CANVAS_HEIGHT / 2, 40, "You    destroyed    " + std::to_string(total_boxes - box_count) + "    boxes!", br);

		drawText(CANVAS_WIDTH / 3 - 60, CANVAS_HEIGHT / 2 + 50, 20, "Press    Y    to    play    again!    (ESC    to    exit)", br);
		this->~Game();

		if (getKeyState(graphics::SCANCODE_Y) || getKeyState(graphics::SCANCODE_ESCAPE)) store_data(nums);
		if (getKeyState(graphics::SCANCODE_Y))
		{
			play_again = true;
			reset_game();
		}
	}
}

void Game::init() {}

Game::Game() {}

Game::~Game()
{
	delete ball;
	delete canon;
	canon = nullptr;
	ball = nullptr;
	ballThrown = false;
	canon_initialized = false;
	platform->reset_coords();
}

void Game::reset_game()
{
	canon_initialized = false;
	ballThrown = false;
	box_count = 0;
	initializedBoxes = false;
	canon = nullptr;
	boxes = nullptr;
	ball = nullptr;
	platform = nullptr;
	destroyed_boxes = nullptr;
	lives = 3;
	total_boxes = 50;
}

void Game::store_data(int nums[])
{

	FILE* fp = fopen((std::string(DATA_PATH) + "scores.data").c_str(), "w");

	fprintf(fp, "%d %d %d", nums[0], nums[1], nums[2]);

	fclose(fp);
}

std::tuple<int, int, int> Game::read_data()
{
	std::tuple<int, int, int> scores;
	FILE* fp = fopen((std::string(DATA_PATH) + "scores.data").c_str(), "r");
	if (fp == nullptr) return std::make_tuple(0, 0, 0);

	int i = 0;
	int nums[3]{};
	int num;

	while (fscanf(fp, "%d", &num) == 1)
	{
		nums[i] = num;
		i++;
	}

	fclose(fp);
	scores = std::make_tuple(nums[0], nums[1], nums[2]);
	return scores;
}