#pragma once

#include <Arduino.h>
#include <ArduinoJson.h>

namespace iot
{

class BaseControl
{
protected:
	String _name;

public:
	BaseControl(String name);
	virtual ~BaseControl();

	virtual String getName() { return _name; };

	// setup after application start and WiFi connection
	virtual void setup();

	// read inputs (e.g. sensors, status) when the device is active
	virtual void readActive();
	// read inputs (e.g. sensors, status) when the device is not active
	virtual void readInactive();

	// make a JSON request string
	virtual String createRequest();

	// apply JSON response
	virtual void processResponse(const JsonObject &json);

	// write to the output (e.g. sensors, status) when the device is active
	virtual void writeActive();
	// write to the output (e.g. sensors, status) when the device is not active
	virtual void writeInactive();
};
} // namespace iot