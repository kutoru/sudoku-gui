#pragma once

#include "util.h"
#include <sstream>
#include <mysql.h>

#define HOST "127.0.0.1"
#define USER "root"
#define PASS ""  // enter your root pass here
#define DATABASE "sudoku"
#define PORT 3306

class DB {
public:
	MYSQL* conn;
	MYSQL_RES* res;
	//MYSQL_ROW row;
	std::stringstream query;
	std::string q;

	void initialize();
	void load_res();
	MYSQL_ROW get_row();
};

extern DB db;
