#include "Map.h"
#include "Game.h"
#include <iostream>

int main() {
	sapper::Game game{};

	while (true) {

		unsigned x, y;

		std::cout << "x : ";
		std::cin >> x ;

		std::cout << "y : ";
		std::cin >> y;

		game.MakeMove(x, y);

	}

}