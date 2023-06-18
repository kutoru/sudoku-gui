#pragma once
#include <string>

class date {
private:
	std::string fsd(std::string temp);  // fix single digit

public:
	int year;
	int month;
	int day;
	int hour;
	int minute;
	int second;

	date();
	void append(int num);
	std::string to_string();
	static date to_date(const char* str);
};
