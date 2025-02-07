#include <WiFi.h>
#include <WebServer.h>
#include "DHT.h"

#define WIFI_SSID "Wokwi-GUEST"
#define WIFI_PASSWORD ""
#define DHTPIN 18
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);
WebServer server(80);

void sendHtml() {
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  
  String response = "<!DOCTYPE html><html><head><title>ESP32 DHT22</title>";
  response += "<style>";
  response += "body { font-family: Arial, sans-serif; text-align: center; background: linear-gradient(to right, #4facfe, #00f2fe); color: white; margin: 0; padding: 0; }";
  response += ".container { max-width: 400px; margin: 50px auto; background: rgba(0, 0, 0, 0.7); padding: 20px; border-radius: 15px; box-shadow: 0px 4px 10px rgba(0,0,0,0.2); }";
  response += "h1 { font-size: 24px; }";
  response += "p { font-size: 20px; margin: 10px 0; }";
  response += ".refresh { display: inline-block; padding: 10px 20px; font-size: 18px; background: #ff7e5f; border: none; color: white; cursor: pointer; border-radius: 5px; transition: 0.3s; }";
  response += ".refresh:hover { background: #feb47b; transform: scale(1.1); }";
  response += "</style></head><body>";

  response += "<div class='container'>";
  response += "<h1>ESP32 DHT22 Sensor</h1>";
  response += "<p>&#127777; Temperature: <b>" + String(temperature) + " &#8451;</b></p>";  // 🌡
  response += "<p>&#128167; Humidity: <b>" + String(humidity) + " %</b></p>";  // 💧
  response += "<button class='refresh' onclick='window.location.reload();'>&#128260; Refresh</button>";
  response += "</div>";

  response += "</body></html>";

  server.send(200, "text/html", response);
}

void setup() {
  Serial.begin(115200);
  dht.begin();
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" Connected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  server.on("/", sendHtml);
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}
