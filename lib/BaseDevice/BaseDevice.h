#pragma once

#include <ArduinoJson.h>

namespace iot
{

enum class ConnectionLogCode
{
	connectionErr,
	requestErr,
	responseErr,
	jsonParsingErr,
	jsonFormatErr
};

class BaseDevice
{
public:
	virtual unsigned long getRefreshInterval() = 0;
	virtual unsigned long getConnectionInterval() = 0;

	virtual void addConnectionLog(ConnectionLogCode code) = 0;

	// read inputs (e.g. sensors, status)
	virtual void read() = 0;
	// make a JSON request string
	virtual String createRequest() = 0;
	// apply JSON response
	virtual void processResponse(const JsonObject &json) = 0;
	// write to outputs (e.g. sensors, status)
	virtual void write() = 0;
};
}