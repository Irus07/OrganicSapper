#pragma once

#include <vector>
#include <array>
#include <string>

namespace sapper {


	enum class CellType { Free, Bomb, Number, };
	enum class CellStatus { Closed, Opened, Flag, };
	enum class MoveResult { Bomb, Number, Empty, Invalid };

	static inline std::string MoveRtoStr(MoveResult res) {
		switch (res) {
		case MoveResult::Bomb: return "Bomb ";
		case MoveResult::Number:return "Number ";
		case MoveResult::Empty: return "None ";
		}
		return "Invalid";
	}

	struct Cell
	{
		CellStatus Status;
		CellType Type;
		unsigned Value;
	};

	class Map
	{
	public:
		Map(unsigned lenX, unsigned lenY, unsigned bombCount);

		unsigned GetLenX() const { return lenX_; };
		unsigned GetLenY() const { return lenY_; };

		void DrawMap(bool isDebug = false) const;
		MoveResult MakeMove(unsigned x, unsigned y);
		void SwitchFlag(unsigned x, unsigned y);
		void OpenAround(unsigned x, unsigned y);

	private:
		static inline const std::array<int, 8> offsetX = { -1, -1, -1, 0, 1, 1, 1, 0 };
		static inline const std::array<int, 8> offsetY = { 1, 0, -1, -1, -1, 0, 1, 1 };

		unsigned lenX_, lenY_, bombCount_;
		std::vector<std::vector<Cell>> map_;
		void CheckMove();
		void PlaceBombs();
		void PlaceNums();
		void IncrementAround(int x, int y);
	};

}