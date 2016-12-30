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
}

void Menu::init_startup_strings()
{
	// create startup strings
	start = std::make_shared<Text>(game_window, std::string("START"), position[LEFT2].first, position[LEFT2].second, font_size);
	start_key = std::make_shared<Text>(game_window, std::string("PRESS S"), position[RIGHT2].first, position[RIGHT2].second, font_size);

	info = std::make_shared<Text>(game_window, std::string("INFO"), position[LEFT3].first, position[LEFT3].second, font_size);
	info_key = std::make_shared<Text>(game_window, std::string("PRESS I"), position[RIGHT3].first, position[RIGHT3].second, font_size);
}

void Menu::init_info_strings()
{
	// create info strings
	player1_up = std::make_shared<Text>(game_window, std::string("UP A"), position[LEFT1].first, position[LEFT1].second, font_size);
	player1_down = std::make_shared<Text>(game_window, std::string("DOWN Z"), position[LEFT2].first, position[LEFT2].second, font_size);

	player2_up = std::make_shared<Text>(game_window, std::string("UP /\\"), position[RIGHT1].first, position[RIGHT1].second, font_size);
	player2_down = std::make_shared<Text>(game_window, std::string("DOWN \\/"), position[RIGHT2].first, position[RIGHT2].second, font_size);

	back = std::make_shared<Text>(game_window, std::string("BACK"), position[LEFT3].first, position[LEFT3].second, font_size);
	back_key = std::make_shared<Text>(game_window, std::string("PRESS B"), position[RIGHT3].first, position[RIGHT3].second, font_size);
}

void Menu::render_startup()
{
	start->render();
	start_key->render();
	info->render();
	info_key->render();
}

void Menu::render_info()
{
	player1_up->render();
	player1_down->render();
	player2_up->render();
	player2_down->render();
	back->render();
	back_key->render();
}
