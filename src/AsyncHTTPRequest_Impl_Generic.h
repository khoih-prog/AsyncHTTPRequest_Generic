/****************************************************************************************************************************
  AsyncHTTPRequest_Impl_Generic.h - Dead simple AsyncHTTPRequest for ESP8266, ESP32 and currently STM32 with built-in LAN8742A Ethernet
  
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
 
  Version: 1.1.3
  
  Version Modified By   Date      Comments
  ------- -----------  ---------- -----------
  1.0.0    K Hoang     14/09/2020 Initial coding to add support to STM32 using built-in Ethernet (Nucleo-144, DISCOVERY, etc).
  1.0.1    K Hoang     09/10/2020 Restore cpp code besides Impl.h code.
  1.0.2    K Hoang     09/11/2020 Make Mutex Lock and delete more reliable and error-proof
  1.1.0    K Hoang     23/12/2020 Add HTTP PUT, PATCH, DELETE and HEAD methods
  1.1.1    K Hoang     24/12/2020 Prevent crash if request and/or method not correct.
  1.1.2    K Hoang     11/02/2021 Rename _lock and _unlock to avoid conflict with AsyncWebServer library
  1.1.3    K Hoang     25/02/2021 Fix non-persistent Connection header bug
 *****************************************************************************************************************************/
 
#pragma once

#ifndef ASYNC_HTTP_REQUEST_GENERIC_IMPL_H
#define ASYNC_HTTP_REQUEST_GENERIC_IMPL_H

#define CANT_SEND_BAD_REQUEST       F("Can't send() bad request")

//**************************************************************************************************************
AsyncHTTPRequest::AsyncHTTPRequest(): _readyState(readyStateUnsent), _HTTPcode(0), _chunked(false), _debug(DEBUG_IOTA_HTTP_SET)
  , _timeout(DEFAULT_RX_TIMEOUT), _lastActivity(0), _requestStartTime(0), _requestEndTime(0), _URL(nullptr)
  , _connectedHost(nullptr), _connectedPort(-1), _client(nullptr), _contentLength(0), _contentRead(0)
  , _readyStateChangeCB(nullptr), _readyStateChangeCBarg(nullptr), _onDataCB(nullptr), _onDataCBarg(nullptr)
  , _request(nullptr), _response(nullptr), _chunks(nullptr), _headers(nullptr)
{
#ifdef ESP32
  threadLock = xSemaphoreCreateRecursiveMutex();
#endif
}

//**************************************************************************************************************
AsyncHTTPRequest::~AsyncHTTPRequest()
{
  if (_client)
    _client->close(true);


  SAFE_DELETE(_URL)
  SAFE_DELETE(_headers)
  SAFE_DELETE(_request)
  SAFE_DELETE(_response)
  SAFE_DELETE(_chunks)
  SAFE_DELETE_ARRAY(_connectedHost)

#ifdef ESP32
  // KH add
  if (threadLock)
  {
    vSemaphoreDelete(threadLock);  
  }
#endif
}

//**************************************************************************************************************
void AsyncHTTPRequest::setDebug(bool debug)
{
  if (_debug || debug)
  {
    _debug = true;

    AHTTP_LOGDEBUG3("setDebug(", debug ? "on" : "off", ") version", ASYNC_HTTP_REQUEST_GENERIC_VERSION);
  }
  
  _debug = debug;
}

//**************************************************************************************************************
bool AsyncHTTPRequest::debug()
{
  return (_debug);
}

//**************************************************************************************************************
bool  AsyncHTTPRequest::open(const char* method, const char* URL)
{
  AHTTP_LOGDEBUG3("open(", method, ", url =", URL);

  if (_readyState != readyStateUnsent && _readyState != readyStateDone)
  {
    AHTTP_LOGDEBUG("open: not ready");
    
    return false;
  }

  _requestStartTime = millis();
  
  SAFE_DELETE(_URL)
  SAFE_DELETE(_headers)
  SAFE_DELETE(_request)
  SAFE_DELETE(_response)
  SAFE_DELETE(_chunks)
  
  _URL          = nullptr;
  _headers      = nullptr;
  _response     = nullptr;
  _request      = nullptr;
  _chunks       = nullptr;
  _chunked      = false;
  _contentRead  = 0;
  _readyState   = readyStateUnsent;
  
  // New in v1.1.1
  _requestReadyToSend = false;
  //////

  if (strcmp(method, "GET") == 0)
  {
    _HTTPmethod = HTTPmethodGET;
  }
  else if (strcmp(method, "POST") == 0)
  {
    _HTTPmethod = HTTPmethodPOST;
  }
  // New in v1.1.0
  else if (strcmp(method, "PUT") == 0)
  {
    _HTTPmethod = HTTPmethodPUT;
  }
  else if (strcmp(method, "PATCH") == 0)
  {
    _HTTPmethod = HTTPmethodPATCH;
  }
  else if (strcmp(method, "DELETE") == 0)
  {
    _HTTPmethod = HTTPmethodDELETE;
  }
  else if (strcmp(method, "HEAD") == 0)
  {
    _HTTPmethod = HTTPmethodHEAD;
  }
  //////
  else
  {
    AHTTP_LOGDEBUG("open: Bad method");
    
    return false;
  }


  if (!_parseURL(URL))
  {
    AHTTP_LOGDEBUG("open: error parsing URL");
    
    return false;
  }
  
  if ( _client && _client->connected() && (strcmp(_URL->host, _connectedHost) != 0 || _URL->port != _connectedPort))
  {
    AHTTP_LOGDEBUG("open: not connected");
    
    return false;
  }

  char* hostName = new char[strlen(_URL->host) + 10];
  
  if (hostName)
  {
    sprintf(hostName, "%s:%d", _URL->host, _URL->port);
    _addHeader("host", hostName);
    
    SAFE_DELETE_ARRAY(hostName)
    
    _lastActivity = millis();
    
    // New in v1.1.1
    _requestReadyToSend = true;
    //////
    
    AHTTP_LOGDEBUG1("open: conneting to hostname =", hostName);

    return _connect();
  }
  else
  {
    AHTTP_LOGDEBUG("open: error alloc");
    
    return false;
  }
}
//**************************************************************************************************************
void AsyncHTTPRequest::onReadyStateChange(readyStateChangeCB cb, void* arg) 
{
  _readyStateChangeCB = cb;
  _readyStateChangeCBarg = arg;
}

//**************************************************************************************************************
void  AsyncHTTPRequest::setTimeout(int seconds) 
{
  AHTTP_LOGDEBUG1("setTimeout = ", seconds);

  _timeout = seconds;
}

//**************************************************************************************************************
bool  AsyncHTTPRequest::send() 
{ 
  // New in v1.1.1
  if (_requestReadyToSend)
  {
    AHTTP_LOGDEBUG("send()");
  }
  else
  {
    AHTTP_LOGDEBUG(CANT_SEND_BAD_REQUEST);
    return false;
  }
  //////

  MUTEX_LOCK(false)
  
  if ( ! _buildRequest()) 
    return false;
    
  _send();
  
  _AHTTP_unlock;
  
  return true;
}

//**************************************************************************************************************
bool AsyncHTTPRequest::send(String body)
{
  // New in v1.1.1
  if (_requestReadyToSend)
  {
    AHTTP_LOGDEBUG3("send(String)", body.substring(0, 16).c_str(), ", length =", body.length());
  }
  else
  {
    AHTTP_LOGDEBUG(CANT_SEND_BAD_REQUEST);
    return false;
  }
  //////

  MUTEX_LOCK(false)
  
  _addHeader("Content-Length", String(body.length()).c_str());
  
  if ( ! _buildRequest()) 
  {
    _AHTTP_unlock;
    
    return false;
  }
  
  _request->write(body);
  _send();
  
  _AHTTP_unlock;
  
  return true;
}

//**************************************************************************************************************
bool  AsyncHTTPRequest::send(const char* body) 
{
  // New in v1.1.1
  if (_requestReadyToSend)
  {
    AHTTP_LOGDEBUG3("send(char)", body, ", length =", strlen(body));
  }
  else
  {
    AHTTP_LOGDEBUG(CANT_SEND_BAD_REQUEST);
    return false;
  }
  //////

  MUTEX_LOCK(false)
  
  _addHeader("Content-Length", String(strlen(body)).c_str());
  
  if ( ! _buildRequest()) 
  {
    _AHTTP_unlock;
    
    return false;
  }
  
  _request->write(body);
  _send();
  
  _AHTTP_unlock;
  
  return true;
}

//**************************************************************************************************************
bool  AsyncHTTPRequest::send(const uint8_t* body, size_t len)
{
  // New in v1.1.1
  if (_requestReadyToSend)
  {
    AHTTP_LOGDEBUG3("send(char)", (char*) body, ", length =", len);
  }
  else
  {
    AHTTP_LOGDEBUG(CANT_SEND_BAD_REQUEST);
    return false;
  }
  //////

  MUTEX_LOCK(false)
  
  _addHeader("Content-Length", String(len).c_str());
  
  if ( ! _buildRequest()) 
  {
    _AHTTP_unlock;
    
    return false;
  }
  
  _request->write(body, len);
  _send();
  
  _AHTTP_unlock;
  
  return true;
}

//**************************************************************************************************************
bool AsyncHTTPRequest::send(xbuf* body, size_t len)
{
  // New in v1.1.1
  if (_requestReadyToSend)
  {
    AHTTP_LOGDEBUG3("send(char)", body->peekString(16).c_str(), ", length =", len);
  }
  else
  {
    AHTTP_LOGDEBUG(CANT_SEND_BAD_REQUEST);
    return false;
  }
  //////

  MUTEX_LOCK(false)
  
  _addHeader("Content-Length", String(len).c_str());
  
  if ( ! _buildRequest()) 
  {
    _AHTTP_unlock;
    
    return false;
  }
  
  _request->write(body, len);
  _send();
  
  _AHTTP_unlock;
  
  return true;
}

//**************************************************************************************************************
void AsyncHTTPRequest::abort()
{
  AHTTP_LOGDEBUG("abort()");

  if (! _client)
  {
    return;
  }
  
  MUTEX_LOCK_NR
    
  _client->abort();
  
  _AHTTP_unlock;
}
//**************************************************************************************************************
reqStates   AsyncHTTPRequest::readyState()
{
  return _readyState;
}

//**************************************************************************************************************
int AsyncHTTPRequest::responseHTTPcode()
{
  return _HTTPcode;
}

//**************************************************************************************************************
String AsyncHTTPRequest::responseText()
{
  AHTTP_LOGDEBUG("responseText()");

  MUTEX_LOCK(String())
  
  if ( ! _response || _readyState < readyStateLoading || ! available())
  {
    AHTTP_LOGDEBUG("responseText() no data");

    _AHTTP_unlock;
    
    return String();
  }

  String localString;
  size_t avail = available();

  if ( ! localString.reserve(avail))
  {
    AHTTP_LOGDEBUG("responseText() no buffer");

    _HTTPcode = HTTPCODE_TOO_LESS_RAM;
    _client->abort();
    
    _AHTTP_unlock;
    
    return String();
  }
  
  localString   = _response->readString(avail);
  _contentRead += localString.length();

  //AHTTP_LOGDEBUG3("responseText(char)", localString.substring(0, 16).c_str(), ", avail =", avail);
  AHTTP_LOGDEBUG3("responseText(char)", localString, ", avail =", avail);

  _AHTTP_unlock;
  
  return localString;
}

//**************************************************************************************************************

#if 1

#if (ESP32)
  #define GLOBAL_STR_LEN      (32 * 1024)
#elif (ESP8266)
  #define GLOBAL_STR_LEN      (16 * 1024) 
#else
  #define GLOBAL_STR_LEN      (4 * 1024)
#endif

char globalLongString[GLOBAL_STR_LEN + 1];

char* AsyncHTTPRequest::responseLongText()
{
  AHTTP_LOGDEBUG("responseLongText()");

  MUTEX_LOCK(NULL)
  
  if ( ! _response || _readyState < readyStateLoading || ! available())
  {
    AHTTP_LOGDEBUG("responseText() no data");

    _AHTTP_unlock;
    
    //return String();
    return NULL;
  }

  // String localString;
  size_t avail = available();
  size_t lenToCopy = (avail <= GLOBAL_STR_LEN) ? avail : GLOBAL_STR_LEN;

  strncpy(globalLongString, _response->readString(avail).c_str(), lenToCopy );
  globalLongString[ lenToCopy + 1 ] = 0;
  
  _contentRead += _response->readString(avail).length();
  
  AHTTP_LOGDEBUG3("responseLongText(char)", globalLongString, ", avail =", avail);
  
  _AHTTP_unlock;
  
  return globalLongString;
}
#endif

//**************************************************************************************************************
size_t AsyncHTTPRequest::responseRead(uint8_t* buf, size_t len)
{
  if ( ! _response || _readyState < readyStateLoading || ! available())
  {
    AHTTP_LOGDEBUG("responseRead() no data");

    return 0;
  }

  MUTEX_LOCK(0)
  
  size_t avail = available() > len ? len : available();
  _response->read(buf, avail);

  AHTTP_LOGDEBUG3("responseRead(char)", (char*) buf, ", avail =", avail);

  _contentRead += avail;
  
  _AHTTP_unlock;

  return avail;
}

//**************************************************************************************************************
size_t  AsyncHTTPRequest::available()
{
  if (_readyState < readyStateLoading)
    return 0;

  if (_chunked && (_contentLength - _contentRead) < _response->available())
  {
    return _contentLength - _contentRead;
  }

  return _response->available();
}

//**************************************************************************************************************
size_t  AsyncHTTPRequest::responseLength()
{
  if (_readyState < readyStateLoading)
    return 0;

  return _contentLength;
}

//**************************************************************************************************************
void  AsyncHTTPRequest::onData(onDataCB cb, void* arg)
{
  AHTTP_LOGDEBUG("onData() CB set");

  _onDataCB = cb;
  _onDataCBarg = arg;
}

//**************************************************************************************************************
uint32_t AsyncHTTPRequest::elapsedTime()
{
  if (_readyState <= readyStateOpened)
    return 0;

  if (_readyState != readyStateDone)
  {
    return millis() - _requestStartTime;
  }

  return _requestEndTime - _requestStartTime;
}

//**************************************************************************************************************
String AsyncHTTPRequest::version()
{
  return String(ASYNC_HTTP_REQUEST_GENERIC_VERSION);
}

/*______________________________________________________________________________________________________________

               PPPP    RRRR     OOO    TTTTT   EEEEE    CCC    TTTTT   EEEEE   DDDD
               P   P   R   R   O   O     T     E       C   C     T     E       D   D
               PPPP    RRRR    O   O     T     EEE     C         T     EEE     D   D
               P       R  R    O   O     T     E       C   C     T     E       D   D
               P       R   R    OOO      T     EEEEE    CCC      T     EEEEE   DDDD
  _______________________________________________________________________________________________________________*/

//**************************************************************************************************************
bool  AsyncHTTPRequest::_parseURL(const char* url)
{
  return _parseURL(String(url));
}

//**************************************************************************************************************
bool  AsyncHTTPRequest::_parseURL(String url)
{
  SAFE_DELETE(_URL)
  
  int hostBeg = 0;
  
  _URL = new URL;
  
  if (_URL)
  {
    _URL->scheme = new char[8];
    
    if (! (_URL->scheme) )
      return false;
  }
  else
    return false;
  
  strcpy(_URL->scheme, "HTTP://");

  if (url.substring(0, 7).equalsIgnoreCase("HTTP://"))
  {
    hostBeg += 7;
  }
  else if (url.substring(0, 8).equalsIgnoreCase("HTTPS://"))
  {
    return false;
  }

  int pathBeg = url.indexOf('/', hostBeg);

  if (pathBeg < 0)
    return false;

  int hostEnd = pathBeg;
  int portBeg = url.indexOf(':', hostBeg);

  if (portBeg > 0 && portBeg < pathBeg)
  {
    _URL->port = url.substring(portBeg + 1, pathBeg).toInt();
    hostEnd = portBeg;
  }

  _URL->host = new char[hostEnd - hostBeg + 1];
  
  if (_URL->host == nullptr)
    return false;
  
  strcpy(_URL->host, url.substring(hostBeg, hostEnd).c_str());

  int queryBeg = url.indexOf('?');
  
  if (queryBeg < 0) 
    queryBeg = url.length();
    
  _URL->path = new char[queryBeg - pathBeg + 1];
  
  if (_URL->path == nullptr)
    return false;
  
  strcpy(_URL->path, url.substring(pathBeg, queryBeg).c_str());
  
  _URL->query = new char[url.length() - queryBeg + 1];
  
  if (_URL->query == nullptr)
    return false;
  
  strcpy(_URL->query, url.substring(queryBeg).c_str());

  AHTTP_LOGDEBUG2("_parseURL(): scheme+host", _URL->scheme, _URL->host);
  AHTTP_LOGDEBUG3("_parseURL(): port+path+query", _URL->port, _URL->path, _URL->query);

  return true;
}

//**************************************************************************************************************
bool  AsyncHTTPRequest::_connect()
{
  AHTTP_LOGDEBUG("_connect()");

  if ( ! _client)
  {
    _client = new AsyncClient();
    
    if (! _client)
      return false;
  }

  SAFE_DELETE_ARRAY(_connectedHost)

  _connectedHost = new char[strlen(_URL->host) + 1];
  
  if (_connectedHost == nullptr)
    return false;
    
  strcpy(_connectedHost, _URL->host);
  _connectedPort = _URL->port;
  
  _client->onConnect([](void *obj, AsyncClient * client) 
  {
    ((AsyncHTTPRequest*)(obj))->_onConnect(client);
  }, this);
  
  _client->onDisconnect([](void *obj, AsyncClient * client) 
  {
    ((AsyncHTTPRequest*)(obj))->_onDisconnect(client);
  }, this);
  
  _client->onPoll([](void *obj, AsyncClient * client) 
  {
    ((AsyncHTTPRequest*)(obj))->_onPoll(client);
  }, this);
  
  _client->onError([](void *obj, AsyncClient * client, uint32_t error) 
  {
    ((AsyncHTTPRequest*)(obj))->_onError(client, error);
  }, this);

  if ( ! _client->connected())
  {
    if ( ! _client->connect(_URL->host, _URL->port))
    {
      AHTTP_LOGDEBUG3("client.connect failed:", _URL->host, ",", _URL->port);

      _HTTPcode = HTTPCODE_NOT_CONNECTED;
      _setReadyState(readyStateDone);

      return false;
    }
  }
  else
  {
    _onConnect(_client);
  }

  _lastActivity = millis();

  return true;
}

//**************************************************************************************************************
bool   AsyncHTTPRequest::_buildRequest()
{
  AHTTP_LOGDEBUG("_buildRequest()");

  // Build the header.
  if ( ! _request)
  {
    _request = new xbuf;
    
    if ( ! _request)
      return false;
  }

  // New in v1.1.1
  AHTTP_LOGDEBUG1("_HTTPmethod =", _HTTPmethod);
  AHTTP_LOGDEBUG3(_HTTPmethodStringwithSpace[_HTTPmethod], _URL->path, _URL->query, " HTTP/1.1\r\n" );
  //////
  
  // New in v1.1.0
  _request->write(_HTTPmethodStringwithSpace[_HTTPmethod]);
  //////
    
  _request->write(_URL->path);
  _request->write(_URL->query);
  _request->write(" HTTP/1.1\r\n");
     
  SAFE_DELETE(_URL)

  _URL = nullptr;
  header* hdr = _headers;

  while (hdr)
  {
    _request->write(hdr->name);
    _request->write(':');
    _request->write(hdr->value);
    _request->write("\r\n");
    
    AHTTP_LOGDEBUG3(hdr->name, ":", hdr->value, "\r\n" );
    
    hdr = hdr->next;
  }

  SAFE_DELETE(_headers)
  
  _headers = nullptr;
  _request->write("\r\n");

  return true;
}

//**************************************************************************************************************
size_t  AsyncHTTPRequest::_send()
{
  if ( ! _request)
    return 0;

  AHTTP_LOGDEBUG1("_send(), _request->available =", _request->available());

  if ( ! _client->connected() || ! _client->canSend())
  {
    AHTTP_LOGDEBUG("*can't send");

    return 0;
  }

  size_t supply = _request->available();
  size_t demand = _client->space();

  if (supply > demand)
    supply = demand;

  size_t sent = 0;
  uint8_t* temp = new uint8_t[100];
  
  if (!temp)
    return 0;

  while (supply)
  {
    size_t chunk = supply < 100 ? supply : 100;
    
    supply  -= _request->read(temp, chunk);
    sent    += _client->add((char*)temp, chunk);
  }

  // KH, Must be delete [] temp;
  SAFE_DELETE_ARRAY(temp)

  if (_request->available() == 0)
  {
    //delete _request;
    SAFE_DELETE(_request)
    
    _request = nullptr;
  }

  _client->send();

  AHTTP_LOGDEBUG1("*send", sent);

  _lastActivity = millis();

  return sent;
}

//**************************************************************************************************************
void  AsyncHTTPRequest::_setReadyState(reqStates newState) 
{
  if (_readyState != newState)
  {
    _readyState = newState;

    AHTTP_LOGDEBUG1("_setReadyState :", _readyState);

    if (_readyStateChangeCB)
    {
      _readyStateChangeCB(_readyStateChangeCBarg, this, _readyState);
    }
  }
}

//**************************************************************************************************************
void  AsyncHTTPRequest::_processChunks()
{
  while (_chunks->available())
  {
    AHTTP_LOGDEBUG3("_processChunks()", _chunks->peekString(16).c_str(), ", chunks available =", _chunks->available());

    size_t _chunkRemaining = _contentLength - _contentRead - _response->available();
    _chunkRemaining -= _response->write(_chunks, _chunkRemaining);

    if (_chunks->indexOf("\r\n") == -1)
    {
      return;
    }

    String chunkHeader = _chunks->readStringUntil("\r\n");

    AHTTP_LOGDEBUG3("*getChunkHeader", chunkHeader.c_str(), ", chunkHeader length =", chunkHeader.length());

    size_t chunkLength = strtol(chunkHeader.c_str(), nullptr, 16);
    _contentLength += chunkLength;

    if (chunkLength == 0)
    {
      char* connectionHdr = respHeaderValue("connection");

      if (connectionHdr && (strcasecmp_P(connectionHdr, PSTR("close")) == 0))
      {
        AHTTP_LOGDEBUG("*all chunks received - closing TCP");

        _client->close();
      }
      else
      {
        AHTTP_LOGDEBUG("*all chunks received - no disconnect");
      }

      _requestEndTime = millis();
      _lastActivity = 0;
      _timeout = 0;
      _setReadyState(readyStateDone);

      return;
    }
  }
}

/*______________________________________________________________________________________________________________

  EEEEE   V   V   EEEEE   N   N   TTTTT         H   H    AAA    N   N   DDDD    L       EEEEE   RRRR     SSS
  E       V   V   E       NN  N     T           H   H   A   A   NN  N   D   D   L       E       R   R   S
  EEE     V   V   EEE     N N N     T           HHHHH   AAAAA   N N N   D   D   L       EEE     RRRR     SSS
  E        V V    E       N  NN     T           H   H   A   A   N  NN   D   D   L       E       R  R        S
  EEEEE     V     EEEEE   N   N     T           H   H   A   A   N   N   DDDD    LLLLL   EEEEE   R   R    SSS
  _______________________________________________________________________________________________________________*/

//**************************************************************************************************************
void  AsyncHTTPRequest::_onConnect(AsyncClient* client)
{
  AHTTP_LOGDEBUG("_onConnect handler");

  MUTEX_LOCK_NR
  
  _client = client;
  _setReadyState(readyStateOpened);
  
  // KH test
  _response = new xbuf;
  //_response = new xbuf(256);
  //////
  
  if (!_response)
  {
    _AHTTP_unlock;
    
    // KH, to remove
    AHTTP_LOGDEBUG("_onConnect: Can't new _responser");
    ///////
    
    return;
  }
  
  _contentLength = 0;
  _contentRead = 0;
  _chunked = false;
  
  _client->onAck([](void* obj, AsyncClient * client, size_t len, uint32_t time) 
  {
    (void) client;
    (void) len;
    (void) time;
    
    ((AsyncHTTPRequest*)(obj))->_send();
  }, this);
  
  _client->onData([](void* obj, AsyncClient * client, void* data, size_t len) 
  {
    (void) client;
    
    ((AsyncHTTPRequest*)(obj))->_onData(data, len);
  }, this);

  if (_client->canSend())
  {
    _send();
  }

  _lastActivity = millis();
  
  _AHTTP_unlock;
}

//**************************************************************************************************************
void  AsyncHTTPRequest::_onPoll(AsyncClient* client)
{
  (void) client;
  
  MUTEX_LOCK_NR

  if (_timeout && (millis() - _lastActivity) > (_timeout * 1000))
  {
    _client->close();
    _HTTPcode = HTTPCODE_TIMEOUT;

    AHTTP_LOGDEBUG("_onPoll timeout");
  }

  if (_onDataCB && available())
  {
    _onDataCB(_onDataCBarg, this, available());
  }

  _AHTTP_unlock;
}

//**************************************************************************************************************
void  AsyncHTTPRequest::_onError(AsyncClient* client, int8_t error)
{
  (void) client;
  
  AHTTP_LOGDEBUG1("_onError handler error =", error);

  _HTTPcode = error;
}

//**************************************************************************************************************
void  AsyncHTTPRequest::_onDisconnect(AsyncClient* client)
{
  (void) client;
  
  AHTTP_LOGDEBUG("\n_onDisconnect handler");

  MUTEX_LOCK_NR
  
  if (_readyState < readyStateOpened)
  {
    _HTTPcode = HTTPCODE_NOT_CONNECTED;
  }
  else if (_HTTPcode > 0 &&
           (_readyState < readyStateHdrsRecvd || (_contentRead + _response->available()) < _contentLength))
  {
    _HTTPcode = HTTPCODE_CONNECTION_LOST;
  }

  SAFE_DELETE(_client)
  
  _client = nullptr;
  
  SAFE_DELETE_ARRAY(_connectedHost)
  
  _connectedHost = nullptr;
  
  _connectedPort  = -1;
  _requestEndTime = millis();
  _lastActivity   = 0;
  _setReadyState(readyStateDone);
  
  _AHTTP_unlock;
}

//**************************************************************************************************************
void  AsyncHTTPRequest::_onData(void* Vbuf, size_t len)
{
  AHTTP_LOGDEBUG3("_onData handler", (char*) Vbuf, ", len =", len);

  MUTEX_LOCK_NR
  
  _lastActivity = millis();

  // Transfer data to xbuf
  if (_chunks)
  {
    _chunks->write((uint8_t*)Vbuf, len);
    
    // KH, to remove
    AHTTP_LOGDEBUG("_onData: _processChunks");
    ///////
    
    _processChunks();
  }
  else
  {
    _response->write((uint8_t*)Vbuf, len);
  }

  // if headers not complete, collect them. If still not complete, just return.
  if (_readyState == readyStateOpened)
  {
    if ( ! _collectHeaders())
    {
      _AHTTP_unlock;
      
      // KH, to remove
      AHTTP_LOGDEBUG("_onData: headers not complete");
      ///////
      
      return;
    }
  }

  // If there's data in the buffer and not Done, advance readyState to Loading.
  if (_response->available() && _readyState != readyStateDone)
  {
    _setReadyState(readyStateLoading);
  }

  // If not chunked and all data read, close it up.
  if ( ! _chunked && (_response->available() + _contentRead) >= _contentLength)
  {
    char* connectionHdr = respHeaderValue("connection");

    if (connectionHdr && (strcasecmp_P(connectionHdr, PSTR("close")) == 0))
    {
      AHTTP_LOGDEBUG("*all data received - closing TCP");

      _client->close();
    }
    else
    {
      AHTTP_LOGDEBUG("*all data received - no disconnect");
    }

    _requestEndTime = millis();
    _lastActivity = 0;
    _timeout = 0;
    _setReadyState(readyStateDone);
  }

  // If onData callback requested, do so.
  if (_onDataCB && available())
  {
    _onDataCB(_onDataCBarg, this, available());
  }

  _AHTTP_unlock;

}

//**************************************************************************************************************
bool  AsyncHTTPRequest::_collectHeaders()
{
  AHTTP_LOGDEBUG("_collectHeaders()");

  // Loop to parse off each header line. Drop out and return false if no \r\n (incomplete)
  do
  {
    String headerLine = _response->readStringUntil("\r\n");

    // If no line, return false.
    if ( ! headerLine.length())
    {
      return false;
    }

    // If empty line, all headers are in, advance readyState.
    if (headerLine.length() == 2)
    {
      _setReadyState(readyStateHdrsRecvd);
    }
    // If line is HTTP header, capture HTTPcode.
    else if (headerLine.substring(0, 7) == "HTTP/1.")
    {
      _HTTPcode = headerLine.substring(9, headerLine.indexOf(' ', 9)).toInt();
    }
    // Ordinary header, add to header list.
    else
    {
      int colon = headerLine.indexOf(':');

      if (colon != -1)
      {
        String name = headerLine.substring(0, colon);
        name.trim();
        String value = headerLine.substring(colon + 1);
        value.trim();
        _addHeader(name.c_str(), value.c_str());
      }
    }
  } while (_readyState == readyStateOpened);

  // If content-Length header, set _contentLength
  header *hdr = _getHeader("Content-Length");

  if (hdr)
  {
    _contentLength = strtol(hdr->value, nullptr, 10);
  }

  // If chunked specified, try to set _contentLength to size of first chunk
  hdr = _getHeader("Transfer-Encoding");

  if (hdr && strcasecmp_P(hdr->value, PSTR("chunked")) == 0)
  {
    AHTTP_LOGDEBUG("*transfer-encoding: chunked");

    _chunked = true;
    _contentLength = 0;
    _chunks = new xbuf;
    _chunks->write(_response, _response->available());
    _processChunks();
  }

  return true;
}


/*_____________________________________________________________________________________________________________

                        H   H  EEEEE   AAA   DDDD   EEEEE  RRRR    SSS
                        H   H  E      A   A  D   D  E      R   R  S
                        HHHHH  EEE    AAAAA  D   D  EEE    RRRR    SSS
                        H   H  E      A   A  D   D  E      R  R       S
                        H   H  EEEEE  A   A  DDDD   EEEEE  R   R   SSS
  ______________________________________________________________________________________________________________*/

//**************************************************************************************************************
void AsyncHTTPRequest::setReqHeader(const char* name, const char* value)
{
  if (_readyState <= readyStateOpened && _headers)
  {
    _addHeader(name, value);
  }
}

//**************************************************************************************************************
void AsyncHTTPRequest::setReqHeader(const char* name, int32_t value)
{
  if (_readyState <= readyStateOpened && _headers)
  {
    setReqHeader(name, String(value).c_str());
  }
}

#if (ESP32 || ESP8266)

//**************************************************************************************************************
void AsyncHTTPRequest::setReqHeader(const char* name, const __FlashStringHelper* value)
{
  if (_readyState <= readyStateOpened && _headers)
  {
    char* _value = _charstar(value);
    _addHeader(name, _value);
    
    SAFE_DELETE_ARRAY(_value)
  }
}

//**************************************************************************************************************
void AsyncHTTPRequest::setReqHeader(const __FlashStringHelper *name, const char* value)
{
  if (_readyState <= readyStateOpened && _headers)
  {
    char* _name = _charstar(name);
    _addHeader(_name, value);
    
    SAFE_DELETE_ARRAY(_name)
  }
}

//**************************************************************************************************************
void AsyncHTTPRequest::setReqHeader(const __FlashStringHelper *name, const __FlashStringHelper* value)
{
  if (_readyState <= readyStateOpened && _headers)
  {
    char* _name = _charstar(name);
    char* _value = _charstar(value);
    _addHeader(_name, _value);
    
    SAFE_DELETE_ARRAY(_name)
    SAFE_DELETE_ARRAY(_value)
  }
}

//**************************************************************************************************************
void AsyncHTTPRequest::setReqHeader(const __FlashStringHelper *name, int32_t value)
{
  if (_readyState <= readyStateOpened && _headers)
  {
    char* _name = _charstar(name);
    setReqHeader(_name, String(value).c_str());
    
    SAFE_DELETE_ARRAY(_name)
  }
}

#endif

//**************************************************************************************************************
int AsyncHTTPRequest::respHeaderCount()
{
  if (_readyState < readyStateHdrsRecvd)
    return 0;

  int count = 0;
  header* hdr = _headers;

  while (hdr)
  {
    count++;
    hdr = hdr->next;
  }

  return count;
}

//**************************************************************************************************************
char* AsyncHTTPRequest::respHeaderName(int ndx) 
{
  if (_readyState < readyStateHdrsRecvd) 
    return nullptr;
    
  header* hdr = _getHeader(ndx);
  
  if ( ! hdr) 
    return nullptr;
    
  return hdr->name;
}

//**************************************************************************************************************
char* AsyncHTTPRequest::respHeaderValue(const char* name)
{
  if (_readyState < readyStateHdrsRecvd)
    return nullptr;

  header* hdr = _getHeader(name);

  if ( ! hdr)
    return nullptr;

  return hdr->value;
}

//**************************************************************************************************************
char* AsyncHTTPRequest::respHeaderValue(int ndx)
{
  if (_readyState < readyStateHdrsRecvd)
    return nullptr;

  header* hdr = _getHeader(ndx);

  if ( ! hdr)
    return nullptr;

  return hdr->value;
}

//**************************************************************************************************************
bool AsyncHTTPRequest::respHeaderExists(const char* name)
{
  if (_readyState < readyStateHdrsRecvd)
    return false;

  header* hdr = _getHeader(name);

  if ( ! hdr)
    return false;

  return true;
}


#if (ESP32 || ESP8266)

//**************************************************************************************************************
char* AsyncHTTPRequest::respHeaderValue(const __FlashStringHelper *name)
{
  if (_readyState < readyStateHdrsRecvd)
    return nullptr;

  char* _name = _charstar(name);
  header* hdr = _getHeader(_name);
  
  SAFE_DELETE_ARRAY(_name)

  if ( ! hdr)
    return nullptr;

  return hdr->value;
}

//**************************************************************************************************************
bool AsyncHTTPRequest::respHeaderExists(const __FlashStringHelper *name)
{
  if (_readyState < readyStateHdrsRecvd)
    return false;

  char* _name = _charstar(name);
  header* hdr = _getHeader(_name);
  
  SAFE_DELETE_ARRAY(_name)

  if ( ! hdr)
    return false;

  return true;
}

#endif

//**************************************************************************************************************
String AsyncHTTPRequest::headers()
{
  MUTEX_LOCK(String())
  
  String _response = "";
  header* hdr = _headers;

  while (hdr)
  {
    _response += hdr->name;
    _response += ':';
    _response += hdr->value;
    _response += "\r\n";
    hdr = hdr->next;
  }

  _response += "\r\n";
  
  _AHTTP_unlock;

  return _response;
}

//**************************************************************************************************************
AsyncHTTPRequest::header*  AsyncHTTPRequest::_addHeader(const char* name, const char* value)
{
  MUTEX_LOCK(nullptr)
  
  header* hdr = (header*) &_headers;

  while (hdr->next)
  {
    if (strcasecmp(name, hdr->next->name) == 0)
    {
      header* oldHdr  = hdr->next;
      hdr->next       = hdr->next->next;
      oldHdr->next    = nullptr;
      
      SAFE_DELETE(oldHdr)
    }
    else
    {
      hdr = hdr->next;
    }
  }

  hdr->next = new header;
  
  if (hdr->next)
  {
    hdr->next->name = new char[strlen(name) + 1];
    
    if (hdr->next->name)
      strcpy(hdr->next->name, name);
    else
    {
      SAFE_DELETE(hdr->next)
      
      return nullptr;
    }
    
    hdr->next->value = new char[strlen(value) + 1];
    
    if (hdr->next->value)
      strcpy(hdr->next->value, value); 
    else
    {
      SAFE_DELETE_ARRAY(hdr->next->name)
      SAFE_DELETE(hdr->next)
      
      return nullptr;
    }
  }
  else
  {
    return nullptr;
  }
  
  _AHTTP_unlock;

  return hdr->next;
}

//**************************************************************************************************************
AsyncHTTPRequest::header* AsyncHTTPRequest::_getHeader(const char* name)
{
  MUTEX_LOCK(nullptr)
  
  header* hdr = _headers;

  while (hdr)
  {
    if (strcasecmp(name, hdr->name) == 0)
      break;

    hdr = hdr->next;
  }

  _AHTTP_unlock;

  return hdr;
}

//**************************************************************************************************************
AsyncHTTPRequest::header* AsyncHTTPRequest::_getHeader(int ndx)
{
  MUTEX_LOCK(nullptr)
  
  header* hdr = _headers;

  while (hdr)
  {
    if ( ! ndx--)
      break;

    hdr = hdr->next;
  }

  _AHTTP_unlock;

  return hdr;
}

#if (ESP32 || ESP8266)

//**************************************************************************************************************
char* AsyncHTTPRequest::_charstar(const __FlashStringHelper * str)
{
  if ( ! str)
    return nullptr;

  char* ptr = new char[strlen_P((PGM_P)str) + 1];
  
  if (ptr)
  {
    strcpy_P(ptr, (PGM_P)str);
  }
  
  // Rturn good ptr or nullptr
  return ptr;
}

#endif

#endif    // ASYNC_HTTP_REQUEST_GENERIC_IMPL_H
