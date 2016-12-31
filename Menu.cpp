#include "Menu.hpp"


Menu::Menu(GameWindow* gw)
	: position{std::make_pair<int, int>(gw->width / 2 - gw->width / 15, 3 * gw->height / 7) ,
		  std::make_pair<int, int>(gw->width / 2 + gw->width / 15, 3 * gw->height / 7) ,
		  std::make_pair<int, int>(gw->width / 2 - gw->width / 15, 4 * gw->height / 7) ,
		  std::make_pair<int, int>(gw->width / 2 + gw->width / 15, 4 * gw->height / 7) ,
		  std::make_pair<int, int>(gw->width / 2 - gw->width / 15, 5 * gw->height / 7) ,
		  std::make_pair<int, int>(gw->width / 2 + gw->width / 15, 5 * gw->height / 7) ,
		  std::make_pair<int, int>(gw->width / 2 - gw->width / 15, 6 * gw->height / 7) ,
		  std::make_pair<int, int>(gw->width / 2 + gw->width / 15, 6 * gw->height / 7)
	  },
	  game_window(gw),
	  font_size(game_window->height / 20)
{
	init_startup_strings();
	init_info_strings();
	init_paused_strings();
	init_win_strings();
}

void Menu::init_startup_strings()
{
	// create startup strings
	start = std::make_unique<Text>(game_window, std::string("START"), position[LEFT2].first, position[LEFT2].second, font_size);
	start_key = std::make_unique<Text>(game_window, std::string("PRESS S"), position[RIGHT2].first, position[RIGHT2].second, font_size);

	info = std::make_unique<Text>(game_window, std::string("INFO"), position[LEFT3].first, position[LEFT3].second, font_size);
	info_key = std::make_unique<Text>(game_window, std::string("PRESS I"), position[RIGHT3].first, position[RIGHT3].second, font_size);
}

void Menu::init_info_strings()
{
	// create info strings
	player1_up = std::make_unique<Text>(game_window, std::string("UP A"), position[LEFT1].first, position[LEFT1].second, font_size);
	player1_down = std::make_unique<Text>(game_window, std::string("DOWN Z"), position[LEFT2].first, position[LEFT2].second, font_size);

	player2_up = std::make_unique<Text>(game_window, std::string("UP /\\"), position[RIGHT1].first, position[RIGHT1].second, font_size);
	player2_down = std::make_unique<Text>(game_window, std::string("DOWN \\/"), position[RIGHT2].first, position[RIGHT2].second, font_size);

	pause = std::make_unique<Text>(game_window, std::string("PAUSE"), position[LEFT3].first, position[LEFT3].second, font_size);
	pause_key = std::make_unique<Text>(game_window, std::string("PRESS P"), position[RIGHT3].first, position[RIGHT3].second, font_size);

	back = std::make_unique<Text>(game_window, std::string("BACK"), position[LEFT4].first, position[LEFT4].second, font_size);
	back_key = std::make_unique<Text>(game_window, std::string("PRESS B"), position[RIGHT4].first, position[RIGHT4].second, font_size);
}

void Menu::init_paused_strings()
{
	game = std::make_unique<Text>(game_window, std::string("GAME"), position[LEFT1].first, position[LEFT1].second, 1.5 * font_size);
	paused = std::make_unique<Text>(game_window, std::string("PAUSED"), position[RIGHT1].first, position[RIGHT1].second, 1.5 * font_size);

	unpause = std::make_unique<Text>(game_window, std::string("CONTINUE"), position[LEFT2].first, position[LEFT2].second, font_size);
	unpause_key = std::make_unique<Text>(game_window, std::string("PRESS P"), position[RIGHT2].first, position[RIGHT2].second, font_size);
}

void Menu::init_win_strings()
{
	win1 = std::make_unique<Text>(game_window, std::string("WIN!"), position[LEFT1].first, position[LEFT1].second, 1.5 * font_size);
	win2 = std::make_unique<Text>(game_window, std::string("WIN!"), position[RIGHT1].first, position[RIGHT1].second, 1.5 * font_size);

	restart = std::make_unique<Text>(game_window, std::string("RESTART"), position[LEFT3].first, position[LEFT3].second, font_size);
	restart_key = std::make_unique<Text>(game_window, std::string("RESTART R"), position[RIGHT3].first, position[RIGHT3].second, font_size);

	back_to_menu = std::make_unique<Text>(game_window, std::string("BACK TO MENU"), position[LEFT4].first, position[LEFT4].second, font_size);
}

void Menu::render_win() const
{
	restart->render();
	restart_key->render();
	back_to_menu->render();
	back_key->render();
	SDL_RenderPresent(game_window->renderer);
}

void Menu::render_startup() const
{
	start->render();
	start_key->render();
	info->render();
	info_key->render();
	SDL_RenderPresent(game_window->renderer);
}

void Menu::render_info() const
{
	player1_up->render();
	player1_down->render();
	player2_up->render();
	player2_down->render();
	pause->render();
	pause_key->render();
	back->render();
	back_key->render();
	SDL_RenderPresent(game_window->renderer);
}

void Menu::render_pause() const
{
	game->render();
	paused->render();
	unpause->render();
	unpause_key->render();
	SDL_RenderPresent(game_window->renderer);
}

void Menu::render_win1() const
{
	win1->render();
	render_win();
}

void Menu::render_win2() const
{
	win2->render();
	render_win();
}
