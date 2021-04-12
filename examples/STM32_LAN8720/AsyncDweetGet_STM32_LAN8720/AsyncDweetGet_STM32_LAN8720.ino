/****************************************************************************************************************************
  AsyncDweetGET_STM32_LAN8720.ino - Dead simple AsyncHTTPRequest for ESP8266, ESP32 and currently STM32
  
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
 
  Version: 1.2.0
  
  Version Modified By   Date      Comments
  ------- -----------  ---------- -----------
  1.0.0    K Hoang     14/09/2020 Initial coding to add support to STM32 using built-in Ethernet (Nucleo-144, DISCOVERY, etc).
  1.0.1    K Hoang     09/10/2020 Restore cpp code besides Impl.h code.
  1.0.2    K Hoang     09/11/2020 Make Mutex Lock and delete more reliable and error-proof
  1.1.0    K Hoang     23/12/2020 Add HTTP PUT, PATCH, DELETE and HEAD methods
  1.1.1    K Hoang     24/12/2020 Prevent crash if request and/or method not correct.
  1.1.2    K Hoang     11/02/2021 Rename _lock and _unlock to avoid conflict with AsyncWebServer library
  1.1.3    K Hoang     25/02/2021 Fix non-persistent Connection header bug
  1.1.4    K Hoang     21/03/2021 Fix `library.properties` dependency
  1.1.5    K Hoang     22/03/2021 Fix dependency on STM32AsyncTCP Library
  1.2.0    K Hoang     11/04/2021 Add support to LAN8720 using STM32F4 or STM32F7
 *****************************************************************************************************************************/

/**
  Connects to dweet.io once every 1 minutes, sends a GET request and a request body.

  Shows how to use Strings to assemble path and parse content from response. 
  dweet.io expects: https://dweet.io/dweet/for/thingName

  For more on dweet.io, see https://dweet.io/play/ 
 * */

#include "defines.h"

// Select a test server address           
const char GET_ServerAddress[] = "dweet.io";

// use your own thing name here
String dweetName = "/dweet/for/currentSecond?second=";

// 60s = 60 seconds to not flooding the server
#define HTTP_REQUEST_INTERVAL_MS     60000

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
    requestOpenResult = request.open("GET", (GET_ServerAddress + dweetName + String(millis()/1000)).c_str() );
    
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
  
  Serial.println("\nStart AsyncDweetGET_STM32_LAN8720 on " + String(BOARD_NAME));
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
