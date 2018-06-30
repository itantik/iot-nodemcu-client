#include "HttpClient.h"

namespace iot
{

HttpClient::HttpClient() : BaseClient()
{
}

void HttpClient::setup(String url)
{
    _url = url;
}

int HttpClient::send(String message)
{
	_errorMessage = "";

	if (Serial)
	{
		Serial.println("***");
		Serial.println("Request URL: " + _url);
		Serial.println("Request JSON: " + message);
		Serial.println("Request method: POST");
	}

   if (!_http.begin(_url))
   {
	   _errorMessage = "Connection failed";
		if (Serial)
		{
			Serial.println(_errorMessage);
		}
		return 0;
   }

    _http.addHeader("Cache-Control", "no-cache");
    _http.addHeader("Content-Type", "application/json");
    int httpCode = _http.POST(message); // send the request

    _errorMessage = (httpCode < 0) ? _http.errorToString(httpCode) : String(httpCode);
	if (Serial)
	{
		Serial.println("Response code: " + _errorMessage);
	}

	return httpCode;
}

String HttpClient::getPayload()
{
	return _http.getString();
}

WiFiClient& HttpClient::getStream()
{
	return _http.getStream();
}

void HttpClient::end()
{
    _http.end();
}

}
