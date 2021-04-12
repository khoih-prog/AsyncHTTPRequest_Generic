/****************************************************************************************************************************
  AsyncHTTPMultiRequests.ino - Dead simple AsyncHTTPRequest for ESP8266, ESP32 and currently STM32 with built-in LAN8742A Ethernet
  
  For ESP8266, ESP32 and STM32 with built-in LAN8742A Ethernet (Nucleo-144, DISCOVERY, etc)
  
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
//************************************************************************************************************
//
// There are scores of ways to use AsyncHTTPRequest.  The important thing to keep in mind is that
// it is asynchronous and just like in JavaScript, everything is event driven.  You will have some
// reason to initiate an asynchronous HTTP request in your program, but then sending the request
// headers and payload, gathering the response headers and any payload, and processing
// of that response, can (and probably should) all be done asynchronously.
//
// In this example, a Ticker function is setup to fire every 300 seconds to initiate a request.
// Everything is handled in AsyncHTTPRequest without blocking.
// The callback onReadyStateChange is made progressively and like most JS scripts, we look for
// readyState == 4 (complete) here.  At that time the response is retrieved and printed.
//
// Note that there is no code in loop().  A code entered into loop would run oblivious to
// the ongoing HTTP requests.  The Ticker could be removed and periodic calls to sendRequest()
// could be made in loop(), resulting in the same asynchronous handling.
//
// For demo purposes, debug is turned on for handling of the first request.  These are the
// events that are being handled in AsyncHTTPRequest.  They all begin with Debug(nnn) where
// nnn is the elapsed time in milliseconds since the transaction was started.
//
//*************************************************************************************************************

#if !( defined(ESP8266) ||  defined(ESP32) )
  #error This code is intended to run on the ESP8266 or ESP32 platform! Please check your Tools->Board setting.
#endif

// Level from 0-4
#define ASYNC_HTTP_DEBUG_PORT     Serial
#define _ASYNC_HTTP_LOGLEVEL_     1

// 300s = 5 minutes to not flooding
#define HTTP_REQUEST_INTERVAL     60  //300

// 10s
#define HEARTBEAT_INTERVAL        10

int status;     // the Wifi radio's status

const char* ssid        = "your_ssid";
const char* password    = "your_pass";

#if (ESP8266)
  #include <ESP8266WiFi.h>
#elif (ESP32)
  #include <WiFi.h>
#endif

#include <AsyncHTTPRequest_Generic.h>           // https://github.com/khoih-prog/AsyncHTTPRequest_Generic
#include <Ticker.h>

AsyncHTTPRequest request;
Ticker ticker;
Ticker ticker1;

void heartBeatPrint(void)
{
  static int num = 1;

  if (WiFi.status() == WL_CONNECTED)
    Serial.print(F("H"));        // H means connected to WiFi
  else
    Serial.print(F("F"));        // F means not connected to WiFi

  if (num == 80)
  {
    Serial.println();
    num = 1;
  }
  else if (num++ % 10 == 0)
  {
    Serial.print(F(" "));
  }
}

// To replace with your real APP_API
#define APP_API       "SECRECT_APP_API"

String requestPart1   = "http://api.openweathermap.org/data/2.5/onecall?lat=-24.32&lon=-46.9983";
String requestAPPID   = "&appid=" + String(APP_API);

// exclude fields: current,minutely,hourly,daily,alerts
String requestCurrent   = requestPart1 + "&exclude=minutely,hourly,daily,alerts" + requestAPPID;
String requestMinutely  = requestPart1 + "&exclude=current,hourly,daily,alerts" + requestAPPID;
String requestHourly    = requestPart1 + "&exclude=current,minutely,daily,alerts" + requestAPPID;
String requestDaily     = requestPart1 + "&exclude=current,minutely,hourly,alerts" + requestAPPID;
String requestAlert     = requestPart1 + "&exclude=current,minutely,hourly,daily" + requestAPPID;

#define NUM_REQUESTS    5

const char* requestName[ NUM_REQUESTS ] = { "Current", "Minutely", "Hourly", "Daily", "Alert" };

const char* requestAll[ NUM_REQUESTS ] = { requestCurrent.c_str(), requestMinutely.c_str(), requestHourly.c_str(), requestDaily.c_str(), requestAlert.c_str() };

uint8_t requestIndex = 0;

void sendRequest() 
{
  static bool requestOpenResult;
  
  if (request.readyState() == readyStateUnsent || request.readyState() == readyStateDone)
  {      
    requestOpenResult = request.open("GET", requestAll[requestIndex] );

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

void requestCB(void* optParm, AsyncHTTPRequest* request, int readyState) 
{
  (void) optParm;
  
  if (readyState == readyStateDone) 
  { 
    Serial.print("\n***************"); Serial.print(requestName[ requestIndex ]); Serial.println("***************");
    Serial.println(request->responseText());
    Serial.println("**************************************");

#if 1
    // Bypass hourly
    if (requestIndex == 1)
      requestIndex = 3;
    else   
      requestIndex = (requestIndex + 1) % NUM_REQUESTS;
#else
    // hourly too long, not display anyway. Not enough heap.
    requestIndex = (requestIndex + 1) % NUM_REQUESTS;
   #endif
   
    request->setDebug(false);
  }
}

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  while (!Serial);
  
  delay(200);
  
  Serial.println("\nStarting AsyncHTTPMultiRequests using " + String(ARDUINO_BOARD));
  Serial.println(ASYNC_HTTP_REQUEST_GENERIC_VERSION);

  WiFi.mode(WIFI_STA);

  WiFi.begin(ssid, password);
  
  Serial.println("Connecting to WiFi SSID: " + String(ssid));

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.print(F("\nHTTP WebServer is @ IP : "));
  Serial.println(WiFi.localIP());
 
  request.setDebug(false);
  
  request.onReadyStateChange(requestCB);
  ticker.attach(HTTP_REQUEST_INTERVAL, sendRequest);

  ticker1.attach(HEARTBEAT_INTERVAL, heartBeatPrint);
  
  // Send first request now
  sendRequest();  
}

void loop()
{ 
}
