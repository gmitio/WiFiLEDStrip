#include "leds.h"
#include <WiFi.h>
#include <ArduinoJson.h>
#include "ESPAsyncWebServer.h"
#include "config.h"

const char* ssid     = "SSIDName";
const char* password = "WiFiKey";

//WiFiServer server(80);
AsyncWebServer server(80);
int value = 0;
int mode = -1;
void setup() { 
    Serial.begin(9600);
    delay(10);


    // We start by connecting to a WiFi network

    Serial.println();
    Serial.println();
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
    
    //server.begin();
    server.on("/post", HTTP_POST, [](AsyncWebServerRequest * request) {
      int params = request->params();
      printf("Num of params saved: %d\r\n", params);
      for (int i=0; i<params; i++) {
        AsyncWebParameter* p = request->getParam(i);
        if(p->isPost()) {
          printf("Post[%s] received: %s with size: %u\r\n", p->name().c_str(), p->value().c_str(), p->size());
        }
      } 

      if(request->hasParam("body", true)) {

        // Set up JSON document, put this here because passing through the lambda crashes the system--do this in a better way
        StaticJsonDocument<200> doc;  // 200-byte JSON document

        AsyncWebParameter* p = request->getParam("body", true);
        String json = p->value();

        DeserializationError error = deserializeJson(doc, json);
          if (error) {
            Serial.print(F("deserializeJson() failed: "));
            Serial.println(error.f_str());
            //return;
          }


        mode = doc["LedMode"].as<int>();

        printf("Mode captured via JSON is: %d\r\n", mode);

        AsyncWebServerResponse *response = request->beginResponse(200, "application/json", "{'msg':'done'}");
        request->send(response);

      }
    });
      // NULL,
      // [](AsyncWebServerRequest * request, uint8_t *data, size_t len, size_t index, size_t total) {
        
      //   for(size_t i=0; i<len; i++) {
      //     Serial.write(data[i]);
      //   }

      //   Serial.println();
      //   request->send(200);
      // }
    // );

  server.begin();
  LEDSetup();
}


void loop() { 


  //  WiFiClient client = server.available();   // listen for incoming clients

  // if (client) {                             // if you get a client,
  //   Serial.println("New Client.");           // print a message out the serial port
  //   String currentLine = "";                // make a String to hold incoming data from the client
  //   while (client.connected()) {            // loop while the client's connected
  //     if (client.available()) {             // if there's bytes to read from the client,
  //       char c = client.read();             // read a byte, then
  //       Serial.write(c);                    // print it out the serial monitor
  //       if (c == '\n') {                    // if the byte is a newline character

  //         // if the current line is blank, you got two newline characters in a row.
  //         // that's the end of the client HTTP request, so send a response:
  //         if (currentLine.length() == 0) {
  //           // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
  //           // and a content-type so the client knows what's coming, then a blank line:
  //           client.println("HTTP/1.1 200 OK");
  //           client.println("Content-type:text/html");
  //           client.println();

  //           // the content of the HTTP response follows the header:
  //           client.print("Click <a href=\"/H\">here</a> to steadily rotate through colors.<br>");
  //           client.print("Click <a href=\"/L\">here</a> to do LED chase pattern.<br>");

  //           // The HTTP response ends with another blank line:
  //           client.println();
  //           // break out of the while loop:
  //           break;
  //         } else {    // if you got a newline, then clear currentLine:
  //           currentLine = "";
  //         }
  //       } else if (c != '\r') {  // if you got anything else but a carriage return character,
  //         currentLine += c;      // add it to the end of the currentLine
  //       }

  //       // Check to see if the client request was "GET /H" or "GET /L":
  //       if (currentLine.endsWith("GET /H")) {
  //         //digitalWrite(5, HIGH);               // GET /H turns the LED on
  //         mode = 0;
  //       }
  //       if (currentLine.endsWith("GET /L")) {
  //         mode = 1;
  //         //digitalWrite(5, LOW);                // GET /L turns the LED off
  //       }
  //     }
  //     // if(mode == 0) {
  //     //   steady_rotation();
  //     // }
  //     // if(mode == 1) {
  //     //   led_chase();
  //     // }
  //   }
  //   // close the connection:
  //   client.stop();
  //   Serial.println("Client Disconnected.");


  // }
  if(mode == 0) {
    steady_rotation();
  }
  if(mode == 1) {
    led_chase();
  }
  //steady_rotation();
  //led_chase();
  //printf("Serial Monitor Test, CNT: %d\r\n", rot_count);
}