#pragma once

#include <Arduino.h>
#include <ESP8266HTTPClient.h>
#include <BaseClient.h>

namespace iot
{

class HttpClient: public BaseClient
{
private:
	HTTPClient _http;
    String _url;
    String _errorMessage;

public:
    HttpClient();

    void setup(String url);
    int send(String message);
    String getPayload();
    virtual WiFiClient& getStream();
    void end();
};

}