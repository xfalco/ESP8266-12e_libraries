#include "RestClient.h"

RestClient::RestClient() {
	_parameterNames = new String[0];
	_parameterValues = new String[0];
}

RestClient::RestClient(WiFiClient& client, String methodType, String method, String parameters, const char* html)
: _client(client),
_methodType(methodType),
_method(method),
_html(html)
{
	int numAmpersands = 0;
	int index = -1;
	while ((index = parameters.indexOf("&", index + 1)) != -1) {
		numAmpersands++;
	}
	_parameterNames = new String[numAmpersands+1];
	_parameterValues = new String[numAmpersands+1];
	numAmpersands = 0;
	int lastIndex = -1;
	index = -1;
	do {
		index = parameters.indexOf("&", index + 1);
		String _parameter;
		if (index == -1) {
			_parameter = parameters.substring(lastIndex + 1);
		} else {
			_parameter = parameters.substring(lastIndex + 1, index);
		}
		int equals = _parameter.indexOf("=");
		_parameterNames[numAmpersands] = _parameter.substring(0, equals);
		_parameterValues[numAmpersands] = _parameter.substring(equals + 1);
		numAmpersands++;
		lastIndex = index;
	} while (lastIndex != -1);
	_numParameters = numAmpersands;
}

String RestClient::getMethod() {
	return _method;
}

String RestClient::getMethodType() {
	return _methodType;
}

String RestClient::getParameterString(String parameterName) {
    for (int index = 0; index < _numParameters; index ++) {
    	if(_parameterNames[index].equals(parameterName)) {
    		return _parameterValues[index];
    	}
    }
}

int RestClient::getParameterInt(String parameterName) {
    for (int index = 0; index < _numParameters; index ++) {
    	if(_parameterNames[index].equals(parameterName)) {
    		return _parameterValues[index].toInt();
    	}
    }
}

void RestClient::print(String message) {
	_client.print(message);
	_client.flush();
}

void RestClient::serveHtml() {
	print(_html);
}

RestClient::operator bool() {
	return !!_client;
}

RestClient::~RestClient() {
	_client.stop();
	delete[] _parameterNames;
	delete[] _parameterValues;
}