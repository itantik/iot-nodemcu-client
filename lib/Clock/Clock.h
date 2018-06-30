#pragma once

#include <TimeValue.h>

namespace iot
{

class Clock
{
private:
	bool _isCalibrated = false;
	TimeValue _lastTime;
	unsigned long _lastMillis = 0;

public:
	Clock();

	void calibrate(int hour, int min, int sec);
	bool isCalibrated() { return _isCalibrated; };
	bool getCurrentTime(TimeValue &time);
};
} // namespace iot