#include"Map.h"
#include <iostream>

//TODO : добавить алгоритм раставления бимб

Map::Map(unsigned lenX, unsigned lenY, unsigned bombCount)
	:lenX_(lenX),
	lenY_(lenY),
	bombCount_(bombCount),
	map_(lenY, std::vector<Cell>(lenX))
{
	PlaceBombs();
	PlaceNums();
}

void Map::DrawMap(bool isDebug) const
{
	std::cout << "\t";

	for (size_t i = 0; i < lenY_; i++)
		std::cout << i << " ";

	std::cout << "\n\n";

	for (size_t i = 0; i < lenX_; i++)
	{
		std::cout << i << "\t";

		for (size_t j = 0; j < lenY_; j++)
		{
			if (isDebug) {

				switch (map_[i][j].Type)
				{
				case CellType::Free:  std::cout << "f "; break;
				case CellType::Number:std::cout << map_[i][j].Value << " ";break;
				case CellType::Bomb: std::cout << "! "; break;
				}


				continue;
			}

			switch (map_[i][j].Status)
			{
			case CellStatus::Closed: std::cout << "# "; break;
			case CellStatus::Flag:  std::cout << "@ "; break;
			case CellStatus::Opened:
				switch (map_[i][j].Type)
				{
				case CellType::Free:  std::cout << "  "; break;
				case CellType::Number:std::cout << map_[i][j].Value << " ";break;
				}
				break;
			}
		}

		std::cout << std::endl;
	}
}

void Map::PlaceBombs()
{
	for (int i = 0; i < bombCount_; i++)
	{
		unsigned x, y;
		do {
			x = rand() % lenX_;
			y = rand() % lenY_;
		} while (map_[x][y].Type != CellType::Free);

		map_[x][y].Type = CellType::Bomb;
	}
}

void Map::PlaceNums()
{
	for (int i = 0; i < lenX_; i++)
	{
		for (int j = 0; j < lenY_; j++)
		{
			if (map_[i][j].Type == CellType::Bomb)
				IncrementAround(i, j);
		}
	}
}

void Map::IncrementAround(int x, int y)
{
	
}

