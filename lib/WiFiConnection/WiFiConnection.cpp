#include "WiFiConnection.h"


namespace iot
{

WiFiConnection::WiFiConnection()
{
}

uint8_t WiFiConnection::connect(String ssid, String password)
{
	if (Serial)
	{
		Serial.println("Connecting to: " + ssid);
	}

	// Explicitly set the ESP8266 to be a WiFi-client, otherwise, it by default,
	// would try to act as both a client and an access-point and could cause
	// network-issues with your other WiFi-devices on your WiFi-network.
	WiFi.mode(WIFI_STA);
	WiFi.begin(ssid.c_str(), password.c_str());
	while (WiFi.status() != WL_CONNECTED)
	{
		delay(500);
		if (Serial)
		{
			Serial.print(".");
		}
	}

	if (Serial)
	{
		Serial.println();
		Serial.println("WiFi connected");
		Serial.print("IP address: ");
		Serial.println(WiFi.localIP());
		Serial.println("***");
		Serial.println();
	}

	return WiFi.status();
}

String WiFiConnection::getMacAddress()
{
	return WiFi.macAddress();
}

}