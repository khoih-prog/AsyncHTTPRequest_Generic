/****************************************************************************************************************************
  AsyncHTTPMultiRequests_WT32_ETH01.ino - Dead simple AsyncHTTPRequest for ESP8266, ESP32 and currently STM32 with built-in LAN8742A Ethernet
  
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

#if !( defined(ESP32) )
  #error This code is intended to run on the ESP32 platform! Please check your Tools->Board setting.
#endif

// Level from 0-4
#define ASYNC_HTTP_DEBUG_PORT           Serial
#define _ASYNC_HTTP_LOGLEVEL_           1
#define _ETHERNET_WEBSERVER_LOGLEVEL_   1

// 300s = 5 minutes to not flooding
#define HTTP_REQUEST_INTERVAL     60  //300

// 10s
#define HEARTBEAT_INTERVAL        10

#include <WebServer_WT32_ETH01.h>               // https://github.com/khoih-prog/WebServer_WT32_ETH01

#include <AsyncHTTPRequest_Generic.h>           // https://github.com/khoih-prog/AsyncHTTPRequest_Generic
#include <Ticker.h>

AsyncHTTPRequest request;
Ticker ticker;
Ticker ticker1;

/////////////////////////////////////////////

// Select the IP address according to your local network
IPAddress myIP(192, 168, 2, 232);
IPAddress myGW(192, 168, 2, 1);
IPAddress mySN(255, 255, 255, 0);

// Google DNS Server IP
IPAddress myDNS(8, 8, 8, 8);

bool eth_connected = false;

/////////////////////////////////////////////

void heartBeatPrint(void)
{
  static int num = 1;

  if (eth_connected)
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
  
  Serial.print("\nStarting AsyncHTTPRequest_WT32_ETH01 on " + String(ARDUINO_BOARD));
  Serial.println(" with " + String(SHIELD_TYPE));
  Serial.println(WEBSERVER_WT32_ETH01_VERSION);
  Serial.println(ASYNC_HTTP_REQUEST_GENERIC_VERSION);

  Serial.setDebugOutput(true);

  // To be called before ETH.begin()
  WT32_ETH01_onEvent();

  //bool begin(uint8_t phy_addr=ETH_PHY_ADDR, int power=ETH_PHY_POWER, int mdc=ETH_PHY_MDC, int mdio=ETH_PHY_MDIO, 
  //           eth_phy_type_t type=ETH_PHY_TYPE, eth_clock_mode_t clk_mode=ETH_CLK_MODE);
  //ETH.begin(ETH_PHY_ADDR, ETH_PHY_POWER, ETH_PHY_MDC, ETH_PHY_MDIO, ETH_PHY_TYPE, ETH_CLK_MODE);
  ETH.begin(ETH_PHY_ADDR, ETH_PHY_POWER);

  // Static IP, leave without this line to get IP via DHCP
  //bool config(IPAddress local_ip, IPAddress gateway, IPAddress subnet, IPAddress dns1 = 0, IPAddress dns2 = 0);
  ETH.config(myIP, myGW, mySN, myDNS);

  WT32_ETH01_waitForConnect();

  Serial.print(F("AsyncHTTPRequest @ IP : "));
  Serial.println(ETH.localIP());
 
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
