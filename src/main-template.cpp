/* *****************************************

   Requires ArduinoJson library by Benoit Blanchon, https://arduinojson.org/
   
   ******************************************/

#include <Arduino.h>
#include <WiFiConnection.h>
#include <HttpClient.h>
#include <Controls.h>
#include <Device.h>
#include <Sender.h>
#include <ControlServerTime.h>
#include <ControlDailySwitch.h>
#include <ControlDht.h>

using namespace iot;

// *** Configuration: ***************************************

// application name and version
const char *APPLICATION = "IoT";
const int VERSION = 1;

// application refresh interval (i.e. main loop delay)
const unsigned long DEFAULT_REFRESH_INTERVAL = 20000;
const unsigned long MIN_REFRESH_INTERVAL = 2000;

// WiFi
const char *SSID = "wifi-ssid";
const char *SSID_PASS = "wifi-password";

// remote URL
#define DEBUG_URL // comment this line before deployment
#ifdef DEBUG_URL
// test/debug server
const char *URL = "http://debug_server/";
#else
// deployment server
const char *URL = "http://deployment_server/";
#endif

// active PINs
const uint8_t PIN_SWITCH = D1; // ControlDailySwitch
const uint8_t PIN_DHT = D3;	// ControlDht

// controls used by the device
ControlServerTime ctrlTime("server_time");
ControlDailySwitch ctrlSwitch("daily_switch", PIN_SWITCH, &ctrlTime);
ControlDht ctrlDht("dht", PIN_DHT);

// ****************************************** end configuration.

WiFiConnection wifi;
HttpClient client;
Controls controls;
Device device(&controls);
Sender sender(&client);

void setup()
{
	Serial.begin(9600);
	delay(10);

	// *** Add controls: ***************************************

	controls.add(&ctrlTime);
	controls.add(&ctrlSwitch);
	controls.add(&ctrlDht);

	// ****************************************** end controls.

	client.setup(String(URL));
	device.setup(wifi.getMacAddress(), String(APPLICATION), VERSION, DEFAULT_REFRESH_INTERVAL, MIN_REFRESH_INTERVAL);

	wifi.connect(SSID, SSID_PASS);
}

void loop()
{
	device.read();
	sender.send(&device);
	device.write();

	delay(device.getRefreshInterval());
}
