#include <iostream>

#include "sgg\graphics.h"
#include "game.h"
#include "config.h"
#include "chooseDifficulty.h"

bool initialized = false;
int difficulty_index = -1;

void update(float ms)
{
	Game* game = reinterpret_cast<Game*>(graphics::getUserData());
	game->update();
}

void draw()
{
	graphics::Brush br;
	br.texture = std::string(ASSET_PATH) + "nebula.png";
	br.outline_opacity = 0.0f;

	float offset = CANVAS_HEIGHT * sinf(graphics::getGlobalTime() / 10000.0f) / 4;

	drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2 + offset, CANVAS_WIDTH, CANVAS_WIDTH, br);
	if (difficulty_index != -1)
	{
		Game* game = reinterpret_cast<Game*>(graphics::getUserData());
		if (initialized == false)
		{
			int lives[] = { 10, 5, 3 };
			int total_boxes[] = { 50, 35, 20 };
			game->set_lives(lives[difficulty_index]);
			game->set_box_number(total_boxes[difficulty_index]);
			game->set_index(difficulty_index);
			initialized = true;
		}
		game->draw();
		if(game->get_play_again())
		{
			initialized = false;
			difficulty_index = -1;
			game->will_play_again();
		}
	} else
	{
		Difficulty* difficulty = new Difficulty();
		difficulty->draw();
		difficulty_index = difficulty->get_difficulty();
		if (difficulty_index != -1) delete difficulty;
	}
}

int main(int argc, char** argv)
{
	Game game;
	graphics::createWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Box Destroyer");

	graphics::setUserData(&game);

	graphics::setDrawFunction(draw);
	graphics::setUpdateFunction(update);

	graphics::setCanvasSize(CANVAS_WIDTH, CANVAS_HEIGHT);
	setCanvasScaleMode(graphics::CANVAS_SCALE_FIT);

	graphics::startMessageLoop();

	return 0;
}