# ESP32 HTTP Server with PlatformIO & Wokwi 🚀

This project demonstrates how to create an HTTP server using ESP32, PlatformIO, and Wokwi. The server reads temperature and humidity data from a **DHT22 sensor** and displays it on a webpage.

## Steps to Follow 🛠️

### 1️⃣ Install VSCode
Download and install [VSCode](https://code.visualstudio.com/) if you haven't already.

### 2️⃣ Install PlatformIO Extension
- Open VSCode.
- Go to **Extensions** (`Ctrl+Shift+X`).
- Search for **PlatformIO** and install it.

### 3️⃣ Create a PlatformIO Project ⚙️
- Open PlatformIO (`Ctrl+Shift+P` → "PlatformIO: Home").
- Click **New Project**.
- Set:
  - **Board**: ESP32 Wrover
  - **Framework**: Arduino
- Click **Finish**.

### 4️⃣ Register on Wokwi 🔗
- Sign up at [Wokwi](https://wokwi.com/) to simulate your ESP32.

### 5️⃣ Install Wokwi Extension 🛠️
- Open VSCode.
- Install the **Wokwi Extension** from the Extensions Marketplace.

### 6️⃣ Add Code 📝
#### C Code (ESP32 HTTP Server)
```cpp
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
  response += "<style>body { text-align: center; font-family: Arial; } </style></head><body>";
  response += "<h1>ESP32 DHT22 Sensor</h1>";
  response += "<p>&#127777; Temperature: <b>" + String(temperature) + " &#8451;</b></p>";
  response += "<p>&#128167; Humidity: <b>" + String(humidity) + " %</b></p>";
  response += "<button onclick='window.location.reload();'>Refresh</button></body></html>";
  
  server.send(200, "text/html", response);
}

void setup() {
  Serial.begin(115200);
  dht.begin();
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" Connected!");
  Serial.println(WiFi.localIP());

  server.on("/", sendHtml);
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}
```

### 7️⃣ Build the Project 🏗️
- Click **Build** (`Ctrl+Alt+B`).
- Ensure there are no errors.

### 8️⃣ Run Wokwi Simulation 🎮
- Open **Wokwi**.
- Load the ESP32 project.
- Run the simulation and view the **local IP address** in the Serial Monitor.
- Open a browser and visit `http://<ESP32-IP>` to see the webpage!

## Features ✨
- 🌐 **ESP32 HTTP Server**
- 🌡️ **DHT22 Temperature & Humidity Monitoring**
- 🎨 **Styled Web Interface**
- 🔄 **Auto Refresh Button**



---
Happy Coding! 💻🔥

