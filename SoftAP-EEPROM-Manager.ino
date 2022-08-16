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


//-------------- WEB APP HTML DECLARATIONS ----------------
// String networksItems = ""; // available networks items set by availabeNetworks function

//-------------- WEB APP INIT
String initHead = "<!DOCTYPE html>"
"<html>"
"<head>"
"<title>Configuration</title>"
"<meta charset='UTF-8'>"
"</head>"
"<body>";

//-------------- FORM
String htmlForm = "</form>"
"<form action='saveConfig' method='get'>"
"SSID:<br><br>"
"<input class='input1' name='ssid' type='text'><br>"
"PASSWORD:<br><br>"
"<input class='input1' name='pass' type='password'><br><br>"
"<input class='boton' type='submit' value='GUARDAR'/><br><br>"
"</form>"

//-------------- WEB APP END
String endHtml = "</body>"
"</html>";


//-------------- FUNCTION TO SET WIFI CONECTION ----------------
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


//-------------- FUNCTION TO SCAN AVAILABLE NETWORKS ----------------
String networksItems = "";

void availabeNetworks() {  
  int listOfNetwoks = WiFi.scanNetworks(); // return available networks

  if (listOfNetwoks == 0) {
    networksItems = "There are not available networks";
  } else {
    networksItems = "";
    
    for (int i = 0; i < networksItems; ++i)
    {
      networksItems = (networksItems) + "<p>" + String(i + 1) + ": " + WiFi.SSID(i) + " (" + WiFi.RSSI(i) + ")" + " </p>\r\n";
      delay(10);
    }
  }
  
}


//-------------- SERVER SETTINGS ----------------
ESP8266WebServer server(80);

void webApp() {
  server.send(200, "text/html", initHead + networksItems + htmlForm + endHtml); 
}


//-------------- FUNCTION TO SET CONFIG MODE ----------------
void setConfig() {
  WiFi.softAP(ssidConf, passConf);
  WiFi.softAPConfig(ip, gateway, subnet);
  Serial.println("WebServer is running on:");
  Serial.println(WiFi.softAPIP());
  Serial.println();

  availabeNetworks();

  // API END POINTS
  server.on("/", webApp); //esta es la pagina de configuracion
  server.on("/guardar_conf", saveConfig); //Graba en la eeprom la configuracion

  server.begin();

  while (true) {
      server.handleClient();
  }

}



void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
