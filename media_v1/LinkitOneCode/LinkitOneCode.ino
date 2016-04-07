
/*
  WiFi Web Server

 A simple web server that a repeated counter

 Change the macro WIFI_AP, WIFI_PASSWORD and WIFI_AUTH accordingly.

 created 13 July 2010
 by dlf (Metodo2 srl)
 modified 31 May 2012
 by Tom Igoe
 modified 20 Aug 2014
 by MediaTek Inc.
 */
#include <LTask.h>
#include <LWiFi.h>
#include <LWiFiServer.h>
#include <LWiFiClient.h>
#include <ArduinoJson.h>

#define WIFI_AP "charif"
#define WIFI_PASSWORD "mahmoudi"
#define WIFI_AUTH LWIFI_WPA  // choose from LWIFI_OPEN, LWIFI_WPA, or LWIFI_WEP according to your WiFi AP configuration

// Enabe debug tracing to Serial port.
#define DEBUGGING
// Here we define a maximum framelength to 64 bytes. Default is 256.
#define MAX_FRAME_LENGTH 64
// Define how many callback functions you have. Default is 1.
#define CALLBACK_FUNCTIONS 1
#define CONNECTION_CLOSE -1

#include <WebSocketServer.h>

LWiFiServer server(80);
WebSocketServer webSocketServer;
DynamicJsonBuffer  jsonBuffer;

void setup()
{
  
  LWiFi.begin();
  // Open serial communications and wait for port to open:
  Serial.begin(9600);

  //StaticJsonBuffer<500> jsonBuffer;

  // StaticJsonBuffer allocates memory on the stack, it can be
  // replaced by DynamicJsonBuffer which allocates in the heap.
  // It's simpler but less efficient.
  //
  // DynamicJsonBuffer  jsonBuffer;
   
  // keep retrying until connected to AP
  Serial.println("Connecting to AP");
  while (0 == LWiFi.connect(WIFI_AP, LWiFiLoginInfo(WIFI_AUTH, WIFI_PASSWORD)))
  {
    Serial.println("retrying until connected to AP");
     int numOfAP = LWiFi.scanNetworks();
    Serial.print("number of WiFi AP found:");
    Serial.println(numOfAP);
    for(uint8_t i = 0; i<numOfAP; i++){
      Serial.print("Access point SSID : ");
      Serial.println(LWiFi.SSID(i));
      
    }
    delay(1000);
  }

  printWifiStatus();

  Serial.println("Start Server");
  server.begin();
  Serial.println("Server Started");
}

int loopCount = 0;

void loop()
{

// put your main code here, to run repeatedly:
  delay(500);
  LWiFiClient client = server.available();
  if (client&& webSocketServer.handshake(client))
  {
    Serial.println("new  client");
    
    while (client.connected())
    {
      if (client.available())
      {
          String data;
          data = webSocketServer.getData();

          int value = 0;
          if (data.length() > 0) {
            value = handleClientData(data);
          }
    
          sendClientData(value);
          if(value == CONNECTION_CLOSE){
            break;
          }
      }
    }
    
    
    // give the web browser time to receive the data
    delay(500);

    // close the connection:
    Serial.println("close connection");
    client.stop();
    Serial.println("client disconnected");
  }

}

int handleElem(JsonObject& e) {
   // Fetch values.
  //
  // Most of the time, you can rely on the implicit casts.
  // In other case, you can do root["time"].as<long>();
  int pin = e["pin"][0];
  int pin1 = e["pin"][1];
  int pin2 = e["pin"][2];
  bool dir = e["dir"];
  int value = e["value"] ;


 Serial.print("pin : ");
 Serial.println(pin);
 Serial.print("pin1 : ");
 Serial.println(pin1);
 Serial.print("pin2 : ");
 Serial.println(pin2);
 Serial.print("dir : ");
 Serial.println(dir);
 Serial.print("value : ");
 Serial.println(value);
 
  pinMode(pin, OUTPUT);
  pinMode(pin1, OUTPUT);
  pinMode(pin2, OUTPUT);

    analogWrite(pin, value);
  digitalWrite(pin1, ! dir);
  digitalWrite(pin2, dir);
}
int handleClientData(String &dataString) {


  JsonObject& root = jsonBuffer.parseObject(dataString);

  Serial.print("Data received : ");
  Serial.println(dataString);
  // Test if parsing succeeds.
  if (!root.success()) {
    Serial.println("parseObject() failed");
    return CONNECTION_CLOSE;
  }

  handleElem(root["left"]);
  handleElem(root["right"]);
    
  return 1;
}

// send the client the analog value of a pin
void sendClientData(int value) {
  String data = "a";
  
 // pinMode(pin, INPUT);
  //data += String(pin) + String(analogRead(pin));
  webSocketServer.sendData(String(value));  
}
void printWifiStatus()
{
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(LWiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = LWiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  Serial.print("subnet mask: ");
  Serial.println(LWiFi.subnetMask());

  Serial.print("gateway IP: ");
  Serial.println(LWiFi.gatewayIP());

  // print the received signal strength:
  long rssi = LWiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}


