#include "Controls.h"
#include <JsonString.h>

namespace iot
{

Controls::Controls()
{
	_numCtrls = 0;
}

void Controls::add(BaseControl *control)
{
	if (_numCtrls >= MAX)
	{
		return;
	}
	_ctrls[_numCtrls] = control;
	_numCtrls++;
}

void Controls::setup()
{
	for (int i = 0; i < _numCtrls; i++)
	{
		_ctrls[i]->setup();
	}
}

void Controls::read(bool isActive)
{
	for (int i = 0; i < _numCtrls; i++)
	{
		if (isActive)
		{
			_ctrls[i]->readActive();
		}
		else
		{
			_ctrls[i]->readInactive();
		}
	}
}

String Controls::createRequest()
{
	BaseControl *c;
	String req = "";
	for (int i = 0; i < _numCtrls; i++)
	{
		c = _ctrls[i];
		JsonString::append(c->getName(), c->createRequest(), req);
	}
	return "{" + req + "}";
}

void Controls::processResponse(const JsonObject &json)
{
	BaseControl *ctrl;
	for (int i = 0; i < _numCtrls; i++)
	{
		ctrl = _ctrls[i];
		ctrl->processResponse(json[ctrl->getName()]);
	}
}

void Controls::write(bool isActive)
{
	for (int i = 0; i < _numCtrls; i++)
	{
		if (isActive)
		{
			_ctrls[i]->writeActive();
		}
		else
		{
			_ctrls[i]->writeInactive();
		}
	}
}

}
