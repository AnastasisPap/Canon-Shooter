#include "chooseDifficulty.h"
#include "sgg\graphics.h"

int starting_selection = 0;
bool key_pressed = true;

Difficulty::Difficulty()
{
}

void draw_active(float text_pos_x, float pos_y, std::string text)
{
	graphics::Brush br;
	br.fill_color[0] = 1.0f;
	br.fill_color[1] = 0.0f;
	br.fill_color[2] = 0.0f;
	drawRect(CANVAS_WIDTH / 2, pos_y, 300, 50, br);
	br.fill_color[0] = 1.0f;
	br.fill_color[1] = 1.0f;
	br.fill_color[2] = 1.0f;
	drawText(text_pos_x, pos_y + 13, 40, text, br);
}

void draw_unselected(float text_pos_x, float pos_y, std::string text)
{
	graphics::Brush br;
	br.fill_color[0] = 1.0f;
	br.fill_color[1] = 1.0f;
	br.fill_color[2] = 1.0f;
	drawRect(CANVAS_WIDTH / 2, pos_y, 300, 50, br);
	br.fill_color[0] = 1.0f;
	br.fill_color[1] = 0.0f;
	br.fill_color[2] = 0.0f;
	drawText(text_pos_x, pos_y + 13, 40, text, br);
}

void Difficulty::draw()
{
	graphics::Brush br;
	br.outline_opacity = 0.0f;
	graphics::setFont(std::string(ASSET_PATH) + "campus_a.ttf");
	drawText(CANVAS_WIDTH / 3 + 20, 50, 20, "Choose    your    difficulty	level:", br);

	if (!getKeyState(graphics::SCANCODE_DOWN) && !getKeyState(graphics::SCANCODE_UP)) key_pressed = true;

	if (getKeyState(graphics::SCANCODE_DOWN) && key_pressed)
	{
		starting_selection++;
		key_pressed = false;
	}
	if (getKeyState(graphics::SCANCODE_UP) && key_pressed)
	{
		starting_selection--;
		key_pressed = false;
	}
	if (starting_selection <= 0) starting_selection = 0;
	else if (starting_selection >= 2) starting_selection = 2;

	int all_text_pos_x[] = { CANVAS_WIDTH / 2 - 60 , CANVAS_WIDTH / 2 - 85, CANVAS_WIDTH / 3 + 90 };
	int all_pos_y[] = { 100, 200, 300 };
	std::string all_text[] = { "Easy", "Medium", "Difficult" };

	for (int i = 0; i < 3; i++)
	{
		if (i == starting_selection) draw_active(all_text_pos_x[i], all_pos_y[i], all_text[i]);
		else draw_unselected(all_text_pos_x[i], all_pos_y[i], all_text[i]);
	}

	if (getKeyState(graphics::SCANCODE_RETURN))
		difficulty = starting_selection;
}
