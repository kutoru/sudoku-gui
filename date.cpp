#include "date.h"

date::date() {
	year = -1;
	month = -1;
	day = -1;
	hour = -1;
	minute = -1;
	second = -1;
}

void date::append(int num) {
	if (year == -1) {
		year = num;
	}
	else if (month == -1) {
		month = num;
	}
	else if (day == -1) {
		day = num;
	}
	else if (hour == -1) {
		hour = num;
	}
	else if (minute == -1) {
		minute = num;
	}
	else if (second == -1) {
		second = num;
	}
}

std::string date::to_string() {
	std::string date = "";
	std::string temp;

	temp = std::to_string(year);
	date += temp + '/';
	temp = std::to_string(month);
	date += fsd(temp) + '/';
	temp = std::to_string(day);
	date += fsd(temp) + ' ';
	temp = std::to_string(hour);
	date += fsd(temp) + ':';
	temp = std::to_string(minute);
	date += fsd(temp) + ':';
	temp = std::to_string(second);
	date += fsd(temp);

	return date;
}

date date::to_date(const char* str) {
	std::string currNum = "";
	date newDate = date();

	for (int i = 0; str[i]; i++) {
		if (str[i] != '-' && str[i] != ' ' && str[i] != ':') {
			currNum += str[i];
		}
		else {
			newDate.append(atoi(currNum.c_str()));
			currNum = "";
		}
	}

	newDate.append(atoi(currNum.c_str()));
	return newDate;
}

std::string date::fsd(std::string temp) {
	if (temp.size() == 1) {
		return '0' + temp;
	}
	else {
		return temp;
	}
}
