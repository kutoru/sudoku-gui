#pragma once

class date {
private:
	std::string fsd(std::string temp) {  // fix single digit
		if (temp.size() == 1) {
			return '0' + temp;
		}
		else {
			return temp;
		}
	}

public:
	int year;
	int month;
	int day;
	int hour;
	int minute;
	int second;

	date() {
		year = -1;
		month = -1;
		day = -1;
		hour = -1;
		minute = -1;
		second = -1;
	}

	void append(int num) {
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

	std::string to_string() {
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

	static date to_date(const char* str) {
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
};
