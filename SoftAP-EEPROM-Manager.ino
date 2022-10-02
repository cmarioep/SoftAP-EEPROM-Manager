#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ArduinoJson.h>
#include <EEPROM.h>


unsigned long previousMillis = 0;
int contconexion = 0;

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
char ssidSTA[50];      
char passSTA[50];


//------------------- SOFT-AP SETTINGS --------------------------
const char *ssidConf = "SoftAP";
const char *passConf = "admin123456";

//IPAddress ip(192, 168, 0, 1);
//IPAddress gateway(192, 168, 0, 254);
//IPAddress subnet(255, 255, 255, 0);


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
"</form>";

//-------------- WEB APP END
String endHtml = "</body>"
"</html>";


//-------------- FUNCTION TO SET WIFI CONECTION ----------------
void setWifi() {
  
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssidSTA, passSTA);
  
  while (WiFi.status() != WL_CONNECTED and contconexion <10)
  {
    ++contconexion;
      Serial.print(".");
      delay(300);
  }

  Serial.print("");
  Serial.println("Connected with IP: ");
  Serial.print(WiFi.localIP());
  Serial.println("");

}


//-------------- FUNCTION TO SCAN AVAILABLE NETWORKS ----------------
String networksItems = "";

void scanForNetworks() {  
  int listOfNetwoks = WiFi.scanNetworks(); // return available networks

  if (listOfNetwoks == 0) {
    networksItems = "There are not available networks";
  } else {
  
    for (int i = 0; i < listOfNetwoks; i++) {
      networksItems = (networksItems) + "<p>" + String(i + 1) + ": " + WiFi.SSID(i) + " (" + WiFi.RSSI(i) + ")" + " </p>\r\n";
      delay(10);      
    }
    
  }
  
}


//-------------- SERVER SETTINGS ----------------
WiFiClient espClient;
ESP8266WebServer server(80);

void webApp() {
  server.send(200, "text/html", initHead + networksItems + htmlForm + endHtml); 
}


//-------------- FUNCTION TO SCAN AVAILABLE NETWORKS RETURN JSON----------------
void scanAvailableNetworks() {

  StaticJsonDocument<1024> jsonDocument;
  JsonArray jsonArray = jsonDocument.to<JsonArray>();

  int listOfNetwoks = WiFi.scanNetworks();
  String networksItems ="";

  if (listOfNetwoks == 0) {
    networksItems = "There are not available networks";
  } else {
  
    for (int i = 0; i < listOfNetwoks; i++) {

      StaticJsonDocument<128> tmpJsonDocument;
      JsonObject tmpObject = tmpJsonDocument.to<JsonObject>();

      tmpObject["id"] = i;
      tmpObject["ssid"] = WiFi.SSID(i);
      tmpObject["rssi"] = WiFi.RSSI(i);

      jsonArray.add(tmpObject);

      delay(10);      
    }

    String jsonBuffer;
    serializeJson(jsonDocument, jsonBuffer);
    server.send(200, "application/json", jsonBuffer);
      
  }  

}


//-------------- FUNCTION TO SET CONFIG MODE ----------------
void setConfigMode() {
  
  WiFi.softAP(ssidConf, passConf);
//  WiFi.softAPConfig(ip, gateway, subnet);
  Serial.println("WebServer is running on: ");
  Serial.print(WiFi.softAPIP());
  Serial.println("");

  scanForNetworks();

  // API END POINTS
  server.on("/", webApp); 
  server.on("/saveConfig", saveConfig);
  server.on("/wifiscan", HTTP_GET, scanAvailableNetworks);

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
  

  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(D5, INPUT_PULLUP);
 
  Serial.begin(115200);

  digitalWrite(LED_BUILTIN, LOW);
  delay(5000);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(100);
  digitalWrite(LED_BUILTIN, LOW);
  delay(100);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(100);
  digitalWrite(LED_BUILTIN, LOW);
  delay(100);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(100);
  digitalWrite(LED_BUILTIN, LOW);
  delay(100);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(100);
  digitalWrite(LED_BUILTIN, LOW);
  delay(5000);
  digitalWrite(LED_BUILTIN, HIGH);

  EEPROM.begin(512);
  
  if (digitalRead(D5) == 0) {
    setConfigMode();
  }
  
  readData(0).toCharArray(ssidSTA, 50);
  readData(50).toCharArray(passSTA, 50);
    
  setWifi();

}

void loop() {

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= 5000) { //envia la temperatura cada 5 segundos
    previousMillis = currentMillis;
    Serial.println("Funcionado...");
    Serial.println(ssidSTA);
    Serial.println(passSTA);
  }
}
