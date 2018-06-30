#include "ControlDht.h"
#include <JsonString.h>

namespace iot
{

ControlDht::ControlDht(String name, uint8_t pin) : BaseControl(name)
{
	_pin = pin;
	_humidity = NAN;
	_temperature = NAN;
}

ControlDht::~ControlDht()
{
}

void ControlDht::setup()
{
	_dht.setup(_pin, DHT::DHT22);
}

void ControlDht::readActive()
{
	bool paused = !_timer.isOver();

	if (!paused)
	{
		float h = _dht.getHumidity();
		float t = _dht.getTemperature();
		_timer.restart();

		switch (_dht.getStatus())
		{
		case DHT::ERROR_NONE:
			_humidity = h;
			_temperature = t;
			break;
		case DHT::ERROR_CHECKSUM:
			_checksumErrs++;
			break;

		case DHT::ERROR_TIMEOUT:
			_timeoutErrs++;
			break;
		}
	}

	if (Serial)
	{
		Serial.println("*");
		Serial.println("Control: " + getName());
		Serial.print("DHT status: ");
		Serial.println(_dht.getStatusString());
		if (paused)
		{
			Serial.println("DHT: measurement paused");
		}
		if (!isnan(_temperature))
		{
			Serial.print("DHT temperature: ");
			Serial.print(_temperature, 1);
			Serial.print(" °C (");
			Serial.print(_dht.toFahrenheit(_temperature), 1);
			Serial.println(" F)");
		}
		if (!isnan(_humidity))
		{
			Serial.print("DHT humidity: ");
			Serial.print(_humidity, 1);
			Serial.println(" %");
		}
	}
}

void ControlDht::readInactive()
{
	// reset values
	_humidity = NAN;
	_temperature = NAN;
	_timer.stop();
}

String ControlDht::createRequest()
{
	String req = "";
	if (!isnan(_humidity))
	{
		JsonString::append("humidity", (int)(_humidity * 10), req);
	}
	if (!isnan(_temperature))
	{
		JsonString::append("temperature", (int)(_temperature * 10), req);
	}

	String logs = _getLogString();
	if (logs != "")
	{
		JsonString::append("logs", "{" + logs + "}", req);
	}

	return "{" + req + "}";
}

String ControlDht::_getLogString()
{
	String req = "";
	if (_timeoutErrs)
	{
		JsonString::append("timeout_errs", _timeoutErrs, req);
	}
	if (_checksumErrs)
	{
		JsonString::append("checksum_errs", _checksumErrs, req);
	}
	return req;
}

void ControlDht::processResponse(const JsonObject &json)
{
	// clear measured values
	_humidity = NAN;
	_temperature = NAN;
	// clear logs
	_timeoutErrs = 0;
	_checksumErrs = 0;

	if (json["interval"] != NULL)
	{
		_duration = json["interval"];
	}
}

void ControlDht::writeActive()
{
	// timer restarts when _duration is changed
	_timer.setDuration(_duration);

	if (Serial)
	{
		Serial.println("*");
		Serial.println("Control: " + getName());
		Serial.println("Measurement interval: " + String(_duration) + " s");
	}
}

void ControlDht::writeInactive()
{
	_timer.stop();

	if (Serial)
	{
		Serial.println("*");
		Serial.println("Control: " + getName());
		Serial.println("Status: inactive");
	}
}
} // namespace iot