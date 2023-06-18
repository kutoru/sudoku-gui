#include "Validation.h"

Validation::Validation() {
	inserted = NULL;
	insRow = -1;
	insCol = -1;
	boardType = BoardType::None;

	foundDupe = false;
	vldType = ValidationType::None;
	dupeRow = -1;
	dupeCol = -1;
	sqrIdx = -1;
}

Validation::Validation(char inserted, int insRow, int insCol, BoardType boardType) {
	this->inserted = inserted;
	this->insRow = insRow;
	this->insCol = insCol;
	this->boardType = boardType;

	foundDupe = false;
	vldType = ValidationType::None;
	dupeRow = -1;
	dupeCol = -1;
	sqrIdx = -1;
}

void Validation::Print() {
	logl("inserted="); logl(inserted); logl("; ");
	logl("insRow="); logl(insRow); logl("; ");
	logl("insCol="); logl(insCol); logl("; ");
	logl("boardType="); logl(static_cast<int>(boardType)); logl("; ");
	logl("foundDupe="); logl(foundDupe); logl("; ");
	logl("vldType="); logl(static_cast<int>(vldType)); logl("; ");
	logl("dupeRow="); logl(dupeRow); logl("; ");
	logl("dupeCol="); logl(dupeCol); logl("; ");
	logl("sqrIdx="); logl(sqrIdx); logl(";\n");
}

Validation::operator bool() const {
	return !foundDupe;
}
