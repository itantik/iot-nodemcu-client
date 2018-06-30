#pragma once

namespace iot
{

class Timer
{
private:
	bool _isRunning = false;
	unsigned long _started; // in milliseconds
	unsigned long _duration = 0;

public:
	Timer();

	void restart();
	void stop();
	bool isOver();
	// sets new duration in seconds
	// timer restarts if differs from current duration
	void setDuration(unsigned int sec);
	// in seconds
	unsigned int getDuration();
};
}