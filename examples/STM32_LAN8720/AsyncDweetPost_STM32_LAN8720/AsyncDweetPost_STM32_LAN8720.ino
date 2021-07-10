/****************************************************************************************************************************
  AsyncDweetPOST_STM32_LAN8720.ino - Dead simple AsyncHTTPRequest for ESP8266, ESP32 and currently STM32
  
  For ESP8266, ESP32 and STM32 with LAN8720 or built-in LAN8742A Ethernet (Nucleo-144, DISCOVERY, etc)
  
  AsyncHTTPRequest_Generic is a library for the ESP8266, ESP32 and currently STM32 run built-in Ethernet WebServer
  
  Based on and modified from asyncHTTPrequest Library (https://github.com/boblemaire/asyncHTTPrequest)
  
  Built by Khoi Hoang https://github.com/khoih-prog/AsyncHTTPRequest_Generic
  Licensed under MIT license
  
  Copyright (C) <2018>  <Bob Lemaire, IoTaWatt, Inc.>
  This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License 
  as published bythe Free Software Foundation, either version 3 of the License, or (at your option) any later version.
  This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.
  You should have received a copy of the GNU General Public License along with this program.  If not, see <https://www.gnu.org/licenses/>.  
 *****************************************************************************************************************************/

  // Dweet.io POST client. Connects to dweet.io once every ten seconds, sends a POST request and a request body.
  // Shows how to use Strings to assemble path and body

#include "defines.h"

// Select a test server address           
const char POST_ServerAddress[] = "dweet.io";

// use your own thing name here
String dweetName = "/dweet/for/pinA0-Read?";

// 60s = 60 seconds to not flooding the server
#define HTTP_REQUEST_INTERVAL_MS     10000

#include <AsyncHTTPRequest_Generic.h>           // https://github.com/khoih-prog/AsyncHTTPRequest_Generic

#include <Ticker.h>                             // https://github.com/sstaub/Ticker

AsyncHTTPRequest request;

void sendRequest(void);

// Repeat forever, millis() resolution
Ticker sendHTTPRequest(sendRequest, HTTP_REQUEST_INTERVAL_MS, 0, MILLIS); 

void sendRequest(void)
{ 
  static bool requestOpenResult;
  
  if (request.readyState() == readyStateUnsent || request.readyState() == readyStateDone)
  {      
    String postData = "sensorValue="; 
    postData += analogRead(A0);

    Serial.println("\nMaking new POST request");

    requestOpenResult = request.open("POST", (POST_ServerAddress + dweetName + postData).c_str() );
    
    if (requestOpenResult)
    {
      // Only send() if open() returns true, or crash
      request.send();
    } 
    else
    {
      Serial.println("Can't send bad request");
    }
  }
  else
  {
    Serial.println("Can't send request");
  }
}

void parseResponse(String responseText)
{
  /*
    Typical response is:
    {"this":"succeeded",
    "by":"getting",
    "the":"dweets",
    "with":[{"thing":"my-thing-name",
      "created":"2016-02-16T05:10:36.589Z",
      "content":{"sensorValue":456}}]}

    You want "content": numberValue
  */
  // now parse the response looking for "content":
  int labelStart = responseText.indexOf("content\":");
  // find the first { after "content":
  int contentStart = responseText.indexOf("{", labelStart);
  // find the following } and get what's between the braces:
  int contentEnd = responseText.indexOf("}", labelStart);
  String content = responseText.substring(contentStart + 1, contentEnd);
  
  Serial.println(content);

  // now get the value after the colon, and convert to an int:
  int valueStart = content.indexOf(":");
  String valueString = content.substring(valueStart + 1);
  int number = valueString.toInt();
  
  Serial.print("Value string: ");
  Serial.println(valueString);
  Serial.print("Actual value: ");
  Serial.println(number);
}

void requestCB(void* optParm, AsyncHTTPRequest* request, int readyState)
{
  (void) optParm;
  
  if (readyState == readyStateDone)
  {
    String responseText = request->responseText();
    
    Serial.println("\n**************************************");
    //Serial.println(request->responseText());
    Serial.println(responseText);
    Serial.println("**************************************");

    parseResponse(responseText);
      
    request->setDebug(false);
  }
}

void setup(void) 
{
  Serial.begin(115200);
  delay(2000);
  
  Serial.println("\nStart AsyncDweetPOST_STM32_LAN8720 on " + String(BOARD_NAME));
  Serial.println(ASYNC_HTTP_REQUEST_GENERIC_VERSION);

  // start the ethernet connection and the server
  // Use random mac
  uint16_t index = millis() % NUMBER_OF_MAC;

  // Use Static IP
  //Ethernet.begin(mac[index], ip);
  // Use DHCP dynamic IP and random mac
  Ethernet.begin(mac[index]);

  Serial.print(F("AsyncHTTPRequest @ IP : "));
  Serial.println(Ethernet.localIP());
  Serial.println();

  request.setDebug(false);
  
  request.onReadyStateChange(requestCB);
  sendHTTPRequest.start(); //start the ticker.
}

void loop(void) 
{
  sendHTTPRequest.update();
}
