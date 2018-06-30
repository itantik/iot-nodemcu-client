#include "TimeValue.h"

namespace iot
{

TimeValue::TimeValue()
{
	_totalSecs = 0;
}

TimeValue::TimeValue(const TimeValue &tv)
{
	_totalSecs = tv._totalSecs;
}

TimeValue::TimeValue(int hour, int min, int sec)
{
	_totalSecs = hour * 3600 + min * 60 + sec;
}

String TimeValue::toString()
{
	int h = _totalSecs / 3600;
	int m = (_totalSecs % 3600) / 60;
	int s = _totalSecs % 60;
	return String(h) + (m < 10 ? ":0" : ":") + String(m) + (s < 10 ? ":0" : ":") + String(s);
}

TimeValue &TimeValue::operator=(const TimeValue &tv)
{
	if (this != &tv || _totalSecs != tv._totalSecs)
	{
		_totalSecs = tv._totalSecs;
	}
	return *this;
}

bool operator<(const TimeValue &tl, const TimeValue &tr)
{
	return tl._totalSecs < tr._totalSecs;
}

bool operator>(const TimeValue &tl, const TimeValue &tr)
{
	return tr < tl;
}

bool operator<=(const TimeValue &tl, const TimeValue &tr)
{
	return !(tr < tl);
}

bool operator>=(const TimeValue &tl, const TimeValue &tr)
{
	return !(tl < tr);
}
}