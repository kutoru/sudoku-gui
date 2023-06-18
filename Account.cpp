#include "Account.h"

Account::Account() {
	wasFound = false;
	id = -1;
	username = "";
	password = "";
	key = "";
	dateCreated = date();
}

Account Account::CreateNew(std::string name, std::string pass) {
	std::string key = GetNewKey();
	pass = EncryptPassword(pass, key);

	db.query << "insert into accounts(`username`, `password`, `key`, `date_created`) " <<
		"values('" << name << "', '" << pass << "', '" << key << "', " << "now());";
	db.load_res();

	Account a = GetAccount(name);
	if (a.wasFound) {
		return a;
	}
	else {
		throw exep("Something went wrong when adding a new Account");
	}
}

bool Account::CheckNameAvailability(std::string name) {
	return !GetAccount(name).wasFound;
}

Account Account::CheckPassword(std::string name, std::string pass) {
	Account a = GetAccount(name);

	if (!a.wasFound) {
		return a;
	}

	pass = EncryptPassword(pass, a.key);
	if (pass == a.password) {
		return a;
	}
	else {
		return Account();
	}
}

Account Account::GetAccount(std::string username) {
	Account a;

	db.query << "select * from accounts where username = '" << username << "';";
	db.load_res();

	auto row = db.get_row();;
	if (row) {
		a.wasFound = true;
		a.id = atoi(row[0]);
		a.username = row[1];
		a.password = row[2];
		a.key = row[3];
		a.dateCreated = date::to_date(row[4]);
	}

	return a;
}

int Account::GetTotalGameCount(int userId) {
	db.query << "select count(id) from games where `user_id` = " << userId << ";";
	db.load_res();
	auto row = db.get_row();
	return atoi(row[0]);
}

int Account::GetCompletedGameCount(int userId) {
	db.query << "select count(id) from games where `user_id` = " << userId << " and completed = 'Y';";
	db.load_res();
	auto row = db.get_row();
	return atoi(row[0]);
}

void Account::ShowAll() {
	db.query << "select * from accounts;";
	db.load_res();
	auto row = db.get_row();

	while (row) {
		logl(row[0]);
		logl(row[1]);
		logl(row[2]);
		logl(row[3]);
		logl(row[4]);
		logl("");
		row = db.get_row();
	}
}

void Account::Delete(int userId) {
	int totalGameCount = GetTotalGameCount(userId);

	if (totalGameCount > 0) {
		int* gameIds = new int[totalGameCount];
		db.query << "select `id` from games where `user_id` = " << userId << ";";
		db.load_res();

		for (int i = 0; i < totalGameCount; i++) {
			auto row = db.get_row();
			gameIds[i] = atoi(row[0]);
		}

		for (int i = 0; i < totalGameCount; i++) {
			db.query << "delete from boards where `game_id` = " << gameIds[i] << ";";
			db.load_res();
		}

		db.query << "delete from games where `user_id` = " << userId << ";";
		db.load_res();
	}

	db.query << "delete from accounts where `id` = " << userId << ";";
	db.load_res();

	logl("Deleted an account, ID: "); logl(userId, true);
}
