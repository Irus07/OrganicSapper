#pragma once

class Map
{
public:
	Map(unsigned short lenX, unsigned short lenY, unsigned short bombCount);

	unsigned short LenX;
	unsigned short LenY;
	unsigned short BombCount;

	void DrawMap() const;
	MoveResult MakeMove(unsigned int x , unsigned int y);

private:
	void CheckMove();
};

enum MoveResult
{
	Bomb,
	Number,
	None
};