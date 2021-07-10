/****************************************************************************************************************************
  AsyncHTTPRequest_STM32_LAN8720.ino - Dead simple AsyncHTTPRequest for ESP8266, ESP32 and currently STM32
  
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
//************************************************************************************************************
//
// There are scores of ways to use AsyncHTTPRequest.  The important thing to keep in mind is that
// it is asynchronous and just like in JavaScript, everything is event driven.  You will have some
// reason to initiate an asynchronous HTTP request in your program, but then sending the request
// headers and payload, gathering the response headers and any payload, and processing
// of that response, can (and probably should) all be done asynchronously.
//
// In this example, a Ticker function is setup to fire every 5 seconds to initiate a request.
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

#include "defines.h"

// 600s = 10 minutes to not flooding, 60s in testing
#define HTTP_REQUEST_INTERVAL_MS     60000  //600000

#include <AsyncHTTPRequest_Generic.h>        // https://github.com/khoih-prog/AsyncHTTPRequest_Generic

#include <Ticker.h>                   // https://github.com/sstaub/Ticker

AsyncHTTPRequest request;

void sendRequest(void);

// Repeat forever, millis() resolution
Ticker sendHTTPRequest(sendRequest, HTTP_REQUEST_INTERVAL_MS, 0, MILLIS); 

void sendRequest(void)
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
    Serial.println("\n**************************************");
    Serial.println(request->responseText());
    Serial.println("**************************************");
    
    request->setDebug(false);
  }
}

void setup(void) 
{
  Serial.begin(115200);
  delay(2000);
  
  Serial.println("\nStart AsyncHTTPRequest_STM32_LAN8720 on " + String(BOARD_NAME));
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

  // Send first request now
  //delay(60);
  sendRequest();
}

void loop(void) 
{
  sendHTTPRequest.update();
}
