#pragma once

#include "Validation.h"
#include "date.h"
//#include <vector>
#include <chrono>
#include <random>
//#include <math.h>

enum class Difficulty {None, Easy, Medium, Hard};
enum class CompletedStatus {No, Yes, Gaveup};

char convDiff(Difficulty diff);
Difficulty convDiff(char diff);
char convCompStat(CompletedStatus status);
CompletedStatus convCompStat(char status);

class Game {
public:
	static char totalChars[16];

	int id;
	int userId;
	char emptyChar;
	Difficulty difficulty;
	int size;
	Board* solvedBoard;
	Board* origBoard;
	Board* lvlBoard;
	std::default_random_engine gen;
	int* squareLayouts;
	double removePercentage;
	int removeAmount;
	date dateCreated;
	CompletedStatus completed;

	Game();
	Game(int size, Difficulty difficulty, int userId);

	static int* GenerateSquareLayouts(int size);
	static void AddToDatabase(Game*& game);
	static int GetMaxId();
	static Game* LoadFromDB(int gameId);
	static void SaveGame(Game* game);
	static void DeleteFromDB(int gameId);
	static bool ExistsInDB(int gameId);

	void LoadNewGameToDB();
	void SolveLevel();

	// need revision
	int FindSquareIndex(int row, int col);
	char* GetFirstEmpty(int& row, int& col);
	void GetNextEmptyIndex(int& startRow, int& startCol);
	bool ValidateRow(char inserted, int row, int col, BoardType boardType);
	bool ValidateCol(char inserted, int row, int col, BoardType boardType);
	bool ValidateSqr(char inserted, int row, int col, BoardType boardType);
	void ValidateRow(Validation& validation);
	void ValidateSqr(Validation& validation);
	void ValidateCol(Validation& validation);
	bool GenerateNewBoard(System::ComponentModel::BackgroundWorker^ w, System::ComponentModel::DoWorkEventArgs^ e);
	void GenerateLevel();

	Validation ValidateLocation(char inserted, int row, int col, BoardType boardType = BoardType::Level);
	Validation ValidateLevel();
	void ResetLevel();
	void Print(BoardType boardType = BoardType::Level);
	void SetChar(int row, int col, char ch);
	char GetChar(int row, int col);
	bool CharIsReplaceable(int row, int col);
	~Game();
};
