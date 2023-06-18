#pragma once

#include "db.h"
#include "date.h"

class Account {
public:
	bool wasFound;
	int id;
	std::string username;
	std::string password;
	std::string key;
	date dateCreated;

	Account();
	static Account CreateNew(std::string name, std::string pass);
	static bool CheckNameAvailability(std::string name);
	static Account CheckPassword(std::string name, std::string pass);
	static Account GetAccount(std::string username);
	static int GetTotalGameCount(int userId);
	static int GetCompletedGameCount(int userId);
	static void ShowAll();
	static void Delete(int userId);
};
