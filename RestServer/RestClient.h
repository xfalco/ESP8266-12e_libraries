#ifndef RestClient_h
#define RestClient_h

#include "ESP8266WiFi.h"

class RestClient
{
  public:
  	RestClient();
    RestClient(WiFiClient& client, String methodType, String method, String parameters, const char* html);
    ~RestClient();
    String getMethodType();
    String getMethod();
    String getParameterString(String parameterName);
    int getParameterInt(String parameterName);
    void print(String message);
    void serveDefaultHtml();
    operator bool();
  private:
  	int _numParameters;
    String _method;
    String _methodType;
    String* _parameterNames;
    String* _parameterValues;
    WiFiClient _client;
    const char* _html;
};

#endif