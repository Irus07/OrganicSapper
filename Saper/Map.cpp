#include"Map.h"
#include <iostream>

namespace sapper {

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
		std::cout << " X\t";

		for (size_t i = 0; i < lenY_; i++)
			std::cout << i << " ";

		std::cout << "\nY\n";


		//i row j col
		for (size_t i = 0; i < lenY_; i++)
		{
			std::cout << i << "\t";

			for (size_t j = 0; j < lenX_; j++)
			{
				auto cell = map_[i][j];

				if (isDebug) {

					switch (cell.Type)
					{
					case CellType::Free:  std::cout << "f "; break;
					case CellType::Number:std::cout << cell.Value << " ";break;
					case CellType::Bomb: std::cout << "! "; break;
					}


					continue;
				}

				switch (cell.Status)
				{
				case CellStatus::Closed: std::cout << "# "; break;
				case CellStatus::Flag:  std::cout << "@ "; break;
				case CellStatus::Opened:
					switch (cell.Type)
					{
					case CellType::Free:  std::cout << "  "; break;
					case CellType::Bomb:  std::cout << "* "; break;
					case CellType::Number:std::cout << cell.Value << " ";break;
					}
					break;
				}
			}

			std::cout << std::endl;
		}
	}

	MoveResult Map::MakeMove(unsigned x, unsigned y)
	{
		// y row x col

		auto& cell = map_[y][x];

		if (cell.Status != CellStatus::Closed)
			return MoveResult::Invalid;

		cell.Status = CellStatus::Opened;

		switch (cell.Type) {
		case CellType::Bomb: return MoveResult::Bomb;
		case CellType::Number: return MoveResult::Number;
		default: return MoveResult::None;
		}
	}

	// y - row x col

	void Map::PlaceBombs()
	{
		for (int i = 0; i < bombCount_; i++)
		{
			unsigned x, y;
			do {
				x = rand() % lenX_;
				y = rand() % lenY_;
			} while (map_[y][x].Type != CellType::Free);

			map_[y][x].Type = CellType::Bomb;
		}
	}

	void Map::PlaceNums()
	{
		// i row j col
		for (int i = 0; i < lenY_; i++)
		{
			for (int j = 0; j < lenX_; j++)
			{
				if (map_[i][j].Type == CellType::Bomb)
					IncrementAround(i, j);
			}
		}
	}

	void Map::IncrementAround(int x, int y)
	{

	}

}