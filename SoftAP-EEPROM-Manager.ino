#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <EEPROM.h>


//------------------- ENVIRONMENT VARIABLES --------------------------
char ssid_OnEEPROM[50];      
char pass_OnEEPROM[50];


//------------------- SOFT-AP SETTINGS --------------------------
const char *ssidConf = "admin";
const char *passConf = "admin";

IPAddress ip(192, 168, 1, 1);
IPAddress gateway(192, 168, 1, 254);
IPAddress subnet(255, 255, 255, 0);


//-------------- FUNCTION SET WIFI CONECTION ----------------
void setWifi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid_OnEEPROM, pass_OnEEPROM);
  
  while (WiFi.status() != WL_CONNECTED)
  {
      Serial.print(".");
      delay(300);
  }

  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

}

//-------------- FUNCTION SET CONFIG MODE ----------------
void setConfig() {
   WiFi.softAP(ssidConf, passConf);
   WiFi.softAPConfig(ip, gateway, subnet);
   Serial.println("WebServer is running on:");
   Serial.println(WiFi.softAPIP());
   Serial.println();


}

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
