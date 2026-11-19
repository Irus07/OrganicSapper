#include "Game.h"
#include "iostream"

sapper::Game::Game(unsigned lenX, unsigned lenY, unsigned bombs)
	:map_(lenX, lenY, bombs)
{
}

void sapper::Game::MakeMove(unsigned x, unsigned y)
{
	auto res = map_.MakeMove(x, y);
	std::cout << "Result : " << sapper::MoveRtoStr(res);

	map_.DrawMap();
}

void sapper::Game::NewGame(unsigned lenX, unsigned lenY, unsigned bombs)
{
	map_ = Map{ lenX,lenY, bombs };
}
