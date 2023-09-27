#include <WiFi.h>
#include <WiFiClient.h>


const char* host = "192.168.145.73";
const uint16_t port = 8081;

WiFiClient checkClient;


char ssid[] = "Spot";
char pass[] = "mypassword";
void setup() {
  Serial.begin(115200);
  // put your setup code here, to run once:
  //  Serial.println("Connecting to " + ssid);
  WiFi.mode(WIFI_STA);
  if (pass && strlen(pass)) {
    WiFi.begin(ssid, pass);
  } else {
    WiFi.begin(ssid);
  }
  while (WiFi.status() != WL_CONNECTED) {
    Serial.println("Connecting...");
    delay(500);
  }

  Serial.println("Connected to WiFi");

  IPAddress myip = WiFi.localIP();
  (void)myip; // Eliminate warnings about unused myip
  Serial.println("Connected to WiFi");
}

long prevTime;

void loop() {
  // put your main code here, to run repeatedly:
  if (!checkClient.connected()) {
    Serial.println("Connecting to server...");
    if (checkClient.connect(host, port)) {
      Serial.println("Connected to server");
    }
  }

  if (millis()- prevTime> 2000) {
    if (checkClient.connected()) {
      checkClient.println("hello from Esp32");
    }
    prevTime = millis();
  }
}
