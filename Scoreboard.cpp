#include "Scoreboard.hpp"

Scoreboard::Scoreboard(GameWindow* gw)
	: game_window(gw),
	  score1(0), score2(0),
	  x1(gw->width / 2 - gw->width / 10),
	  x2(gw->width / 2 + gw->width / 10),
	  y1(gw->height / 15),
	  y2(gw->height / 15),
	  font_size(gw->height / 8)
{
	update1();
	update2();
}

void Scoreboard::reset()
{
	score1 = score2 = 0;
}

void Scoreboard::update1()
{
	score1_string = std::make_shared<Text>(game_window, std::to_string(score1), x1, y1, font_size);
}

void Scoreboard::update2()
{
	score2_string = std::make_shared<Text>(game_window, std::to_string(score2), x2, y2, font_size);
}

void Scoreboard::render() const
{
	score1_string->render();
	score2_string->render();
	SDL_RenderPresent(game_window->renderer);
}

int& Scoreboard::operator[](const int& index)
{
	if (index == 0)
		return score1;
	else if (index == 1)
		return score2;
	else
		throw Error("Wrong index called in Scoreboard operator[]");	// std::range_error
}
