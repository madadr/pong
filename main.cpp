#include "GameWindow.hpp"
#include <fstream>

int main(int argc, char** argv)
{
	GameWindow game(1200, 600, 15);
	game.play();

	return 0;
}
