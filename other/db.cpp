#include "db.h"

void DB::initialize() {
	conn = mysql_init(0);
	conn = mysql_real_connect(conn, HOST, USER, PASS, DATABASE, PORT, NULL, 0);

	if (!conn) {
		logl("Couldn't connect to the database");
		throw 727;
	}

	query.str("");
}

void DB::load_res() {
	q = query.str();
	logl("New query:\n");
	logl(q, true);
	mysql_query(conn, q.c_str());
	res = mysql_store_result(conn);
	query.str("");
}

MYSQL_ROW DB::get_row() {
	return mysql_fetch_row(res);
}

DB db = DB();
