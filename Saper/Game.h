#pragma once

#include "Map.h"

namespace sapper {

	class Game
	{
	public:
		Game(unsigned lenX = 10, unsigned lenY = 10, unsigned bombs = 10);
		void MakeMove(unsigned x, unsigned y);
		void NewGame(unsigned lenX = 10, unsigned lenY = 10, unsigned bombs = 10);
	private:
		sapper::Map map_;
		void GameOver();
		bool IsGameOver(MoveResult res);
	};

}