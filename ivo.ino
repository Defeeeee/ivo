#include <WiFi.h>
#include <WebServer.h>

const char* apSSID = "espdefe";
const char* apPassword = "esptest1";

#define RELE1 15
#define RELE2 4

WebServer server(80);

int relay1State = LOW;
int relay2State = LOW;

void handleRoot() {
  String html = "<!DOCTYPE html><html><head><title>Sensor Readings</title></head><body>";
  html += "<button onclick=\"toggleRelay()\">Toggle Relay 1</button>";
  html += "<script>";
  html += "function toggleRelay() {";
  html += "  var xhttp = new XMLHttpRequest();";
  html += "  xhttp.open(\"GET\", \"/toggle\", true);";
  html += "  xhttp.send();";
  html += "}";
  html += "</script>";

  html += "<button onclick=\"toggleRelay1()\">Toggle Relay 2</button>";
  html += "<script>";
  html += "function toggleRelay1() {";
  html += "  var xhttp = new XMLHttpRequest();";
  html += "  xhttp.open(\"GET\", \"/toggle1\", true);";
  html += "  xhttp.send();";
  html += "}";
  html += "</script>";

  html += "</body></html>";

  server.send(200, "text/html", html);
}

void handleToggle() {
  relay1State = !relay1State;
  digitalWrite(RELE1, relay1State);
  server.send(200, "text/plain", "Toggled Relay 1");
}

void handleToggle1() {
  relay2State = !relay2State;
  digitalWrite(RELE2, relay2State);
  server.send(200, "text/plain", "Toggled Relay 2");
}

void setup() {
  Serial.begin(115200);

  WiFi.softAP(apSSID, apPassword);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);

  Serial.print("AP SSID: ");
  Serial.println(apSSID);
  Serial.print("AP Password: ");
  Serial.println(apPassword);

  server.on("/", handleRoot);
  server.on("/toggle", handleToggle);
  server.on("/toggle1", handleToggle1);
  server.begin();
  Serial.println("HTTP server started");

  pinMode(RELE1, OUTPUT);
  pinMode(RELE2, OUTPUT);
}

void loop() {
  server.handleClient();
}