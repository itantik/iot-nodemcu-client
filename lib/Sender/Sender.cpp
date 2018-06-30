#include "Sender.h"
#include <JsonString.h>

namespace iot
{

Sender::Sender(BaseClient *client)
{
	_client = client;
}

void Sender::send(BaseDevice *device)
{
	// connection interval
	if (!_connectionTimer.isOver())
	{
		if (Serial)
		{
			Serial.println("***");
			Serial.println("Connection is paused");
		}
		return;
	}
	// start a new interval
	_connectionTimer.restart();

	// make connection
	String message = device->createRequest();
	int code = _client->send(message);
	if (code == 200)
	{
		// jsonBuffer can read from an input Stream,
		// memory is freed when jsonBuffer goes out of scope
		DynamicJsonBuffer jsonBuffer;
		JsonObject &json = jsonBuffer.parse(_client->getStream());
		if (!json.success())
		{
			device->addConnectionLog(ConnectionLogCode::jsonParsingErr);
			if (Serial)
			{
				Serial.println("Response error: JSON parsing failed");
			}
			return;
		}

		device->processResponse(json);
		if (Serial)
		{
			Serial.print("Response JSON: ");
			json.printTo(Serial);
			Serial.println();
		}
		_connectionTimer.setDuration(device->getConnectionInterval());
	}
	else if (code == 0)
	{
		device->addConnectionLog(ConnectionLogCode::connectionErr);
		if (Serial)
		{
			Serial.println("Connection failed");
		}
	}
	else if (code < 0)
	{
		device->addConnectionLog(ConnectionLogCode::requestErr);
		if (Serial)
		{
			Serial.println("Connection error: code " + String(code));
		}
	}
	else
	{
		device->addConnectionLog(ConnectionLogCode::responseErr);
		if (Serial)
		{
			Serial.println("Response error: status code " + String(code));
		}
	}
	_client->end();
}

} // namespace iot
