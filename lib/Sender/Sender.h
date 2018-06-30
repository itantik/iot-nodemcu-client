#pragma once

#include <BaseDevice.h>
#include <BaseClient.h>
#include <Timer.h>
#include <ArduinoJson.h>

namespace iot
{

class Sender
{
  private:
	// client connection interval
	Timer _connectionTimer;

	BaseClient *_client;

  public:
	Sender(BaseClient *client);

	// send request, receive response
	void send(BaseDevice *device);
};
} // namespace iot