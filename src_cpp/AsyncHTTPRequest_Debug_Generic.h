/****************************************************************************************************************************
  AsyncHTTPRequest_Debug_Generic.h - Dead simple AsyncHTTPRequest for ESP8266, ESP32 and currently STM32 with built-in LAN8742A Ethernet
  
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
 
  Version: 1.1.1
  
  Version Modified By   Date      Comments
  ------- -----------  ---------- -----------
  1.0.0    K Hoang     14/09/2020 Initial coding to add support to STM32 using built-in Ethernet (Nucleo-144, DISCOVERY, etc).
  1.0.1    K Hoang     09/10/2020 Restore cpp code besides Impl.h code.
  1.0.2    K Hoang     09/11/2020 Make Mutex Lock and delete more reliable and error-proof
  1.1.0    K Hoang     23/12/2020 Add HTTP PUT, PATCH, DELETE and HEAD methods
  1.1.1    K Hoang     24/12/2020 Prevent crash if request and/or method not correct.
 *****************************************************************************************************************************/

#pragma once

#ifdef ASYNC_HTTP_DEBUG_PORT
  #define A_DBG_PORT      ASYNC_HTTP_DEBUG_PORT
#else
  #define A_DBG_PORT      Serial
#endif

// Change _ASYNC_HTTP_LOGLEVEL_ to set tracing and logging verbosity
// 0: DISABLED: no logging
// 1: ERROR: errors
// 2: WARN: errors and warnings
// 3: INFO: errors, warnings and informational (default)
// 4: DEBUG: errors, warnings, informational and debug

#ifndef _ASYNC_HTTP_LOGLEVEL_
  #define _ASYNC_HTTP_LOGLEVEL_       0
#endif

#define AHTTP_LOGERROR(x)         if(_ASYNC_HTTP_LOGLEVEL_>0) { A_DBG_PORT.print("[AHTTP] "); A_DBG_PORT.println(x); }
#define AHTTP_LOGERROR0(x)        if(_ASYNC_HTTP_LOGLEVEL_>0) { A_DBG_PORT.print(x); }
#define AHTTP_LOGERROR1(x,y)      if(_ASYNC_HTTP_LOGLEVEL_>0) { A_DBG_PORT.print("[AHTTP] "); A_DBG_PORT.print(x); A_DBG_PORT.print(" "); A_DBG_PORT.println(y); }
#define AHTTP_LOGERROR2(x,y,z)    if(_ASYNC_HTTP_LOGLEVEL_>0) { A_DBG_PORT.print("[AHTTP] "); A_DBG_PORT.print(x); A_DBG_PORT.print(" "); A_DBG_PORT.print(y); A_DBG_PORT.print(" "); A_DBG_PORT.println(z); }
#define AHTTP_LOGERROR3(x,y,z,w)  if(_ASYNC_HTTP_LOGLEVEL_>0) { A_DBG_PORT.print("[AHTTP] "); A_DBG_PORT.print(x); A_DBG_PORT.print(" "); A_DBG_PORT.print(y); A_DBG_PORT.print(" "); A_DBG_PORT.print(z); A_DBG_PORT.print(" "); A_DBG_PORT.println(w); }

#define AHTTP_LOGWARN(x)          if(_ASYNC_HTTP_LOGLEVEL_>1) { A_DBG_PORT.print("[AHTTP] "); A_DBG_PORT.println(x); }
#define AHTTP_LOGWARN0(x)         if(_ASYNC_HTTP_LOGLEVEL_>1) { A_DBG_PORT.print(x); }
#define AHTTP_LOGWARN1(x,y)       if(_ASYNC_HTTP_LOGLEVEL_>1) { A_DBG_PORT.print("[AHTTP] "); A_DBG_PORT.print(x); A_DBG_PORT.print(" "); A_DBG_PORT.println(y); }
#define AHTTP_LOGWARN2(x,y,z)     if(_ASYNC_HTTP_LOGLEVEL_>1) { A_DBG_PORT.print("[AHTTP] "); A_DBG_PORT.print(x); A_DBG_PORT.print(" "); A_DBG_PORT.print(y); A_DBG_PORT.print(" "); A_DBG_PORT.println(z); }
#define AHTTP_LOGWARN3(x,y,z,w)   if(_ASYNC_HTTP_LOGLEVEL_>1) { A_DBG_PORT.print("[AHTTP] "); A_DBG_PORT.print(x); A_DBG_PORT.print(" "); A_DBG_PORT.print(y); A_DBG_PORT.print(" "); A_DBG_PORT.print(z); A_DBG_PORT.print(" "); A_DBG_PORT.println(w); }

#define AHTTP_LOGINFO(x)          if(_ASYNC_HTTP_LOGLEVEL_>2) { A_DBG_PORT.print("[AHTTP] "); A_DBG_PORT.println(x); }
#define AHTTP_LOGINFO0(x)         if(_ASYNC_HTTP_LOGLEVEL_>2) { A_DBG_PORT.print(x); }
#define AHTTP_LOGINFO1(x,y)       if(_ASYNC_HTTP_LOGLEVEL_>2) { A_DBG_PORT.print("[AHTTP] "); A_DBG_PORT.print(x); A_DBG_PORT.print(" "); A_DBG_PORT.println(y); }
#define AHTTP_LOGINFO2(x,y,z)     if(_ASYNC_HTTP_LOGLEVEL_>2) { A_DBG_PORT.print("[AHTTP] "); A_DBG_PORT.print(x); A_DBG_PORT.print(" "); A_DBG_PORT.print(y); A_DBG_PORT.print(" "); A_DBG_PORT.println(z); }
#define AHTTP_LOGINFO3(x,y,z,w)   if(_ASYNC_HTTP_LOGLEVEL_>2) { A_DBG_PORT.print("[AHTTP] "); A_DBG_PORT.print(x); A_DBG_PORT.print(" "); A_DBG_PORT.print(y); A_DBG_PORT.print(" "); A_DBG_PORT.print(z); A_DBG_PORT.print(" "); A_DBG_PORT.println(w); }

#define AHTTP_LOGDEBUG(x)         if(_ASYNC_HTTP_LOGLEVEL_>3) { A_DBG_PORT.print("[AHTTP] "); A_DBG_PORT.println(x); }
#define AHTTP_LOGDEBUG0(x)        if(_ASYNC_HTTP_LOGLEVEL_>3) { A_DBG_PORT.print(x); }
#define AHTTP_LOGDEBUG1(x,y)      if(_ASYNC_HTTP_LOGLEVEL_>3) { A_DBG_PORT.print("[AHTTP] "); A_DBG_PORT.print(x); A_DBG_PORT.print(" "); A_DBG_PORT.println(y); }
#define AHTTP_LOGDEBUG2(x,y,z)    if(_ASYNC_HTTP_LOGLEVEL_>3) { A_DBG_PORT.print("[AHTTP] "); A_DBG_PORT.print(x); A_DBG_PORT.print(" "); A_DBG_PORT.print(y); A_DBG_PORT.print(" "); A_DBG_PORT.println(z); }
#define AHTTP_LOGDEBUG3(x,y,z,w)  if(_ASYNC_HTTP_LOGLEVEL_>3) { A_DBG_PORT.print("[AHTTP] "); A_DBG_PORT.print(x); A_DBG_PORT.print(" "); A_DBG_PORT.print(y); A_DBG_PORT.print(" "); A_DBG_PORT.print(z); A_DBG_PORT.print(" "); A_DBG_PORT.println(w); }

