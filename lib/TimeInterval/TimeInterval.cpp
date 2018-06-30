#include "TimeInterval.h"

namespace iot
{

TimeInterval::TimeInterval()
{
}

void TimeInterval::setBegin(int hour, int min, int sec)
{
	_timeBegin = TimeValue(hour, min, sec);
}

void TimeInterval::setBegin(const TimeValue &time)
{
	_timeBegin = time;
}

void TimeInterval::setEnd(int hour, int min, int sec)
{
	_timeEnd = TimeValue(hour, min, sec);
}

void TimeInterval::setEnd(const TimeValue &time)
{
	_timeEnd = time;
}

bool TimeInterval::contains(const TimeValue &time)
{
	if (_timeBegin <= _timeEnd)
	{
		return time >= _timeBegin && time < _timeEnd;
	}
	else
	{
		return time >= _timeBegin || time < _timeEnd;
	}
}
}