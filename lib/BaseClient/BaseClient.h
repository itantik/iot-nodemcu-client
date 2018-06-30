#pragma once

#include <Arduino.h>
#include <WiFiClient.h>

namespace iot
{

class BaseClient
{
  private:
  public:
    virtual int send(String message) = 0;
    virtual String getPayload() = 0;
    virtual WiFiClient &getStream() = 0;
    virtual void end() = 0;
};

} // namespace iot