#pragma once

#include <Arduino.h>
#include <ArduinoJson.h>

namespace iot
{

class JsonString
{
private:
	static const String _commaLikeChars;

public:
	static void append(String name, String value, String &json);
	static void append(String name, int value, String &json);
	static void appendComma(String &json);
};
} // namespace iot