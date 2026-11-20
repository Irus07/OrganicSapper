#include "Game.h"
#include "iostream"

sapper::Game::Game(unsigned lenX, unsigned lenY, unsigned bombs)
	:map_(lenX, lenY, bombs)
{
	map_.DrawMap();
}

void sapper::Game::MakeMove(unsigned x, unsigned y)
{
	auto res = map_.MakeMove(x, y);

	std::cout << "Result : " << sapper::MoveRtoStr(res) << std::endl;

	switch (res) {
	case MoveResult::Bomb: GameOver(); return;
	case MoveResult::Empty: map_.OpenAround(x, y); break;
	}

	map_.DrawMap();
	std::cout << std::endl;
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


