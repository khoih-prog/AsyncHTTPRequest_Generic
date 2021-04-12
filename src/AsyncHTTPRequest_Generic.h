/****************************************************************************************************************************
  AsyncHTTPRequest_Generic.h - Dead simple AsyncHTTPRequest for ESP8266, ESP32 and currently STM32 with built-in LAN8742A Ethernet
  
  For ESP8266, ESP32 and STM32 with built-in LAN8742A Ethernet (Nucleo-144, DISCOVERY, etc)
  
  AsyncHTTPRequest_STM32 is a library for the ESP8266, ESP32 and currently STM32 run built-in Ethernet WebServer
  
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

#pragma once

#ifndef ASYNC_HTTP_REQUEST_GENERIC_H
#define ASYNC_HTTP_REQUEST_GENERIC_H

#define ASYNC_HTTP_REQUEST_GENERIC_VERSION   "AsyncHTTPRequest_Generic v1.2.0"

#include <Arduino.h>

#include "AsyncHTTPRequest_Debug_Generic.h"

#ifndef DEBUG_IOTA_PORT
  #define DEBUG_IOTA_PORT Serial
#endif

#ifdef DEBUG_IOTA_HTTP
  #define DEBUG_IOTA_HTTP_SET     true
#else
  #define DEBUG_IOTA_HTTP_SET     false
#endif


// KH add
#define SAFE_DELETE(object)         if (object) { delete object;}
#define SAFE_DELETE_ARRAY(object)   if (object) { delete[] object;}

#if ESP32

  #include <AsyncTCP.h>
  
  // KH mod
  #define MUTEX_LOCK_NR           if (xSemaphoreTakeRecursive(threadLock,portMAX_DELAY) != pdTRUE) { return;}
  #define MUTEX_LOCK(returnVal)   if (xSemaphoreTakeRecursive(threadLock,portMAX_DELAY) != pdTRUE) { return returnVal;}
  
  #define _AHTTP_lock       xSemaphoreTakeRecursive(threadLock,portMAX_DELAY)
  #define _AHTTP_unlock     xSemaphoreGiveRecursive(threadLock)
  
#elif ESP8266

  #include <ESPAsyncTCP.h>
  
  #define MUTEX_LOCK_NR
  #define MUTEX_LOCK(returnVal)
  
  #define _AHTTP_lock
  #define _AHTTP_unlock
  
#elif ( defined(STM32F0) || defined(STM32F1) || defined(STM32F2) || defined(STM32F3)  ||defined(STM32F4) || defined(STM32F7) || \
       defined(STM32L0) || defined(STM32L1) || defined(STM32L4) || defined(STM32H7)  ||defined(STM32G0) || defined(STM32G4) || \
       defined(STM32WB) || defined(STM32MP1) )
       
  #include "STM32AsyncTCP.h"
  
  #define MUTEX_LOCK_NR
  #define MUTEX_LOCK(returnVal)
  #define _AHTTP_lock
  #define _AHTTP_unlock
  
#endif

#include <pgmspace.h>
#include <utility/xbuf.h>

#define DEBUG_HTTP(format,...)  if(_debug){\
    DEBUG_IOTA_PORT.printf("Debug(%3ld): ", millis()-_requestStartTime);\
    DEBUG_IOTA_PORT.printf_P(PSTR(format),##__VA_ARGS__);}

#define DEFAULT_RX_TIMEOUT 3                    // Seconds for timeout

#define HTTPCODE_CONNECTION_REFUSED  (-1)
#define HTTPCODE_SEND_HEADER_FAILED  (-2)
#define HTTPCODE_SEND_PAYLOAD_FAILED (-3)
#define HTTPCODE_NOT_CONNECTED       (-4)
#define HTTPCODE_CONNECTION_LOST     (-5)
#define HTTPCODE_NO_STREAM           (-6)
#define HTTPCODE_NO_HTTP_SERVER      (-7)
#define HTTPCODE_TOO_LESS_RAM        (-8)
#define HTTPCODE_ENCODING            (-9)
#define HTTPCODE_STREAM_WRITE        (-10)
#define HTTPCODE_TIMEOUT             (-11)

typedef enum
{
  readyStateUnsent      = 0,            // Client created, open not yet called
  readyStateOpened      = 1,            // open() has been called, connected
  readyStateHdrsRecvd   = 2,            // send() called, response headers available
  readyStateLoading     = 3,            // receiving, partial data available
  readyStateDone        = 4             // Request complete, all data available.
} reqStates;
    
class AsyncHTTPRequest
{
    struct header
    {
      header*   next;
      char*     name;
      char*     value;
      
      header(): next(nullptr), name(nullptr), value(nullptr)
      {};
      
      ~header() 
      {
        SAFE_DELETE_ARRAY(name)
        SAFE_DELETE_ARRAY(value)
        SAFE_DELETE(next)
        //delete[] name;
        //delete[] value;
        //delete next;
      }
    };

    struct  URL 
    {
      char*   scheme;
      char*   user;
      char*   pwd;
      char*   host;
      int     port;
      char*   path;
      char*   query;
      char*   fragment;
      
      URL():  scheme(nullptr), user(nullptr), pwd(nullptr), host(nullptr),
              port(80), path(nullptr), query(nullptr), fragment(nullptr)
      {};
      
      ~URL() 
      {
        SAFE_DELETE_ARRAY(scheme)
        SAFE_DELETE_ARRAY(user)
        SAFE_DELETE_ARRAY(pwd)
        SAFE_DELETE_ARRAY(host)
        SAFE_DELETE_ARRAY(path)
        SAFE_DELETE_ARRAY(query)
        SAFE_DELETE_ARRAY(fragment)
      }
    };

    typedef std::function<void(void*, AsyncHTTPRequest*, int readyState)> readyStateChangeCB;
    typedef std::function<void(void*, AsyncHTTPRequest*, size_t available)> onDataCB;

  public:
    AsyncHTTPRequest();
    ~AsyncHTTPRequest();


    //External functions in typical order of use:
    //__________________________________________________________________________________________________________*/
    void        setDebug(bool);                                         // Turn debug message on/off
    bool        debug();                                                // is debug on or off?

    bool        open(const char* /*GET/POST*/, const char* URL);        // Initiate a request
    void        onReadyStateChange(readyStateChangeCB, void* arg = 0);  // Optional event handler for ready state change
    // or you can simply poll readyState()
    void        setTimeout(int);                                        // overide default timeout (seconds)

    void        setReqHeader(const char* name, const char* value);      // add a request header
    void        setReqHeader(const char* name, int32_t value);          // overload to use integer value
    
#if (ESP32 || ESP8266)
    void        setReqHeader(const char* name, const __FlashStringHelper* value);
    void        setReqHeader(const __FlashStringHelper *name, const char* value);
    void        setReqHeader(const __FlashStringHelper *name, const __FlashStringHelper* value);
    void        setReqHeader(const __FlashStringHelper *name, int32_t value);
#endif

    bool        send();                                                 // Send the request (GET)
    bool        send(String body);                                      // Send the request (POST)
    bool        send(const char* body);                                 // Send the request (POST)
    bool        send(const uint8_t* buffer, size_t len);                // Send the request (POST) (binary data?)
    bool        send(xbuf* body, size_t len);                           // Send the request (POST) data in an xbuf
    void        abort();                                                // Abort the current operation

    reqStates   readyState();                                           // Return the ready state

    int         respHeaderCount();                                      // Retrieve count of response headers
    char*       respHeaderName(int index);                              // Return header name by index
    char*       respHeaderValue(int index);                             // Return header value by index
    char*       respHeaderValue(const char* name);                      // Return header value by name
    
    bool        respHeaderExists(const char* name);                     // Does header exist by name?
    
#if (ESP32 || ESP8266)
    char*       respHeaderValue(const __FlashStringHelper *name);
    bool        respHeaderExists(const __FlashStringHelper *name);
#endif
    
    String      headers();                                              // Return all headers as String

    void        onData(onDataCB, void* arg = 0);                        // Notify when min data is available
    size_t      available();                                            // response available
    size_t      responseLength();                                       // indicated response length or sum of chunks to date
    int         responseHTTPcode();                                     // HTTP response code or (negative) error code
    String      responseText();                                         // response (whole* or partial* as string)
    
    char*       responseLongText();                                     // response long (whole* or partial* as string)
    
    size_t      responseRead(uint8_t* buffer, size_t len);              // Read response into buffer
    uint32_t    elapsedTime();                                          // Elapsed time of in progress transaction or last completed (ms)
    String      version();                                              // Version of AsyncHTTPRequest
    //___________________________________________________________________________________________________________________________________

  private:

    // New in v1.1.1
    bool _requestReadyToSend;
    //////
    
    // New in v1.1.0
    typedef enum  { HTTPmethodGET, HTTPmethodPOST, HTTPmethodPUT, HTTPmethodPATCH, HTTPmethodDELETE, HTTPmethodHEAD, HTTPmethodMAX } HTTPmethod;
    
    HTTPmethod _HTTPmethod;
    
    const char* _HTTPmethodStringwithSpace[HTTPmethodMAX] = {"GET ", "POST ", "PUT ", "PATCH ", "DELETE ", "HEAD "};
    //////
    
    reqStates       _readyState;

    int16_t         _HTTPcode;                  // HTTP response code or (negative) exception code
    bool            _chunked;                   // Processing chunked response
    bool            _debug;                     // Debug state
    uint32_t        _timeout;                   // Default or user overide RxTimeout in seconds
    uint32_t        _lastActivity;              // Time of last activity
    uint32_t        _requestStartTime;          // Time last open() issued
    uint32_t        _requestEndTime;            // Time of last disconnect
    URL*            _URL;                       // -> URL data structure
    char*           _connectedHost;             // Host when connected
    int             _connectedPort;             // Port when connected
    AsyncClient*    _client;                    // ESPAsyncTCP AsyncClient instance
    size_t          _contentLength;             // content-length header value or sum of chunk headers
    size_t          _contentRead;               // number of bytes retrieved by user since last open()
    readyStateChangeCB  _readyStateChangeCB;    // optional callback for readyState change
    void*           _readyStateChangeCBarg;     // associated user argument
    onDataCB        _onDataCB;                  // optional callback when data received
    void*           _onDataCBarg;               // associated user argument

#ifdef ESP32
    SemaphoreHandle_t threadLock;
#endif

    // request and response String buffers and header list (same queue for request and response).

    xbuf*       _request;                       // Tx data buffer
    xbuf*       _response;                      // Rx data buffer for headers
    xbuf*       _chunks;                        // First stage for chunked response
    header*     _headers;                       // request or (readyState > readyStateHdrsRcvd) response headers

    // Protected functions

    header*     _addHeader(const char*, const char*);
    header*     _getHeader(const char*);
    header*     _getHeader(int);
    bool        _buildRequest();
    bool        _parseURL(const char*);
    bool        _parseURL(String);
    void        _processChunks();
    bool        _connect();
    size_t      _send();
    void        _setReadyState(reqStates);
    
#if (ESP32 || ESP8266)    
    char*       _charstar(const __FlashStringHelper *str);
#endif

    // callbacks

    void        _onConnect(AsyncClient*);
    void        _onDisconnect(AsyncClient*);
    void        _onData(void*, size_t);
    void        _onError(AsyncClient*, int8_t);
    void        _onPoll(AsyncClient*);
    bool        _collectHeaders();
};

#include "AsyncHTTPRequest_Impl_Generic.h"

#endif    // ASYNC_HTTP_REQUEST_GENERIC_H
