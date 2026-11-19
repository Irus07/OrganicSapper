#include"Map.h"
#include <iostream>

//TODO : добавить алгоритм раставления бимб

Map::Map(unsigned lenX, unsigned lenY, unsigned bombCount)
	:lenX_(lenX),
	lenY_(lenY),
	bombCount_(bombCount),
	map_(lenY, std::vector<Cell>(lenX))
{

}

void Map::DrawMap() const
{
	std::cout << "\t";

	for (size_t i = 0; i < lenY_; i++)
		std::cout << i << " ";

	for (size_t i = 0; i < lenX_; i++)
	{
		std::cout << i << "\t";

		for (size_t j = 0; j < lenY_; j++)
		{
			switch (map_[i][j].Status) {

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
