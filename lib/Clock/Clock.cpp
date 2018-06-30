#include "Clock.h"
#include <Arduino.h>

namespace iot 
{

Clock::Clock()
{
}

void Clock::calibrate(int hour, int min, int sec)
{
	_lastMillis = millis();
	_lastTime = TimeValue(hour, min, sec);
	if (!_isCalibrated)
	{
		_isCalibrated = true;
	}
}

bool Clock::getCurrentTime(TimeValue &time)
{
	if (!_isCalibrated)
	{
		return false;
	}

	unsigned long delta = (millis() - _lastMillis) / 1000;
	int secs = (delta + _lastTime.getTotalSecs()) % 86400L;
	time = TimeValue(0, 0, secs);

	return true;
}
}
