#pragma once

#include <BaseControl.h>
#include <Arduino.h>
#include <TimeInterval.h>
#include <ControlServerTime.h>

namespace iot
{

class ControlDailySwitch : public BaseControl
{
private:
	// active PIN
	uint8_t _pin;
	// time interval
	TimeInterval _onInterval;
	// time settings
	ControlServerTime *_controlTime;

public:
	ControlDailySwitch(String name, uint8_t pin, ControlServerTime *controlTime);
	virtual ~ControlDailySwitch();

	// setup after application start and WiFi connection
	void setup();

	// read inputs (e.g. sensors, status) when the device is active
	//void readActive();
	// read inputs (e.g. sensors, status) when the device is not active
	//void readInactive();

	// make a JSON request string
	//String createRequest();

	// apply JSON response
	void processResponse(const JsonObject &json);

	// write to the output (e.g. sensors, status) when the device is active
	void writeActive();
	// write to the output (e.g. sensors, status) when the device is not active
	void writeInactive();
};
}