#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <EEPROM.h>


//------------------- FUNCTION TO SAVE DATA ON EEPROM --------------------------
void saveData(int addr, String data) {
  
  int dataLength = data.length(); 
  char inchar[50]; 
  data.toCharArray(inchar, dataLength + 1);
  
  for (int i = 0; i < dataLength; i++) {
    EEPROM.write(addr+i, inchar[i]);
  }
  
  for (int i = dataLength; i < 50; i++) {
    EEPROM.write(addr+i, 255);
  }
  
  EEPROM.commit();
  
}


//------------------- FUNCTION TO READ DATA ON EEPROM --------------------------
String readData(int addr) {
  
   byte singleData;
   String stringData;
   
   for (int i = addr; i < addr + 50; i++) {
      singleData = EEPROM.read(i);
      
      if (singleData != 255) {
        stringData += (char)singleData;
      }
      
   }
   
   return stringData;
}


//------------------- ENVIRONMENT VARIABLES ON EEPROM --------------------------
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
  server.on("/", webApp); 
  server.on("/guardar_conf", saveConfig);

  server.begin();

  while (true) {
      server.handleClient();
  }

}


//-------------- FUNCTION TO SAVE DATA FROM WEB APP TO EEPROM ----------------
void saveConfig() {
   
  // get the values from web app form and save them on EEPROM memory
  saveData(0,server.arg("ssid"));
  saveData(50,server.arg("pass"));

  networksItems = "SETTING WERE SAVED... REBOOT YOUR DEVICE";
  webApp();
  
}


//-------------- MAIN FUNCTION ----------------
void setup() {
  
  Serial.begin(115200);
  Serial.print("....");
  delay(1000);

  EEPROM.begin(512);

  pinMode(D5, INPUT);
  
  if (digitalRead(D5) == 0) {
    setConfig();
  } else {
    
      readDatar(0).toCharArray(ssid, 50);
      leerreadData(50). toCharArray(pass, 50);

      setWifi();
  }

}

void loop() {
  // put your main code here, to run repeatedly:

}
