#include "ControlServerTime.h"
#include <JsonString.h>

namespace iot
{

ControlServerTime::ControlServerTime(String name) : BaseControl(name)
{
	_timeOfWritingUpdated = false;
}

ControlServerTime::~ControlServerTime()
{
}

void ControlServerTime::readActive()
{
	_clock.getCurrentTime(_timeOfReading);
	_timeOfWritingUpdated = false;

	if (Serial)
	{
		Serial.println("*");
		Serial.println("Control: " + getName());
		Serial.println("Time of reading: " + (_clock.isCalibrated() ? _timeOfReading.toString() : "NOT CALIBRATED"));
	}
}

void ControlServerTime::readInactive()
{
	readActive();
}

String ControlServerTime::createRequest()
{
	String req = "";
	if (_calibrationErrs > 0)
	{
		String logs = "";
		JsonString::append("calibration_errs", _calibrationErrs, logs);
		JsonString::append("logs", "{" + logs + "}", req);
	}
	return "{" + req + "}";
}

void ControlServerTime::processResponse(const JsonObject &json)
{
	_calibrationErrs = 0;

	if (json["time"] != NULL)
	{
		_clock.calibrate(0, 0, json["time"]);
	}
	else if (!_clock.isCalibrated())
	{
		_calibrationErrs++;
	}
}

void ControlServerTime::writeActive()
{
	_timeOfWritingUpdated = _clock.getCurrentTime(_timeOfWriting);

	if (Serial)
	{
		Serial.println("*");
		Serial.println("Control: " + getName());
		Serial.println("Time of writing: " + (_timeOfWritingUpdated ? _timeOfWriting.toString() : "NOT CALIBRATED"));
	}
}

void ControlServerTime::writeInactive()
{
	writeActive();
}

bool ControlServerTime::getTimeOfReading(TimeValue &time)
{
	if (_clock.isCalibrated())
	{
		time = _timeOfReading;
		return true;
	}
	return false;
}

bool ControlServerTime::getTimeOfWriting(TimeValue &time)
{
	if (_timeOfWritingUpdated && _clock.isCalibrated())
	{
		time = _timeOfWriting;
		return true;
	}
	return false;
}
}
