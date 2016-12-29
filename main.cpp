#include "GameWindow.hpp"
#include <fstream>

int main(int argc, char** argv)
{
	std::fstream log("ping_pong.log", std::ios_base::out | std::ios_base::trunc);
	std::streambuf* logbuf = log.rdbuf();
	std::cerr.rdbuf(logbuf);

	GameWindow game(600, 400, 5);
	game.play();

	std::cerr.rdbuf(nullptr);
	return 0;
}
