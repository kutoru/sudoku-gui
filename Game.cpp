#include "Game.h"

char convDiff(Difficulty diff) {
	if (diff == Difficulty::Easy) {
		return 'E';
	}
	else if (diff == Difficulty::Medium) {
		return 'M';
	}
	else if (diff == Difficulty::Hard) {
		return 'H';
	}
	else {
		throw exep("Unknown difficulty");
	}
}

Difficulty convDiff(char diff) {
	if (diff == 'E') {
		return Difficulty::Easy;
	}
	else if (diff == 'M') {
		return Difficulty::Medium;
	}
	else if (diff == 'H') {
		return Difficulty::Hard;
	}
	else {
		throw exep("Unknown difficulty");
	}
}

char convCompStat(CompletedStatus status) {
	if (status == CompletedStatus::No) {
		return 'N';
	}
	else if (status == CompletedStatus::Yes) {
		return 'Y';
	}
	else if (status == CompletedStatus::Gaveup) {
		return 'G';
	}
	else {
		throw exep("Unknown CompletedStatus");
	}
}

CompletedStatus convCompStat(char status) {
	if (status == 'N') {
		return CompletedStatus::No;
	}
	else if (status == 'Y') {
		return CompletedStatus::Yes;
	}
	else if (status == 'G') {
		return CompletedStatus::Gaveup;
	}
	else {
		throw exep("Unknown CompletedStatus");
	}
}

char Game::totalChars[16] = {
	'1', '2', '3', '4',  // 4
	'5', '6', '7', '8', '9',  // 9
	'A', 'B', 'C', 'D', 'E', 'F', 'G'  // 16
};

Game::Game() {}

Game::Game(int size, Difficulty difficulty, int userId) {
	if (size != 4 && size != 9 && size != 16) {
		throw exep("Invalid board size");
	}

	this->id = -1;
	this->emptyChar = '0';
	this->userId = userId;
	this->difficulty = difficulty;
	this->size = size;
	
	dateCreated = date();
	completed = CompletedStatus::No;

	solvedBoard = new Board(size, BoardType::Solved);
	origBoard = new Board(size, BoardType::Original);
	lvlBoard = new Board(size, BoardType::Level);

	solvedBoard->Initialize(emptyChar);

	int rngSeed = std::chrono::system_clock::now().time_since_epoch().count();
	gen = std::default_random_engine(rngSeed);

	squareLayouts = GenerateSquareLayouts(size);
}

void Game::LoadNewGameToDB() {
	id = GetMaxId() + 1;
	solvedBoard->SetGameId(id);
	origBoard->SetGameId(id);
	lvlBoard->SetGameId(id);

	Game* game = this;
	AddToDatabase(game);
}

int* Game::GenerateSquareLayouts(int size) {
	int* squareLayouts = new int[size * size * 2];
	int sqrSize = std::sqrt(size);
	int sqrIdx, pairIdx, pairStartIdx;

	for (int row = 0; row < sqrSize; row++) {
		for (int col = 0; col < sqrSize; col++) {
			for (int sqrRow = 0; sqrRow < sqrSize; sqrRow++) {
				for (int sqrCol = 0; sqrCol < sqrSize; sqrCol++) {
					sqrIdx = row * sqrSize + col;
					pairIdx = sqrRow * sqrSize + sqrCol;
					pairStartIdx = (sqrIdx * size * 2) + (pairIdx * 2);
					squareLayouts[pairStartIdx] = sqrRow + (row * sqrSize);
					squareLayouts[pairStartIdx + 1] = sqrCol + (col * sqrSize);
				}
			}
		}
	}

	return squareLayouts;
}

void Game::AddToDatabase(Game*& game) {
	int id = game->id;
	int userId = game->userId;
	char emptyChar = game->emptyChar;
	char diff = convDiff(game->difficulty);
	std::string size = std::to_string(game->size);
	double rmvPrc = game->removePercentage;
	int rmvMnt = game->removeAmount;
	std::string slvdBrd = game->solvedBoard->ToString();
	std::string origBrd = game->origBoard->ToString();
	std::string lvlBrd = game->lvlBoard->ToString();

	// ideally i would want to insert everything at the same time, but it doesn't fucking work that way
	db.query << "insert into games(`id`, `user_id`, `empty_char`, `difficulty`, `size`, `remove_percentage`, `remove_amount`, `date_created`) " <<
		"values(" << id << ", " << userId << ", '" << emptyChar << "', '" << diff << "', '" << size << "', " << rmvPrc << ", " << rmvMnt << ", " << "now());";
	db.load_res();
	db.query << "insert into boards(`game_id`, `size`, `board_type`, `board`) " <<
		"values(" << id << ", '" << size << "', 'S', '" << slvdBrd << "');";
	db.load_res();
	db.query << "insert into boards(`game_id`, `size`, `board_type`, `board`) " <<
		"values(" << id << ", '" << size << "', 'O', '" << origBrd << "');";
	db.load_res();
	db.query << "insert into boards(`game_id`, `size`, `board_type`, `board`) " <<
		"values(" << id << ", '" << size << "', 'L', '" << lvlBrd << "');";
	db.load_res();

	id = GetMaxId();
	if (id != game->id) {
		throw exep("Couldn't find the created game in the database, it probably failed to add");
	}
}

int Game::GetMaxId() {
	int id = 0;

	db.query << "select max(`id`) from games;";
	db.load_res();
	auto row = db.get_row();
	if (row[0]) {
		id = atoi(row[0]);
	}

	return id;
}

Game* Game::LoadFromDB(int gameId) {
	db.query << "select * from games where `id` = " << gameId << ";";
	db.load_res();

	auto row = db.get_row();
	Game* game = nullptr;

	if (row) {
		try {
			game = new Game();
			game->solvedBoard = nullptr;
			game->origBoard = nullptr;
			game->lvlBoard = nullptr;
			game->squareLayouts = nullptr;

			game->id = gameId;
			game->userId = atoi(row[1]);
			game->emptyChar = *row[2];
			game->size = atoi(row[3]);
			game->difficulty = convDiff(*row[4]);
			game->removePercentage = std::stod(row[5]);
			game->removeAmount = atoi(row[6]);
			game->dateCreated = date::to_date(row[7]);
			game->completed = convCompStat(*row[8]);

			game->solvedBoard = Board::LoadFromDB(gameId, BoardType::Solved);
			game->origBoard = Board::LoadFromDB(gameId, BoardType::Original);
			game->lvlBoard = Board::LoadFromDB(gameId, BoardType::Level);
			game->squareLayouts = Game::GenerateSquareLayouts(game->size);
		}
		catch (std::exception& e) {
			delete game;
			throw e;
		}
	}
	else {
		throw exep("Couldn't load the game from the db");
	}

	return game;
}

void Game::SaveGame(Game* game) {
	db.query << "update boards set `board` = '" << game->lvlBoard->ToString() << "' where `game_id` = " << game->id << " and `board_type` = 'L';";
	db.load_res();

	if (db.res) {  // yes, apparently if db.res is not NULL than something went wrong
		throw exep("Couldn't update a board");
	}

	if (game->completed == CompletedStatus::Yes || game->completed == CompletedStatus::Gaveup) {
		db.query << "update games set `completed` = '" << convCompStat(game->completed) << "' where `id` = " << game->id << ";";
		db.load_res();

		if (db.res) {
			throw exep("Couldn't update game completed status");
		}
	}
}

void Game::DeleteFromDB(int gameId) {
	db.query << "delete from boards where `game_id` = " << gameId << ";";
	db.load_res();

	db.query << "delete from games where `id` = " << gameId << ";";
	db.load_res();

	if (ExistsInDB(gameId)) {
		throw exep("Could not fully delete the game");
	}
}

bool Game::ExistsInDB(int gameId) {
	db.query << "select `id` from games where `id` = " << gameId << ";";
	db.load_res();

	auto row = db.get_row();
	if (row) {
		return true;
	}
	else {
		return false;
	}
}

void Game::SolveLevel() {
	*lvlBoard = *solvedBoard;
}

int Game::FindSquareIndex(int origRow, int origCol) {
	int pairStartIdx, row, col;

	for (int sqrIdx = 0; sqrIdx < size; sqrIdx++) {
		for (int pairIdx = 0; pairIdx < size; pairIdx++) {
			pairStartIdx = (sqrIdx * size * 2) + (pairIdx * 2);
			row = squareLayouts[pairStartIdx];
			col = squareLayouts[pairStartIdx + 1];

			if (row == origRow && col == origCol) {
				return sqrIdx;
			}
		}
	}
}

char* Game::GetFirstEmpty(int& row, int& col) {  // can only be used for solvedBoard
	char* loc;
	for (row = 0; row < size; row++) {
		for (col = 0; col < size; col++) {
			loc = &(solvedBoard->get(row, col));
			if (*loc == emptyChar) {
				return loc;
			}
		}
	}
	return NULL;
}

void Game::GetNextEmptyIndex(int& row, int& col) {  // only for origBoard
	if (row == -1) {
		row = 0;
	}
	col++;

	for (row; row < size; row++) {
		while (col < size) {
			if (origBoard->get(row, col) == emptyChar) {
				return;
			}
			col++;
		}
		col = 0;
	}

	row = -1;
	col = -1;
}

bool Game::ValidateRow(char inserted, int origRow, int origCol, BoardType boardType) {
	Board* board;
	if (boardType == BoardType::Solved) {
		board = solvedBoard;
	}
	else if (boardType == BoardType::Original) {
		board = origBoard;
	}
	else if (boardType == BoardType::Level) {
		board = lvlBoard;
	}
	else {
		//std::cout << "Unknown board type " << static_cast<int>(boardType) << std::endl;
		throw 727;
	}

	for (int col = 0; col < size; col++) {
		if (inserted == board->get(origRow, col)) {
			if (col != origCol) {
				return false;
			}
		}
	}

	return true;
}

bool Game::ValidateCol(char inserted, int origRow, int origCol, BoardType boardType) {
	Board* board;
	if (boardType == BoardType::Solved) {
		board = solvedBoard;
	}
	else if (boardType == BoardType::Original) {
		board = origBoard;
	}
	else if (boardType == BoardType::Level) {
		board = lvlBoard;
	}
	else {
		//std::cout << "Unknown board type " << static_cast<int>(boardType) << std::endl;
		throw 727;
	}

	for (int row = 0; row < size; row++) {
		if (inserted == board->get(row, origCol)) {
			if (row != origRow) {
				return false;
			}
		}
	}

	return true;
}

bool Game::ValidateSqr(char inserted, int origRow, int origCol, BoardType boardType) {
	Board* board;
	if (boardType == BoardType::Solved) {
		board = solvedBoard;
	}
	else if (boardType == BoardType::Original) {
		board = origBoard;
	}
	else if (boardType == BoardType::Level) {
		board = lvlBoard;
	}
	else {
		//std::cout << "Unknown board type " << static_cast<int>(boardType) << std::endl;
		throw 727;
	}

	int sqrIdx = FindSquareIndex(origRow, origCol);
	int pairStartIdx, row, col;

	for (int pairIdx = 0; pairIdx < size; pairIdx++) {
		pairStartIdx = (sqrIdx * size * 2) + (pairIdx * 2);
		row = squareLayouts[pairStartIdx];
		col = squareLayouts[pairStartIdx + 1];

		if (inserted == board->get(row, col)) {
			if (row != origRow && col != origCol) {
				return false;
			}
		}
	}

	return true;
}

void Game::ValidateRow(Validation& vld) {
	Board* board;
	if (vld.boardType == BoardType::Solved) {
		board = solvedBoard;
	}
	else if (vld.boardType == BoardType::Original) {
		board = origBoard;
	}
	else if (vld.boardType == BoardType::Level) {
		board = lvlBoard;
	}
	else {
		//std::cout << "Unknown board type " << static_cast<int>(vld.boardType) << std::endl;
		throw 727;
	}

	for (int col = 0; col < size; col++) {
		if (vld.inserted == board->get(vld.insRow, col)) {
			if (col != vld.insCol) {
				vld.foundDupe = true;
				vld.vldType = ValidationType::Row;
				vld.dupeRow = vld.insRow;
				vld.dupeCol = col;
				return;
			}
		}
	}
}

void Game::ValidateCol(Validation& vld) {
	Board* board;
	if (vld.boardType == BoardType::Solved) {
		board = solvedBoard;
	}
	else if (vld.boardType == BoardType::Original) {
		board = origBoard;
	}
	else if (vld.boardType == BoardType::Level) {
		board = lvlBoard;
	}
	else {
		//std::cout << "Unknown board type " << static_cast<int>(vld.boardType) << std::endl;
		throw 727;
	}

	for (int row = 0; row < size; row++) {
		if (vld.inserted == board->get(row, vld.insCol)) {
			if (row != vld.insRow) {
				vld.foundDupe = true;
				vld.vldType = ValidationType::Col;
				vld.dupeRow = row;
				vld.dupeCol = vld.insCol;
				return;
			}
		}
	}
}

void Game::ValidateSqr(Validation& vld) {
	Board* board;
	if (vld.boardType == BoardType::Solved) {
		board = solvedBoard;
	}
	else if (vld.boardType == BoardType::Original) {
		board = origBoard;
	}
	else if (vld.boardType == BoardType::Level) {
		board = lvlBoard;
	}
	else {
		//std::cout << "Unknown board type " << static_cast<int>(vld.boardType) << std::endl;
		throw 727;
	}

	int sqrIdx = FindSquareIndex(vld.insRow, vld.insCol);
	int pairStartIdx, row, col;

	for (int pairIdx = 0; pairIdx < size; pairIdx++) {
		pairStartIdx = (sqrIdx * size * 2) + (pairIdx * 2);
		row = squareLayouts[pairStartIdx];
		col = squareLayouts[pairStartIdx + 1];

		if (vld.inserted == board->get(row, col)) {
			if (row != vld.insRow && col != vld.insCol) {
				vld.foundDupe = true;
				vld.vldType = ValidationType::Sqr;
				vld.dupeRow = row;
				vld.dupeCol = col;
				vld.sqrIdx = sqrIdx;
				return;
			}
		}
	}
}

bool Game::GenerateNewBoard(System::ComponentModel::BackgroundWorker^ w, System::ComponentModel::DoWorkEventArgs^ e) {  // used for solvedBoard initialization only
	int row, col;
	char* loc = GetFirstEmpty(row, col);
	if (!loc) {
		return true;
	}

	std::vector<char> avalChars;
	avalChars.reserve(size);
	for (int i = 0; i < size; i++) {
		avalChars.push_back(totalChars[i]);
	}

	std::shuffle(avalChars.begin(), avalChars.end(), gen);

	for (int i = 0; i < size; i++) {
		*loc = avalChars[i];

		if (!ValidateRow(*loc, row, col, BoardType::Solved) ||
			!ValidateCol(*loc, row, col, BoardType::Solved) ||
			!ValidateSqr(*loc, row, col, BoardType::Solved)) {
			continue;
		}

		if (GenerateNewBoard(w, e)) {  // if FillBoard is true, that means it has hit the base case, which means that the board has been filled
			return true;
		}
		else if (w->CancellationPending) {
			e->Cancel = true;
			return false;
		}
	}

	*loc = emptyChar;
	return false;
}

void Game::GenerateLevel() {
	int row, col;
	char* val;
	std::uniform_int_distribution<> distrPer, distrIdx;

	if (difficulty == Difficulty::Easy) {  // for each difficulty, there is a range of percentages (for an example 350 = 35.0%)
		distrPer = std::uniform_int_distribution<>(350, 400);
	}
	else if (difficulty == Difficulty::Medium) {
		distrPer = std::uniform_int_distribution<>(450, 500);
	}
	else if (difficulty == Difficulty::Hard) {
		distrPer = std::uniform_int_distribution<>(550, 600);
	}

	removePercentage = distrPer(gen) / 1000.0;  // getting percentage of characters to remove
	removeAmount = std::floor(size * size * removePercentage);  // getting amount of characters to remove based on the percentage
	//std::cout << removePercentage << " " << removeAmount << std::endl;

	distrIdx = std::uniform_int_distribution<>(0, size - 1);
	*origBoard = *solvedBoard;  // copying the board

	for (int i = 0; i < removeAmount; i++) {
		row = distrIdx(gen);  // getting random row
		col = distrIdx(gen);  // getting random col
		//std::cout << row << " " << col << std::endl;

		val = &(origBoard->get(row, col));
		if (*val == emptyChar) {  // checking if the position has already been removed
			i--;
		}
		else {
			*val = emptyChar;
		}
	}

	*lvlBoard = *origBoard;  // copying the board
}

Validation Game::ValidateLocation(char inserted, int row, int col, BoardType boardType) {
	Validation validation(inserted, row, col, boardType);

	ValidateRow(validation);
	if (!validation) return validation;

	ValidateCol(validation);
	if (!validation) return validation;

	ValidateSqr(validation);
	return validation;
}

Validation Game::ValidateLevel() {
	Validation vld;
	int currRow = -1;
	int currCol = -1;
	GetNextEmptyIndex(currRow, currCol);
	char currChar;

	while (currRow != -1) {
		currChar = lvlBoard->get(currRow, currCol);
		//std::cout << currChar << " " << currRow << " " << currCol << std::endl;
		if (currChar != emptyChar) {
			vld = ValidateLocation(currChar, currRow, currCol, BoardType::Level);
			if (!vld) {
				break;
			}
		}

		GetNextEmptyIndex(currRow, currCol);
	}

	return vld;
}

void Game::ResetLevel() {
	*lvlBoard = *origBoard;  // copying the board
}

void Game::Print(BoardType boardType) {
	Board* board;

	if (boardType == BoardType::Solved) {
		//std::cout << "Solved:\n";
		board = solvedBoard;
	}
	else if (boardType == BoardType::Original) {
		//std::cout << "Original:\n";
		board = origBoard;
	}
	else if (boardType == BoardType::Level) {
		//std::cout << "Level:\n";
		board = lvlBoard;
	}
	else {
		//std::cout << "Unknown board type " << static_cast<int>(boardType) << std::endl;
		throw 727;
	}

	board->Print();
}

void Game::SetChar(int row, int col, char ch) {  // only for lvlBoard
	if (origBoard->get(row, col) != emptyChar) {
		//std::cout << "Cannot modify original values\n";
		throw 727;
	}

	if (ch == emptyChar) {
		lvlBoard->get(row, col) = ch;
		return;
	}

	for (int i = 0; i < size; i++) {
		if (totalChars[i] == ch) {
			lvlBoard->get(row, col) = ch;
			return;
		}
	}

	//std::cout << "Cannot set invalid character\n";
	throw 727;
}

char Game::GetChar(int row, int col) {  // only for lvlBoard
	return lvlBoard->get(row, col);
}

bool Game::CharIsReplaceable(int row, int col) {
	if (origBoard->get(row, col) == emptyChar) {
		return true;
	}
	else {
		return false;
	}
}

Game::~Game() {
	if (squareLayouts != nullptr) {
		delete[] squareLayouts;
	}
	if (lvlBoard != nullptr) {
		delete lvlBoard;
	}
	if (origBoard != nullptr) {
		delete origBoard;
	}
	if (solvedBoard != nullptr) {
		delete solvedBoard;
	}
	//delete[] totalChars;  // this causes object deletion to fail, for explanation see scenario 1.A: https://stackoverflow.com/a/64418625; as far as i understand, it gets deleted automatically
}
