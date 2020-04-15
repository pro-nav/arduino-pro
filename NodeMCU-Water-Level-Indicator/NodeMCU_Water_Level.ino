/*****************************************************
IoT Based Water Level Indicator

By:-Pranav Dudhane

This is code for small scale water level indicator made with NodeMCU v1.0
To know about it in details cheak out by blog tiny.cc/pranavdudhane
You may need to make some changes as this code was done just for fun there are no comments inside

You can change the custom made sensor with UltraSonic Sensor and modify code

*********************************************************/


#include <ESP8266WebServer.h>
#include <ESP8266WebServerSecure.h>


#include <ESP8266WiFi.h>

int pin1 = D8;
int pin2 = D7;
int pin3 = D6;
int pin4 = D5;
int pin5 = D2;
int lvl;
int relay_pin = D1;

char* ssid     = "YOUR_SSID";
char* password = "YOUR_PASSWORD";

WiFiServer server(80);

String header;

void setup() {
  pinMode(pin1, INPUT);
  pinMode(pin2, INPUT);
  pinMode(pin3, INPUT);
  pinMode(pin4, INPUT);
  pinMode(pin5, INPUT);
  
  pinMode(relay_pin, OUTPUT);
  
  Serial.begin(115200);
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
  digitalWrite(relay_pin, LOW);
}

void loop(){
  int var1 = 0;
  int var2 = 0;
  int var3 = 0;
  int var4 = 0;
  int var5 = 0;

  WiFiClient client = server.available();   

    if (client){
    Serial.println("New Client.");          
    String currentLine = "";               
    while (client.connected()) {            
      if (client.available()) {             
        char c = client.read();             
        Serial.write(c);                    
        header += c;
        if (c == '\n') {                   
          if (currentLine.length() == 0) {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();

            
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            client.println("<style> body {font-family: monospace; color: #ffffff; margin: 0; padding: 0; display: flex; justify-content: center; align-items: center; height: 100vh; background: rgb(44, 44, 55); } ");
            client.println(".btnG{ background: #00ffff; border:none; height: 40px; width: 50px;} .btnR{ background: #ff0000; border: none; height: 40px; width: 50px;} </style></head>");
            
            
            client.println("<body><div><h1>Tank Water Level</h1><br><hr>");
            client.println("<br><h3>Volume of Tank is 12 Liters Approx.<h3><br>");

            //Code here

 if (digitalRead(pin4) == HIGH){
  var1 =1;
  Serial.print("1");
 }
 if (digitalRead(pin2)==HIGH){
    var2=1;
    Serial.print("2");
 }
 if (digitalRead(pin1)==HIGH){
      var3=1;
      Serial.print("3");
 }
 if(digitalRead(pin5)==HIGH){
      var4=1;
      Serial.print("4");
 }
 if(digitalRead(pin3)==HIGH){
      var5=1;
      Serial.print("5");
 } 
           
            client.println(var1);
            client.println(var2);
            client.println(var3);
            client.println(var4);
            client.println(var5);
            client.println("</div></body></html");
            client.println();
            break;
          } else { 
            currentLine = "";
          }
        } else if (c != '\r') {  
          currentLine += c;     
        }
      }
    }
    header = "";
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}


void sensorFun(){



}

