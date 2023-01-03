#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ArduinoJson.h>
#include <FS.h>


ESP8266WebServer server(80);



//------------------- SOFT-AP SETTINGS --------------------------
const char *ssidConf = "SoftAP";
const char *passConf = "admin123456";



//-------------- FUNCTION TO SCAN AVAILABLE NETWORKS RETURN JSON----------------
void scanAvailableNetworks() {
  
  StaticJsonDocument<1024> jsonDocument;
  JsonArray jsonArray = jsonDocument.to<JsonArray>();
  
  int listOfNetwoks = WiFi.scanNetworks();
  String networksItems = "";
  
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



//-------------- FUNCTION TO RETURN BOARD INFO----------------
void getNodeInfo() {

  StaticJsonDocument<1024> jsonDocument;
  
  jsonDocument["ssid"] = ssidConf;
  jsonDocument["ip"] = WiFi.softAPIP();
  jsonDocument["mac"] = WiFi.softAPmacAddress();
  
  String jsonBuffer;
  serializeJson(jsonDocument, jsonBuffer);
  
  server.send(200, "application/json", jsonBuffer);
      
}  



//-------------- FUNCTION TO SAVE WIFI SETTINGS----------------
void setWifiSettings() {
  
  String data = server.arg("plain");
  DynamicJsonDocument jBuffer(1024);
  DeserializationError error = deserializeJson(jBuffer, data);

  File configFile = SPIFFS.open("/config.json", "w");
  serializeJson(jBuffer, configFile);
  configFile.close();
  
  server.send(200, "application/json", "{\"status\" : \"ok\"}");
  delay(500);
 
}



//-------------- FUNCTION TO SET CONFIG MODE ----------------
void setConfigMode() {
  
  WiFi.softAP(ssidConf, passConf);
  Serial.println("WebServer is running on: ");
  Serial.print(WiFi.softAPIP());
  Serial.println("");

  server.on("/", serveHTML);
  server.on("/styles.css", serveStyles);
  server.on("/main.js", serveJavaScript);
  server.on("/favicon.svg", serveFavicon);
  

  // API END POINTS
  server.on("/nodeinfo", HTTP_GET, getNodeInfo);  
  server.on("/wifiscan", HTTP_GET, scanAvailableNetworks);  
  server.on("/wifisettings", HTTP_POST, setWifiSettings);
  
  server.begin();

  while (true) {
    server.handleClient();
  }

}


//-------------- FUNCTION TO SET WIFI CONECTION----------------
void wifiConnect() {

  //check for stored credentials
  if(SPIFFS.exists("/config.json")) {
    
    const char * _ssid = "", *_pass = "";
    
    File configFile = SPIFFS.open("/config.json", "r");
    
    if(configFile) {
    
      size_t size = configFile.size();
      std::unique_ptr<char[]> buf(new char[size]);
      configFile.readBytes(buf.get(), size);
      configFile.close();
      
      DynamicJsonDocument jsonBuffer(1024);
      DeserializationError error = deserializeJson(jsonBuffer, buf.get());
      
      if(error) {
        return;
      } else {
      
        _ssid = jsonBuffer["ssid"];
        _pass = jsonBuffer["password"];
        
        WiFi.mode(WIFI_STA);
        WiFi.begin(_ssid, _pass);
        
        int contconexion = 0;

        while (WiFi.status() != WL_CONNECTED and contconexion <10) {
          ++contconexion;
          Serial.print(".");
          delay(300);
        }

        if (WiFi.status() != WL_CONNECTED) {
          Serial.print("");
          Serial.println("Connection error");
        } else {
          Serial.print("");
          Serial.println("IP Address: ");
          Serial.print(WiFi.localIP());
          Serial.println("");     
        }           

      }
    }
  }
}



//-------------- MAIN FUNCTION ----------------

void setup(){
  
  Serial.begin(115200);
  SPIFFS.begin();
  setConfigMode();
      
}


//-------------- LOOP FUNCTION ----------------
void loop(){
  
}




// Route for index HTML / SoftAP
void serveHTML(){
  File html = SPIFFS.open("/index.html","r");
  server.streamFile(html, "text/html");
  html.close();
}

// Route for css styles / SoftAP
void serveStyles(){
  File styles = SPIFFS.open("/styles.css","r");
  server.streamFile(styles, "text/css");
  styles.close();
}


// Route for javascript file / SoftAP
void serveJavaScript(){
  File javascript = SPIFFS.open("/main.js","r");
  server.streamFile(javascript, "text/javascript");
  javascript.close();
}


// Route for favicon file / SoftAP
void serveFavicon(){
  File favicon = SPIFFS.open("/favicon.svg","r");
  server.streamFile(favicon, "image/svg+xml");
  favicon.close();
}
