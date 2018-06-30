#include "ControlDailySwitch.h"

namespace iot
{

ControlDailySwitch::ControlDailySwitch(String name, uint8_t pin, ControlServerTime *controlTime) : BaseControl(name)
{
	_pin = pin;
	_controlTime = controlTime;
}

ControlDailySwitch::~ControlDailySwitch()
{
}

void ControlDailySwitch::setup()
{
	pinMode(_pin, OUTPUT);
	digitalWrite(_pin, LOW);
}

void ControlDailySwitch::processResponse(const JsonObject &json)
{
	if (json["on"] != NULL && json["off"] != NULL)
	{
		_onInterval.setBegin(0, 0, json["on"]);
		_onInterval.setEnd(0, 0, json["off"]);
	}
}

void ControlDailySwitch::writeActive()
{
	TimeValue time;
	bool isOn = _controlTime->getTimeOfWriting(time) && _onInterval.contains(time);

	digitalWrite(_pin, isOn ? HIGH : LOW);

	if (Serial)
	{
		Serial.println("*");
		Serial.println("Control: " + getName());
		Serial.println("Switch on: " + _onInterval.getBegin().toString());
		Serial.println("Switch off: " + _onInterval.getEnd().toString());
		Serial.print("Switch status: ");
		Serial.println(isOn ? "ON" : "OFF");
	}
}

void ControlDailySwitch::writeInactive()
{
	digitalWrite(_pin, LOW);
	
	if (Serial)
	{
		Serial.println("*");
		Serial.println("Control: " + getName());
		Serial.println("Switch status: OFF");
	}
}
}