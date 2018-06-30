#include "BaseControl.h"

namespace iot
{

BaseControl::BaseControl(String name)
{
	_name = name;
}

BaseControl::~BaseControl()
{
}

void BaseControl::setup()
{
}

void BaseControl::readActive()
{
}

void BaseControl::readInactive()
{
}

String BaseControl::createRequest()
{
	return "{}";
}

void BaseControl::processResponse(const JsonObject &json)
{
}

void BaseControl::writeActive()
{
}

void BaseControl::writeInactive()
{
}

} // namespace iot