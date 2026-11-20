#pragma once

#include "Map.h"

namespace sapper {

	class Game
	{
	public:
		Game(unsigned lenX = 10, unsigned lenY = 10, unsigned bombs = 10);
		void TakeControl();
		
		void NewGame(unsigned lenX = 10, unsigned lenY = 10, unsigned bombs = 10);
	private:
		sapper::Map map_;
		void GameOver();
		void MakeMove(unsigned x, unsigned y);
		void MakeFlag(unsigned x, unsigned y);
		bool IsGameOver(MoveResult res);
		void OpenAround(unsigned x, unsigned y);
	};

}