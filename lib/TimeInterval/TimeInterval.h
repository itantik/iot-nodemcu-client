#pragma once

#include <TimeValue.h>

namespace iot
{

class TimeInterval
{
  private:
	TimeValue _timeBegin;
	TimeValue _timeEnd;

  public:
	TimeInterval();

	void setBegin(int hour, int min, int sec);
	void setBegin(const TimeValue &time);
	void setEnd(int hour, int min, int sec);
	void setEnd(const TimeValue &time);

	TimeValue getBegin() { return _timeBegin; };
	TimeValue getEnd() { return _timeEnd; };

	bool contains(const TimeValue &time);
};
}