#pragma once

#include <Arduino.h>

namespace iot
{

class TimeValue
{
private:
	int _totalSecs = 0;

public:
	TimeValue();
	TimeValue(const TimeValue &tv);
	TimeValue(int hour, int min, int sec);

	int getTotalSecs() { return _totalSecs; };

	String toString();

	TimeValue & operator=(const TimeValue &tv);

	friend bool operator<(const TimeValue &tl, const TimeValue &tr);
	friend bool operator>(const TimeValue &tl, const TimeValue &tr);
	friend bool operator<=(const TimeValue &tl, const TimeValue &tr);
	friend bool operator>=(const TimeValue &tl, const TimeValue &tr);
};
}