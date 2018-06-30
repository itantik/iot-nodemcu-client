#pragma once

#include <BaseControl.h>
#include <ArduinoJson.h>

namespace iot
{

class Controls
{
private:
	// max allowed controls
	static const int MAX = 20;
	// number of controls
	int _numCtrls;
	// array of controls
	BaseControl *_ctrls[MAX];

public:
	Controls();

	void add(BaseControl *control);

	void setup();
	void read(bool isActive);
	String createRequest();
	void processResponse(const JsonObject &json);
	void write(bool isActive);
};
}