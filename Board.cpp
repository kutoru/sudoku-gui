#include "Board.h"

char convBoardType(BoardType type) {
	if (type == BoardType::None) {
		return 'N';
	}
	else if (type == BoardType::Solved) {
		return 'S';
	}
	else if (type == BoardType::Original) {
		return 'O';
	}
	else if (type == BoardType::Level) {
		return 'L';
	}
	else {
		throw exep("Unknown board type");
	}
}

BoardType convBoardType(char type) {
	if (type == 'N') {
		return BoardType::None;
	}
	else if (type == 'S') {
		return BoardType::Solved;
	}
	else if (type == 'O') {
		return BoardType::Original;
	}
	else if (type == 'L') {
		return BoardType::Level;
	}
	else {
		throw exep("Unknown board type");
	}
}

Board::Board() {}

std::string Board::ToString() {
	std::string newStr(size * size, '\0');
	for (int i = 0; i < size * size; i++) {
		newStr[i] = board[i];
	}
	return newStr;
}

void Board::FromString(const char* str) {
	if (board != nullptr) {
		delete[] board;
	}

	board = new char[size * size];

	try {
		for (int i = 0; i < size * size; i++) {
			board[i] = str[i];
		}
	}
	catch (std::exception& e) {
		delete[] board;
		throw e;
	}
}

void Board::SetGameId(int gameId) {
	this->gameId = gameId;
}

Board* Board::LoadFromDB(int gameId, BoardType boardType) {
	db.query << "select * from boards where `game_id` = " << gameId << " and `board_type` = '" << convBoardType(boardType) << "';";
	db.load_res();

	auto row = db.get_row();
	Board* board = nullptr;

	if (row) {
		board = new Board();
		board->board = nullptr;

		board->gameId = gameId;
		board->size = atoi(row[1]);
		board->type = boardType;
		board->FromString(row[3]);
		//board->board = row[3];
	}
	else {
		throw exep("Coulnd't load the board from the db");
	}

	return board;
}

Board::Board(int size, BoardType type) {
	this->size = size;
	this->type = type;
	this->board = new char[size * size];
}

void Board::Initialize(char initializeWith) {
	for (int i = 0; i < size * size; i++) {
		board[i] = initializeWith;
	}
}

void Board::Print() {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			logl(get(i, j));
			logl(' ');
		}
		logl('\n');
	}
}

char& Board::get(int row, int col) {  // this returns a REFERENCE to board[row][col]
	if ((row < 0 || row >= size) || ((col < 0 || col >= size))) {
		throw exep("Board index is out of range");
	}

	return board[row * size + col];
}

void Board::operator=(Board& newBoard) {
	if (size != newBoard.size) {
		throw exep("Board sizes do not match");
	}

	for (int i = 0; i < size * size; i++) {
		board[i] = newBoard.board[i];
	}
}

Board::~Board() {
	if (board != nullptr) {
		delete[] board;
	}
}
