/* *****************************************

   Requires DHT Temperature & Humidity Sensor library for Arduino 
   by Mark Ruys, mark@paracas.nl, http://www.github.com/markruys/arduino-DHT
   
   ******************************************/

#pragma once

#include <BaseControl.h>
#include <Arduino.h>
#include <ArduinoJson.h>
#include <DHT.h>
#include <Timer.h>

namespace iot
{

class ControlDht : public BaseControl
{
  private:
	// active PIN
	uint8_t _pin;
	// DHT object
	DHT _dht;
	// measured values
	float _humidity;
	float _temperature;
	// measurement interval
	Timer _timer;
	// timer interval in secs
	unsigned int _duration;
	// errors
	int _timeoutErrs = 0;
	int _checksumErrs = 0;

	String _getLogString();

  public:
	ControlDht(String name, uint8_t pin);
	virtual ~ControlDht();

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