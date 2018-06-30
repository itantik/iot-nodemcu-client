#include "Timer.h"
#include <Arduino.h>

namespace iot
{

Timer::Timer()
{
}

void Timer::restart()
{
	if (_duration > 0)
	{
		_started = millis();
		_isRunning = true;
	}
	else
	{
		stop();
	}
}

void Timer::stop()
{
	_isRunning = false;
}

bool Timer::isOver()
{
	if (!_isRunning)
	{
		return true;
	}

	unsigned long delta = millis() - _started;
	if (delta >= _duration)
	{
		_isRunning = false;
		return true;
	}
	return false;
}

void Timer::setDuration(unsigned int sec)
{
	unsigned int d = sec * 1000;
	if (d > 0 && d != _duration)
	{
		_duration = d;
		restart();
	}
}

unsigned int Timer::getDuration()
{
	return _duration / 1000;
}
}