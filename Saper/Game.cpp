#include "Game.h"
#include "iostream"
#include <string>

sapper::Game::Game(unsigned lenX, unsigned lenY, unsigned bombs)
	:map_(lenX, lenY, bombs)
{
	map_.DrawMap();
}

void sapper::Game::TakeControl()
{
	unsigned x{}, y{};
	char c{};
	std::string sx, sy, sc;

	while (true) {
		std::cout << "Format : action[f - flag/any str - move] pointX pointY" << std::endl;
		std::cin >> sc >> sx >> sy;

		try
		{
			x = std::stoi(sx);
			y = std::stoi(sy);
			c = sc[0];
		}
		catch (std::exception ex) {
			std::cout << "Incorrect input : try again " << std::endl << std::endl;
			continue;
		}

		std::cout << std::endl;

		if (c == 'f')
			MakeFlag(x, y);
		else
			MakeMove(x, y);

		map_.DrawMap();
		std::cout << std::endl;
	}
}

void sapper::Game::MakeMove(unsigned x, unsigned y)
{
	auto res = map_.MakeMove(x, y);

	std::cout << "Result : " << sapper::MoveRtoStr(res) << std::endl;

	switch (res) {
	case MoveResult::Bomb: GameOver(); return;
	case MoveResult::Empty: map_.OpenAround(x, y); break;
	}

}

void sapper::Game::MakeFlag(unsigned x, unsigned y)
{

}

void sapper::Game::NewGame(unsigned lenX, unsigned lenY, unsigned bombs)
{
	map_ = Map{ lenX,lenY, bombs };
}

void sapper::Game::GameOver()
{

	map_.DrawMap();

	std::cout << "\n=========================================" << std::endl;
	std::cout << "\t\tYou lose" << std::endl;
	std::cout << "=========================================" << std::endl;

	exit(0);
}

bool sapper::Game::IsGameOver(MoveResult res)
{
	if (res == MoveResult::Bomb)
		return true;

	return false;
}


