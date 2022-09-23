#pragma once
#pragma once
#include<iostream>
#include<sstream>
using namespace std;
struct time {
	//时间格式hour:minute +day
	int hour;
	int minute;
	//int day;
	void show() {
		cout << hour << ":" << minute;
	}
	/*ostream& operator<< (ostream& output)
	{
		output << day << hour << minute;
		return output;
	}*/
	/*istream& operator >> (istream& input)
	{
		input >> day >> hour >> minute;
		return input;
	}*/
};
