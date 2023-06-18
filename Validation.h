#pragma once

#include "Board.h"

enum class ValidationType {None, Row, Col, Sqr};

class Validation {
public:
	char inserted;
	int insRow;
	int insCol;
	BoardType boardType;

	bool foundDupe;
	ValidationType vldType;
	int dupeRow;
	int dupeCol;
	int sqrIdx;

	Validation();
	Validation(char inserted, int insRow, int insCol, BoardType boardType);
	void Print();
	operator bool() const;
};
