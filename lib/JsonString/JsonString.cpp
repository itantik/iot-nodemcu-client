#include "JsonString.h"

namespace iot
{

const String JsonString::_commaLikeChars = ",:{[";

void JsonString::append(String name, String value, String &json)
{
	appendComma(json);

	int len = value.length();
	if ((len > 1) &&
		((value[0] == '{' && value[len - 1] == '}') ||
		 (value[0] == '[' && value[len - 1] == ']') ||
		 (value[0] == '"' && value[len - 1] == '"')))
	{
		json += "\"" + name + "\":" + value;
	}
	else
	{
		json += "\"" + name + "\":\"" + value + "\"";
	}
}

void JsonString::append(String name, int value, String &json)
{
	appendComma(json);
	json += "\"" + name + "\":" + String(value);
}

void JsonString::appendComma(String &json)
{
	if (json == "")
	{
		return;
	}

	char last = json[json.length() - 1];
	if (_commaLikeChars.indexOf(last) >= 0)
	{
		return;
	}

	json += ",";
}
} // namespace iot