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
    void addSelectParameter(String parameterTitle, String parameterName, String option1, String option2);
    void addSelectParameter(String parameterTitle, String parameterName, String option1, String option2, String option3);
    void addSelectParameter(String parameterTitle, String parameterName, String option1, String option2, String option3, String option4);
    void addSelectParameter(String parameterTitle, String parameterName, String option1, String option2, String option3, String option4, String option5);
    void connect(const char* ssid, const char* password, bool printToSerial);
    RestClient getClient();

    friend class RestClient;
  private:
  	WiFiServer _server;
  	String _html;
    static String NULL_STRING;

};

#endif