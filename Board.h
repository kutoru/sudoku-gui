#pragma once

#include "db.h"

enum class BoardType {None, Solved, Original, Level};

char convBoardType(BoardType type);
BoardType convBoardType(char type);

class Board {
private:
	int gameId;
	int size;
	BoardType type;
	char* board;
public:
	Board();

	std::string ToString();
	void FromString(const char* str);
	void SetGameId(int gameId);
	static Board* LoadFromDB(int gameId, BoardType boardType);

	// need revision
	Board(int size, BoardType type);
	void Initialize(char initializeWith);
	void Print();
	char& get(int row, int col);
	void operator=(Board& oldBoard);
	~Board();
};
