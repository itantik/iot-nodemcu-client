#pragma once

#include <BaseDevice.h>
#include <Controls.h>
#include <ArduinoJson.h>

namespace iot
{

class Device : public BaseDevice
{
  private:
	// device identification
	String _macAddress;
	String _appName;
	int _version;
	bool _isActive;
	// application refresh interval (ms)
	unsigned long _defRefreshInterval = 2000;
	unsigned long _minRefreshInterval = 2000;
	unsigned long _refreshInterval = 0;
	// client connection interval (s)
	unsigned long _connectionInterval = 0;
	// logs
	int _restartedLog = 1;
	int _connectionErrs = 0;
	int _requestErrs = 0;
	int _responseErrs = 0;
	int _jsonParsingErrs = 0;
	int _jsonFormatErrs = 0;

	Controls *_controls;

	void _printName();
	void _printStatus();
	String _getLogString();

  public:
	Device(Controls *controls);

	unsigned long getRefreshInterval();
	unsigned long getConnectionInterval() { return _connectionInterval; };

	void addConnectionLog(ConnectionLogCode code);

	// initial setup of this device and its controls
	void setup(String macAddress, String appName, int version);
	void setup(String macAddress, String appName, int version, unsigned long defaultRefreshInterval, unsigned long minRefreshInterval);
	// read inputs (e.g. sensors, status)
	void read();
	// make a JSON request string
	String createRequest();
	// apply JSON response
	void processResponse(const JsonObject &json);
	// write to outputs (e.g. sensors, status)
	void write();
};
} // namespace iot