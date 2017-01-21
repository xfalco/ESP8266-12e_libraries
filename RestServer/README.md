A set of wrappers around the ESP8266 WiFi library to facilitate building and servicing a REST interface.

WARNING: This library assumes relatively infrequent requests (compared to loop cycles), and is thus not designed for processing speed

RestServer wraps the WiFiServer class with additional support for building out an index page listing the REST interface supported by the application.
example:
```
  server.startMethod("My Method", "/myMethod");
  server.addParameter("foo");
  server.addParameter("blah");
  server.endMethod();
```
will construct a default HTML page with a form supporting a `foo` and a `blah` label.

RestClient (accessible via the `RestServer:getClient` method) in turn wraps a WiFiClient with additional functionality enabling access to the REST interface accessed. For example, to access the parameters sent to the above method:
```
RestClient client = server.getClient();
  if (!client) {
    return;
  }
  if(client.getMethod().equals("/")) {
    client.serveHtml();
    return;
  }
  Serial.println(client.getMethodType());
  Serial.println(client.getMethod());
  Serial.println(client.getParameterInt("foo"));
  Serial.println(client.getParameterString("blah"));
```
