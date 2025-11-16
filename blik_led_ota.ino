#include <ESP8266WiFi.h>
const char* ssid = "TOPNET_1618";
const char* password = "1yk2bho2u4";

WiFiServer server(80);

int ledPin = 2;

void setup(){
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("Connected");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());  

  server.begin();
}

void loop(){
  WiFiClient client = server.available();
  if (client) {
    String request = client.readStringUntil('\r');
    client.flush();

    if (request.indexOf("/LED=ON") != -1) {
      digitalWrite(ledPin, HIGH);
    }
    if (request.indexOf("/LED=OFF") != -1) {
      digitalWrite(ledPin, LOW);
    }

    client.print("HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n");
    client.print("<!DOCTYPE HTML><html><body>");
    client.print("<p>LED Control:</p>");
    client.print("<a href=\"/LED=ON\">Turn On</a><br>");
    client.print("<a href=\"/LED=OFF\">Turn Off</a><br>");
    client.print("</body></html>");
    client.stop();
  }
}
