#ifndef RestServer_h
#define RestServer_h

#include "ESP8266WiFi.h"
#include "RestClient.h"

class RestServer
{
  public:
    RestServer(uint16_t port);
    ~RestServer();
    void startMethod(String methodAddress);
    void startMethod(String methodTitle, String methodAddress);
    void endMethod();
    void addParameter(String parameterName);
    void addParameter(String parameterTitle, String parameterName);
    void addSelectParameter(String parameterName, const char* option1, const char* option2);
    void addSelectParameter(String parameterName, const char* option1, const char* option2, const char* option3);
    void addSelectParameter(String parameterName, const char* option1, const char* option2, const char* option3, const char* option4);
    void addSelectParameter(String parameterName, const char* option1, const char* option2, const char* option3, const char* option4, const char* option5);
    void addSelectParameter(String parameterTitle, String parameterName, const char* option1, const char* option2);
    void addSelectParameter(String parameterTitle, String parameterName, const char* option1, const char* option2, const char* option3);
    void addSelectParameter(String parameterTitle, String parameterName, const char* option1, const char* option2, const char* option3, const char* option4);
    void addSelectParameter(String parameterTitle, String parameterName, const char* option1, const char* option2, const char* option3, const char* option4, const char* option5);
    void connect(const char* ssid, const char* password, bool printToSerial);
    RestClient getClient();

    friend class RestClient;
  private:
  	WiFiServer _server;
  	String _html;

};

#endif