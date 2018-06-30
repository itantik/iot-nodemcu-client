#pragma once

#include <BaseControl.h>
#include <Arduino.h>
#include <TimeValue.h>
#include <Clock.h>

namespace iot
{
	
class ControlServerTime : public BaseControl
{
  private:
	Clock _clock;
	TimeValue _timeOfReading;
	TimeValue _timeOfWriting;
	bool _timeOfWritingUpdated;
	// errors
	int _calibrationErrs = 0;

  public:
	ControlServerTime(String name);
	virtual ~ControlServerTime();

	// setup after application start and WiFi connection
	//void setup();

	// read inputs (e.g. sensors, status) when the device is active
	void readActive();
	// read inputs (e.g. sensors, status) when the device is not active
	void readInactive();

	// make a JSON request string
	String createRequest();

	// apply JSON response
	void processResponse(const JsonObject &json);

	// write to the output (e.g. sensors, status) when the device is active
	void writeActive();
	// write to the output (e.g. sensors, status) when the device is not active
	void writeInactive();

	bool getTimeOfReading(TimeValue &time);
	bool getTimeOfWriting(TimeValue &time);
};
}
