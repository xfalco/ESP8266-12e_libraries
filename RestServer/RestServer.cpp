#include "RestServer.h"

RestServer::RestServer(uint16_t port)
: _server(WiFiServer(port)),
_html("HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>\r\n")
{
}

void RestServer::startMethod(String methodAddress) {
  startMethod(methodAddress, methodAddress);
}

void RestServer::startMethod(String methodTitle, String methodAddress) {
  _html.concat("<h3>" + methodTitle + "</h3><form action=\"" + methodAddress + "\">");
}

void RestServer::endMethod() {
  _html.concat("<input type=\"submit\" value=\"Submit\">");
  _html.concat("</form>");
}

void RestServer::addParameter(String parameterName) {
  addParameter(parameterName, parameterName);
}

void RestServer::addParameter(String parameterTitle, String parameterName) {
  _html.concat("<label for=\"" + parameterName + "\">" + parameterTitle + "</label>");
  _html.concat("<input type=\"text\" id=\"" + parameterName + "\" name=\"" + parameterName + "\"><br/>");
}

void RestServer::addSelectParameter(String parameterName, const char* option1, const char* option2) {
  addSelectParameter(parameterName, parameterName, option1, option2);
}

void RestServer::addSelectParameter(String parameterName, const char* option1, const char* option2, const char* option3) {
  addSelectParameter(parameterName, parameterName, option1, option2, option3);
}

void RestServer::addSelectParameter(String parameterName, const char* option1, const char* option2, const char* option3, const char* option4) {
  addSelectParameter(parameterName, parameterName, option1, option2, option3, option4);
}

void RestServer::addSelectParameter(String parameterName, const char* option1, const char* option2, const char* option3, const char* option4, const char* option5) {
  addSelectParameter(parameterName, parameterName, option1, option2, option3, option4, option4);
}

void RestServer::addSelectParameter(String parameterTitle, String parameterName, const char* option1, const char* option2) {
  addSelectParameter(parameterTitle, parameterName, option1, option2, NULL);
}

void RestServer::addSelectParameter(String parameterTitle, String parameterName, const char* option1, const char* option2, const char* option3) {
  addSelectParameter(parameterTitle, parameterName, option1, option2, option3, NULL);
}

void RestServer::addSelectParameter(String parameterTitle, String parameterName, const char* option1, const char* option2, const char* option3, const char* option4) {
  addSelectParameter(parameterTitle, parameterName, option1, option2, option3, option4, NULL);
}

void RestServer::addSelectParameter(String parameterTitle, String parameterName, const char* option1, const char* option2, const char* option3, const char* option4, const char* option5) {
  _html.concat("<label for=\"" + parameterName + "\">" + parameterTitle + "</label>");
  _html.concat("<select id=\"" + parameterName + "\" name=\"" + parameterName + "\">");
    if(option1 != NULL) {
      _html.concat(String("<option value=\"") + option1 + "\">" + option1 + "</option>");
    }
    if(option2!= NULL) {
      _html.concat(String("<option value=\"") + option2 + "\">" + option2 + "</option>");
    }
    if(option3 != NULL) {
      _html.concat(String("<option value=\"") + option3 + "\">" + option3 + "</option>");
    }
    if(option4 != NULL) {
      _html.concat(String("<option value=\"") + option4 + "\">" + option4 + "</option>");
    }
    if(option5 != NULL) {
      _html.concat(String("<option value=\"") + option5 + "\">" + option5 + "</option>");
    }
  _html.concat("</select><br/>");
}

void RestServer::connect(const char* ssid, const char* password, bool printToSerial) {
	if(printToSerial) {
		  Serial.println();
  		Serial.println();
  		Serial.print("Connecting to ");
  		Serial.println(ssid);
	}
	WiFi.begin(ssid, password);
	while (WiFi.status() != WL_CONNECTED) {
    	delay(500);
    	if(printToSerial) {
    		Serial.print(".");
    	}
  	}
  	if (printToSerial) {
  		Serial.println("");
  		Serial.println("WiFi connected");
  	}

  	// Start the server
  	_server.begin();
  	if (printToSerial) {
  		Serial.println("Server started");
		Serial.println(WiFi.localIP());
	}
}

RestClient RestServer::getClient() {
  WiFiClient client = _server.available();
  if (!client) {
    return RestClient();
  }
  while(!client.available()){
    delay(1);
  }
  String req = client.readStringUntil('\r');
  client.flush();
  int indexOfFirstSpace = req.indexOf(" ");
  int indexOfSecondSpace = req.indexOf(" ", indexOfFirstSpace + 1);

  String methodType = req.substring(0, indexOfFirstSpace);
  String paramsAndMethod = req.substring(indexOfFirstSpace + 1, indexOfSecondSpace);

  int indexOfQuestionMark = paramsAndMethod.indexOf("?");
  String params = paramsAndMethod.substring(indexOfQuestionMark + 1);
  String method = paramsAndMethod.substring(0, indexOfQuestionMark);
  if(method.equals("")) {
    method = "/";
  }

  return RestClient(client, methodType, method, params, _html.c_str());
}

RestServer::~RestServer() {

}