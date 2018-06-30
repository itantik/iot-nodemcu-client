#pragma once

#include <ESP8266WiFi.h>

namespace iot
{

class WiFiConnection
{
public:
	WiFiConnection();

	uint8_t connect(String ssid, String password);
	String getMacAddress();
};
}