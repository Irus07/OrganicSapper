#include"Map.h"
#include <format>
#include<array>
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
		default: return MoveResult::Empty;
		}
	}

	void Map::SwitchFlag(unsigned x, unsigned y)
	{
		auto& cell = map_[y][x];
		if (cell.Status == CellStatus::Closed)
			cell.Status = CellStatus::Flag;
		else if (cell.Status == CellStatus::Flag)
			cell.Status = CellStatus::Closed;
		else {
			return;
		}

	}

	void Map::OpenAround(unsigned x, unsigned y)
	{
		for (size_t i = 0; i < 8; i++)
		{
			int tmpX = x + offsetX[i];
			int tmpY = y + offsetY[i];

			if (!(tmpY >= 0 && tmpY < map_.size()))
				continue;

			if (!(tmpX >= 0 && tmpX < map_[0].size()))
				continue;

			auto& tmpCell = map_[tmpY][tmpX];

			if (tmpCell.Type != CellType::Free || tmpCell.Status != CellStatus::Closed)
				continue;

			tmpCell.Status = CellStatus::Opened;

			OpenAround(tmpX, tmpY);
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
					IncrementAround(j, i);
			}
		}
	}

	void Map::IncrementAround(int x, int y)
	{
		//const std::array<int, 8> offsetX = { -1, -1, -1, 0, 1, 1, 1, 0 };
		//const std::array<int, 8> offsetY = { 1, 0, -1, -1, -1, 0, 1, 1 };

		auto& cell = map_[y][x];

		for (size_t i = 0; i < 8; i++)
		{
			int tmpX = x + offsetX[i];
			int tmpY = y + offsetY[i];

			if (!(tmpY >= 0 && tmpY < map_.size()))
				continue;

			if (!(tmpX >= 0 && tmpX < map_[0].size()))
				continue;


			auto& target = map_[tmpY][tmpX];

			if (target.Type == CellType::Bomb)
				continue;
						
			target.Type = CellType::Number;
			target.Value++;
		}
	}

}