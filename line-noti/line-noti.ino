#include <ESP8266WiFi.h>
void Line_Notify(String message);

#define WIFI_SSID "<WIFI_SSID>"
#define WIFI_PASSWORD "<WIFI_PASSWORD>"
#define LINE_TOKEN "<LINE_TOKEN>"

String message = "%E0%BA%A1%E0%BA%B5%E0%BA%84%E0%BA%BB%E0%BA%99%E0%BB%80%E0%BA%82%E0%BA%BB%E0%BB%89%E0%BA%B2%E0%BB%80%E0%BA%AE%E0%BA%B7%E0%BA%AD%E0%BA%99%E0%BA%82%E0%BA%AD%E0%BA%87%E0%BB%80%E0%BA%88%E0%BA%BB%E0%BB%89%E0%BA%B2";

#define laser D2
#define LDR A0



void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(laser, OUTPUT);

  WiFi.mode(WIFI_STA);
  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  
  Serial.println();
  Serial.print("connecting");

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
//  Serial.println("Enter !");
//  Line_Notify(message);
}

void loop() {
  static int sensor_value;
  // put your main code here, to run repeatedly:
  digitalWrite(laser, HIGH);
  sensor_value = analogRead(LDR);
  
  float voltage = sensor_value * (5.0 / 1023.0);
//  if (digitalRead(SW) == HIGH) {
//    while(digitalRead(SW) == HIGH) delay(10);
//
//    Serial.println("Enter !");
//    Line_Notify(message);
//    // Serial.println();
//  }
  Serial.println(voltage);
  
  if(voltage <= 1.50){
    delay(100);
    Serial.println("Enter !");
    Line_Notify(message);
    delay(100);
  }
  
  delay(500);
}


void Line_Notify(String message) {
  WiFiClientSecure client;

  if (!client.connect("notify-api.line.me", 443)) {
    Serial.println("connection failed");
    return;   
  }

  String req = "";
  req += "POST /api/notify HTTP/1.1\r\n";
  req += "Host: notify-api.line.me\r\n";
  req += "Authorization: Bearer " + String(LINE_TOKEN) + "\r\n";
  req += "Cache-Control: no-cache\r\n";
  req += "User-Agent: ESP8266\r\n";
  req += "Content-Type: application/x-www-form-urlencoded\r\n";
  req += "Content-Length: " + String(String("message=" + message).length()) + "\r\n";
  req += "\r\n";
  req += "message=" + message;
  // Serial.println(req);
  client.print(req);
    
  delay(20);

  // Serial.println("-------------");
  while(client.connected()) {
    String line = client.readStringUntil('\n');
    if (line == "\r") {
      break;
    }
    //Serial.println(line);
  }
  // Serial.println("-------------");
}
