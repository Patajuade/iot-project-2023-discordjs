
//Include Lib for Arduino to Nodemcu
#include <SoftwareSerial.h>
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

//D6 = Rx & D5 = Tx
SoftwareSerial statusNode(D5, D3);
SoftwareSerial resultNode(D7, D6);

ESP8266WebServer server;

char* ssid = "Pouet";
char* password = "niquetamere";

//Your Domain name with URL path or IP address with path
String serverName = "http://connected-dice-api.azurewebsites.net/roll";

void setup() {
  // Initialize Serial port
  Serial.begin(115200);

  WiFi.begin(ssid,password);
  
  statusNode.begin(115200);
  resultNode.begin(115200);
  while (!Serial) continue;

  while(WiFi.status()!=WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  //server.on("/",handleIndex);
  server.begin();
}

void sendNumberToNodeMCU(int num)
{
  StaticJsonBuffer<1000> jsonBuffer;
  JsonObject &data = jsonBuffer.createObject();
  data["result"] = num;
  Serial.print("sendNumberToNodeMCU");
  Serial.println(num);

  // Send data to NodeMCU
  data.printTo(resultNode);
  jsonBuffer.clear();
}


int extractNumberFromString(String result){
  String resultString = result;
  String resultStringArray[2];
        int i = 0;
        int j = 0;
        while(resultString[i] != '\0'){
          if(resultString[i] == ':'){
            resultStringArray[j] = resultString.substring(0,i);
            resultStringArray[j+1] = resultString.substring(i+1,resultString.length());
            break;
          }
          i++;
        }
        resultStringArray[0].remove(0,1);
        resultStringArray[1].remove(resultStringArray[1].length()-1,1);

        int resultInt = resultStringArray[1].toInt();
        return resultInt;    
}

void loop() {
  StaticJsonBuffer<1000> jsonBuffer;
  JsonObject& data = jsonBuffer.parseObject(statusNode);
  
  if (data == JsonObject::invalid()) {
    jsonBuffer.clear();
  }

  int result = data["status"];
  //Serial.println(result);

   if(WiFi.status()== WL_CONNECTED && result == -1){
      WiFiClient client;
      HTTPClient http;

      String serverPath = serverName;// + "?result=" + result;
      
      // Your Domain name with URL path or IP address with path
      http.begin(client, serverPath.c_str());
      
      // Send HTTP GET request
      int httpResponseCode = http.GET();
      
      if (httpResponseCode>0) {
        String payload = http.getString();
        int num = extractNumberFromString(payload);
        sendNumberToNodeMCU(num);
      }
      else {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
      }
      // Free resources
      http.end();
    }
    else {
      //Serial.println("WiFi Disconnected");
    }
}
