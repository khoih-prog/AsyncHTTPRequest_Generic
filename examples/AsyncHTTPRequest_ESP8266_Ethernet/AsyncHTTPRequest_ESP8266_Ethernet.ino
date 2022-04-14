/****************************************************************************************************************************
  AsyncHTTPRequest_ESP.ino - Dead simple AsyncHTTPRequest for ESP8266, ESP32 and currently STM32 with built-in LAN8742A Ethernet
  
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

#if !( defined(ESP8266) )
  #error This code is intended to run on the ESP8266 platform! Please check your Tools->Board setting.
#endif

// Level from 0-4
#define ASYNC_HTTP_DEBUG_PORT     Serial
#define _ASYNC_HTTP_LOGLEVEL_     1    

// 300s = 5 minutes to not flooding
#define HTTP_REQUEST_INTERVAL     60  //300

// 10s
#define HEARTBEAT_INTERVAL        10

//////////////////////////////////////////////////////////

#define USING_W5500         true
#define USING_W5100         false
#define USING_ENC28J60      false

#include <SPI.h>

#define CSPIN       16      // 5

#if USING_W5500
  #include "W5500lwIP.h"
  #define SHIELD_TYPE       "ESP8266_W5500 Ethernet"
  
  Wiznet5500lwIP eth(CSPIN); 
   
#elif USING_W5100
  #include <W5100lwIP.h>
  #define SHIELD_TYPE       "ESP8266_W5100 Ethernet"
  
  Wiznet5100lwIP eth(CSPIN);

#elif USING_ENC28J60
  #include <ENC28J60lwIP.h>
  #define SHIELD_TYPE       "ESP8266_ENC28J60 Ethernet"
  
  ENC28J60lwIP eth(CSPIN);
#else
  // default if none selected
  #include "W5500lwIP.h"

  Wiznet5500lwIP eth(CSPIN);
#endif


#include <WiFiClient.h> // WiFiClient (-> TCPClient)

using TCPClient = WiFiClient;





//////////////////////////////////////////////////////////

#define ASYNC_HTTP_REQUEST_GENERIC_VERSION_MIN_TARGET      "AsyncHTTPRequest_Generic v1.7.1"
#define ASYNC_HTTP_REQUEST_GENERIC_VERSION_MIN             1007001

// To be included only in main(), .ino with setup() to avoid `Multiple Definitions` Linker Error
#include <AsyncHTTPRequest_Generic.h>             // https://github.com/khoih-prog/AsyncHTTPRequest_Generic

#include <Ticker.h>

AsyncHTTPRequest request;
Ticker ticker;
Ticker ticker1;

void heartBeatPrint()
{
  static int num = 1;

  if (eth.connected())
    Serial.print(F("H"));        // H means connected to Ethernet
  else
    Serial.print(F("F"));        // F means not connected to Ethernet

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

void sendRequest() 
{
  static bool requestOpenResult;
  
  if (request.readyState() == readyStateUnsent || request.readyState() == readyStateDone)
  {
    //requestOpenResult = request.open("GET", "http://worldtimeapi.org/api/timezone/Europe/London.txt");
    requestOpenResult = request.open("GET", "http://worldtimeapi.org/api/timezone/America/Toronto.txt");
    
    if (requestOpenResult)
    {
      // Only send() if open() returns true, or crash
      request.send();
    }
    else
    {
      Serial.println(F("Can't send bad request"));
    }
  }
  else
  {
    Serial.println(F("Can't send request"));
  }
}

void requestCB(void* optParm, AsyncHTTPRequest* request, int readyState) 
{
  (void) optParm;
  
  if (readyState == readyStateDone) 
  {
    Serial.println(F("\n**************************************"));
    Serial.println(request->responseText());
    Serial.println(F("**************************************"));
    
    request->setDebug(false);
  }
}

void initEthernet()
{
  SPI.begin();
  SPI.setClockDivider(SPI_CLOCK_DIV4);
  SPI.setBitOrder(MSBFIRST);
  SPI.setDataMode(SPI_MODE0);
  eth.setDefault();
  
  if (!eth.begin()) 
  {
    Serial.println("No Ethernet hardware ... Stop here");
    
    while (true) 
    {
      delay(1000);
    }
  } 
  else 
  {
    Serial.print("Connecting to network : ");
    
    while (!eth.connected()) 
    {
      Serial.print(".");
      delay(1000);
    }
  }
  
  Serial.println();
  Serial.print("Ethernet IP address: ");
  Serial.println(eth.localIP());
}

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  while (!Serial && millis() < 5000);

  delay(200);
  
  Serial.print(F("\nStarting AsyncHTTPRequest_ESP8266_Ethernet on ")); Serial.print(ARDUINO_BOARD);
  Serial.print(F(" using ")); Serial.println(SHIELD_TYPE);
  Serial.println(ASYNC_HTTP_REQUEST_GENERIC_VERSION);

  initEthernet();

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
