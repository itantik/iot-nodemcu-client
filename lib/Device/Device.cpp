#include "Device.h"
#include <JsonString.h>

namespace iot
{

Device::Device(Controls *controls)
{
	_isActive = false;
	_controls = controls;
}

void Device::setup(String macAddress, String name, int version)
{
	setup(macAddress, name, version, _defRefreshInterval, _minRefreshInterval);
}

void Device::setup(String macAddress, String appName, int version, unsigned long defaultRefreshInterval, unsigned long minRefreshInterval)
{
	_macAddress = macAddress;
	_appName = appName;
	_version = version;

	_defRefreshInterval = defaultRefreshInterval;
	_minRefreshInterval = minRefreshInterval;

	if (Serial)
	{
		Serial.println();
		Serial.println("*** Welcome ***");
		_printName();
	}

	_controls->setup();
}

unsigned long Device::getRefreshInterval()
{
	if (_refreshInterval == 0)
	{
		return _defRefreshInterval;
	}
	else if (_refreshInterval < _minRefreshInterval)
	{
		return _minRefreshInterval;
	}
	return _refreshInterval;
}

void Device::read()
{
	if (Serial)
	{
		_printName();
		_printStatus();
	}

	_controls->read(_isActive);
}

String Device::createRequest()
{
	String req = "";
	JsonString::append("mac", _macAddress, req);
	JsonString::append("firmware", _appName, req);
	JsonString::append("version", _version, req);
	JsonString::append("active", _isActive ? 1 : 0, req);

	if (_isActive)
	{
		JsonString::append("controls", _controls->createRequest(), req);
	}

	String logs = _getLogString();
	if (logs != "")
	{
		JsonString::append("logs", "{" + logs + "}", req);
	}

	return "{" + req + "}";
}

void Device::processResponse(const JsonObject &json)
{
	// clear logs
	_restartedLog = 0;
	_connectionErrs = 0;
	_requestErrs = 0;
	_responseErrs = 0;
	_jsonParsingErrs = 0;
	_jsonFormatErrs = 0;

	// process json
	_isActive = json["active"] == 1;

	if (json["refresh_interval"] != NULL)
	{
		_refreshInterval = json["refresh_interval"];
	}
	if (json["connection_interval"] != NULL)
	{
		_connectionInterval = json["connection_interval"];
	}

	_controls->processResponse(json["controls"]);
}

void Device::write()
{
	if (Serial)
	{
		Serial.println("***");
		_printStatus();
	}

	_controls->write(_isActive);

	if (Serial)
	{
		Serial.println("***");
		Serial.println();
	}
}

void Device::_printName()
{
	Serial.println("*** " + _appName + " (v. " + String(_version) + ") ***");
}

void Device::_printStatus()
{
	if (_isActive)
	{
		Serial.println("Device status: ACTIVE");
	}
	else
	{
		Serial.println("Device status: NOT ACTIVE");
	}
}

void Device::addConnectionLog(ConnectionLogCode code)
{
	switch (code)
	{
	case ConnectionLogCode::connectionErr:
		_connectionErrs++;
		break;
	case ConnectionLogCode::requestErr:
		_requestErrs++;
		break;
	case ConnectionLogCode::responseErr:
		_responseErrs++;
		break;
	case ConnectionLogCode::jsonParsingErr:
		_jsonParsingErrs++;
		break;
	case ConnectionLogCode::jsonFormatErr:
		_jsonFormatErrs++;
		break;
	}
}

String Device::_getLogString()
{
	String req = "";
	if (_restartedLog)
	{
		JsonString::append("restarted", _restartedLog, req);
	}
	if (_connectionErrs)
	{
		JsonString::append("connection_errs", _connectionErrs, req);
	}
	if (_requestErrs)
	{
		JsonString::append("request_errs", _requestErrs, req);
	}
	if (_responseErrs)
	{
		JsonString::append("response_errs", _responseErrs, req);
	}
	if (_jsonParsingErrs)
	{
		JsonString::append("json_parse_errs", _jsonParsingErrs, req);
	}
	if (_jsonFormatErrs)
	{
		JsonString::append("json_format_errs", _jsonFormatErrs, req);
	}
	return req;
}

} // namespace iot
