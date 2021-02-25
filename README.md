# AsyncHTTPRequest_Generic

[![arduino-library-badge](https://www.ardu-badge.com/badge/AsyncHTTPRequest_Generic.svg?)](https://www.ardu-badge.com/AsyncHTTPRequest_Generic)
[![GitHub release](https://img.shields.io/github/release/khoih-prog/AsyncHTTPRequest_Generic.svg)](https://github.com/khoih-prog/AsyncHTTPRequest_Generic/releases)
[![GitHub](https://img.shields.io/github/license/mashape/apistatus.svg)](https://github.com/khoih-prog/AsyncHTTPRequest_Generic/blob/master/LICENSE)
[![contributions welcome](https://img.shields.io/badge/contributions-welcome-brightgreen.svg?style=flat)](#Contributing)
[![GitHub issues](https://img.shields.io/github/issues/khoih-prog/AsyncHTTPRequest_Generic.svg)](http://github.com/khoih-prog/AsyncHTTPRequest_Generic/issues)

---
---

## Table of Contents


* [Why do we need the new Async AsyncHTTPRequest_Generic library](#why-do-we-need-this-async-asynchttprequest_generic-library)
  * [Features](#features)
  * [Supports](#supports)
  * [Principles of operation](#principles-of-operation)
  * [Currently supported Boards](#currently-supported-boards)
* [Changelog](#changelog)
  * [Releases v1.1.3](#releases-v113)
  * [Releases v1.1.2](#releases-v112)
  * [Releases v1.1.1](#releases-v111)
  * [Releases v1.1.0](#releases-v110)
  * [Releases v1.0.2](#releases-v102)
  * [Releases v1.0.1](#releases-v101)
  * [Releases v1.0.0](#releases-v100)
* [AsyncHTTPRequest_Generic for ESP32, ESP8266 using built-in WiFi and STM32 boards using built-in LAN8742A Ethernet](#asynchttprequest_generic-for-esp32-esp8266-using-built-in-wifi-and-stm32-boards-using-built-in-lan8742a-ethernet)
* [Prerequisites](#prerequisites)
* [Installation](#installation)
  * [Use Arduino Library Manager](#use-arduino-library-manager)
  * [Manual Install](#manual-install)
  * [VS Code & PlatformIO](#vs-code--platformio)
* [Packages' Patches](#packages-patches)
  * [1. For Adafruit nRF52840 and nRF52832 boards](#1-for-adafruit-nRF52840-and-nRF52832-boards)
  * [2. For Teensy boards](#2-for-teensy-boards)
  * [3. For Arduino SAM DUE boards](#3-for-arduino-sam-due-boards)
  * [4. For Arduino SAMD boards](#4-for-arduino-samd-boards)
      * [For core version v1.8.10+](#for-core-version-v1810)
      * [For core version v1.8.9-](#for-core-version-v189-)
  * [5. For Adafruit SAMD boards](#5-for-adafruit-samd-boards)
  * [6. For Seeeduino SAMD boards](#6-for-seeeduino-samd-boards)
  * [7. For STM32 boards](#7-for-stm32-boards)
* [HOWTO Install esp32-s2 core for ESP32-S2 (Saola, AI-Thinker ESP-12K) boards into Arduino IDE)](#howto-install-esp32-s2-core-for-esp32-s2-saola-ai-thinker-esp-12k-boards-into-arduino-ide)
  * [1. Save the original esp32 core](#1-save-the-original-esp32-core)
  * [2. Download esp32-s2 core](#2-download-esp32-s2-core)
    * [2.1 Download zip](#21-download-zip)
    * [2.2 Unzip](#22-unzip)
    * [2.3 Update esp32-s2 core directories](#23-update-esp32-s2-core-directories)
  * [3. Download tools](#3-download-tools) 
    * [3.1 Download Toolchain for Xtensa (ESP32-S2) based on GCC](#31-download-toolchain-for-xtensa-esp32-s2-based-on-gcc)
    * [3.2 Download esptool](#32-download-esptool)
    * [3.3 Unzip](#33-unzip)
  * [4. Update tools](#4-update-tools)
    * [4.1 Update Toolchain](#41-update-toolchain)
    * [4.2 Update esptool](#42-update-esptool)
  * [5. esp32-s2 WebServer Library Patch](#5-esp32-s2-webserver-library-patch)
* [Note for Platform IO using ESP32 LittleFS](#note-for-platform-io-using-esp32-littlefs) 
* [HOWTO Fix `Multiple Definitions` Linker Error](#howto-fix-multiple-definitions-linker-error)
* [Note for Platform IO using ESP32 LittleFS](#note-for-platform-io-using-esp32-littlefs)
* [HOWTO Use analogRead() with ESP32 running WiFi and/or BlueTooth (BT/BLE)](#howto-use-analogread-with-esp32-running-wifi-andor-bluetooth-btble)
  * [1. ESP32 has 2 ADCs, named ADC1 and ADC2](#1--esp32-has-2-adcs-named-adc1-and-adc2)
  * [2. ESP32 ADCs functions](#2-esp32-adcs-functions)
  * [3. ESP32 WiFi uses ADC2 for WiFi functions](#3-esp32-wifi-uses-adc2-for-wifi-functions)
* [Examples](#examples)
  * [AsyncHTTPRequest_ESP](examples/AsyncHTTPRequest_ESP)
  * [AsyncHTTPRequest_ESP_WiFiManager](examples/AsyncHTTPRequest_ESP_WiFiManager)
  * [AsyncHTTPRequest_STM32](examples/AsyncHTTPRequest_STM32)
  * [AsyncCustomHeader_STM32](examples/AsyncCustomHeader_STM32)
  * [AsyncDweetGet_STM32](examples/AsyncDweetGet_STM32)
  * [AsyncDweetPost_STM32](examples/AsyncDweetPost_STM32)
  * [AsyncSimpleGET_STM32](examples/AsyncSimpleGET_STM32)
  * [AsyncWebClientRepeating_STM32](examples/AsyncWebClientRepeating_STM32)
* [Example AsyncHTTPRequest_STM32](#example-asynchttprequest_stm32)
  * [1. File AsyncHTTPRequest_STM32.ino](#1-file-asynchttprequest_stm32ino)
  * [2. File defines.h](#2-file-definesh) 
* [Debug Terminal Output Samples](#debug-termimal-output-samples)
  * [1. AsyncHTTPRequest_STM32 running on STM32F7 Nucleo-144 NUCLEO_F767ZI using built-in LAN8742A ](#1-asynchttprequest_stm32-running-on-stm32f7-nucleo-144-nucleo_f767zi-using-built-in-lan8742a)
  * [2. AsyncHTTPRequest_ESP_WiFiManager running on ESP8266_NODEMCU](#2-asynchttprequest_esp_wifimanager-running-on-esp8266_nodemcu)
  * [3. AsyncHTTPRequest_ESP_WiFiManager running on ESP32_DEV](#3-asynchttprequest_esp_wifimanager-running-on-esp32_dev)
  * [4. AsyncHTTPRequest_ESP running on ESP8266_NODEMCU](#4-asynchttprequest_esp-running-on-esp8266_nodemcu)
  * [5. AsyncWebClientRepeating_STM32 running on STM32F7 Nucleo-144 NUCLEO_F767ZI using built-in LAN8742A](#5-asyncwebclientrepeating_stm32-running-on-stm32f7-nucleo-144-nucleo_f767zi-using-built-in-lan8742a)
* [Debug](#debug)
* [Troubleshooting](#troubleshooting)
* [Issues](#issues)
* [Releases](#releases)
* [TO DO](#to-do)
* [DONE](#done)
* [Contributions and Thanks](#contributions-and-thanks)
* [Contributing](#contributing)
* [License and credits](#license-and-credits)
* [Copyright](#copyright)

---
---

## Why do we need this Async [AsyncHTTPRequest_Generic library](https://github.com/khoih-prog/AsyncHTTPRequest_Generic)

### Features

1. Asynchronous HTTP Request library for ESP8266, including ESP32-S2 (ESP32-S2 Saola, AI-Thinker ESP-12K, etc.) using built-in WiFi, and STM32 boards using built-in LAN8742A Ethernet. 
2. Providing a subset of HTTP.
3. Relying on on **[`ESPAsyncTCP`](https://github.com/me-no-dev/ESPAsyncTCP) for ESP8266, [`AsyncTCP`](https://github.com/me-no-dev/AsyncTCP) for ESP32** using built-in WiFi
4. Relying on **[`STM32duino LwIP`](https://github.com/stm32duino/LwIP)/[`STM32duino STM32Ethernet`](https://github.com/stm32duino/STM32Ethernet)/[`STM32AsyncTCP`](https://github.com/philbowles/STM32AsyncTCP) for STM32 using built-in LAN8742A Ethernet.**
5. Methods similar in format and usage to XmlHTTPrequest in Javascript.

### Supports

1. **GET, POST, PUT, PATCH, DELETE and HEAD**
2. Request and response headers
3. Chunked response
4. Single String response for short (<~5K) responses (heap permitting).
5. Optional onData callback.
6. Optional onReadyStatechange callback.

### Principles of operation

This library adds a simple HTTP layer on top of the ESPAsyncTCP/AsyncTCP/STM32 AsyncTCP library to **facilitate REST communication from a Client to a Server**. The paradigm is similar to the XMLHttpRequest in Javascript, employing the notion of a ready-state progression through the transaction request.

**Synchronization can be accomplished using callbacks on ready-state change, a callback on data receipt, or simply polling for ready-state change**. Data retrieval can be incremental as received, or bulk retrieved when the transaction completes provided there is enough heap to buffer the entire response.

The underlying buffering uses a new xbuf class. It handles both character and binary data. Class xbuf uses a chain of small (64 byte) segments that are allocated and added to the tail as data is added and deallocated from the head as data is read, achieving the same result as a dynamic circular buffer limited only by the size of heap. The xbuf implements indexOf and readUntil functions.

For short transactions, buffer space should not be an issue. In fact, it can be more economical than other methods that use larger fixed length buffers. Data is acked when retrieved by the caller, so there is some limited flow control to limit heap usage for larger transfers.

Request and response headers are handled in the typical fashion.

Chunked responses are recognized and handled transparently.

This library is based on, modified from:

1. [Bob Lemaire's asyncHTTPrequest Library](https://github.com/boblemaire/asyncHTTPrequest)

---

### Currently Supported Boards

#### 1. ESP32 including ESP32-S2 (ESP32-S2 Saola, AI-Thinker ESP-12K, etc.)

#### 2. ESP8266

#### 3. STM32F/L/H/G/WB/MP1 with built-in LAN8742A Ethernet.

1. Nucleo-144 (F429ZI, F746ZG, F756ZG, F767ZI)
2. Discovery STM32F746G-DISCOVERY
3. Any STM32 boards with enough flash/memory and already configured to run LAN8742A Ethernet.


---
---


## Changelog

### Releases v1.1.3

1. Fix non-persistent Connection header bug. Check [**'Connection' header expects 'disconnect' instead 'close' ? #13**](https://github.com/khoih-prog/AsyncHTTPRequest_Generic/issues/13)
2. Add ESP32-S2 support
3. Tested with [**Latest ESP32 Core 1.0.5**](https://github.com/espressif/arduino-esp32) for ESP32-based boards.

### Releases v1.1.2

1. Rename _lock and _unlock to avoid conflict with [**ESP32/ESP8266 AsyncWebServer**](https://github.com/me-no-dev/ESPAsyncWebServer) library. Check [**compatibility with ESPAsyncWebServer #11**](https://github.com/khoih-prog/AsyncHTTPRequest_Generic/issues/11)
2. Fix compiler warnings.

### Releases v1.1.1

1. Prevent crash if request and/or method not correct.


### Releases v1.1.0

1. Add HTTP PUT, PATCH, DELETE and HEAD methods. Check [Add support for sending PUT, PATCH, DELETE request](https://github.com/khoih-prog/AsyncHTTPRequest_Generic/issues/5)
2. Add Table of Contents
3. Add Version String


### Releases v1.0.2

1. Make Mutex Lock and delete more reliable and error-proof to prevent random crash.

### Releases v1.0.1

1. Restore cpp code besides Impl.h code to use in case of `multiple definition` linker error. Thanks to [Daniel Brunner](https://github.com/0xFEEDC0DE64) to report and make PR in [**Fixed linker errors when included in multiple .cpp files**](https://github.com/khoih-prog/AsyncHTTPRequest_Generic/pull/1). See [**HOWTO Fix `Multiple Definitions` Linker Error**](https://github.com/khoih-prog/AsyncHTTPRequest_Generic#HOWTO-Fix-Multiple-Definitions-Linker-Error)


### Releases v1.0.0

1. Initial coding to add support to **STM32F/L/H/G/WB/MP1** using built-in LAN8742A Ethernet (Nucleo-144, DISCOVERY, etc).
2. Add examples using STM32 boards.

---
---

## Prerequisites

 1. [`Arduino IDE 1.8.13+` for Arduino](https://www.arduino.cc/en/Main/Software)
 2. [`ESP8266 Core 2.7.4+`](https://github.com/esp8266/Arduino) for ESP8266-based boards. [![Latest release](https://img.shields.io/github/release/esp8266/Arduino.svg)](https://github.com/esp8266/Arduino/releases/latest/)
 3. [`ESP32 Core 1.0.5+`](https://github.com/espressif/arduino-esp32) for ESP32-based boards. [Latest stable release ![Release Version](https://img.shields.io/github/release/espressif/arduino-esp32.svg?style=plastic)
 4. [`ESP32S2 Core 1.0.4+`](https://github.com/espressif/arduino-esp32/tree/esp32s2) for ESP32-S2-based boards.
 5. [`Arduino Core for STM32 1.9.0+`](https://github.com/stm32duino/Arduino_Core_STM32) for for STM32 using built-in Ethernet LAN8742A. [![GitHub release](https://img.shields.io/github/release/stm32duino/Arduino_Core_STM32.svg)](https://github.com/stm32duino/Arduino_Core_STM32/releases/latest)
 6. [`ESPAsyncTCP v1.2.2+`](https://github.com/me-no-dev/ESPAsyncTCP) for ESP8266.
 7. [`AsyncTCP v1.1.1+`](https://github.com/me-no-dev/AsyncTCP) for ESP32.
 8. [`STM32Ethernet library v1.2.0+`](https://github.com/stm32duino/STM32Ethernet) for STM32 using built-in Ethernet LAN8742A on (Nucleo-144, Discovery). [![GitHub release](https://img.shields.io/github/release/stm32duino/STM32Ethernet.svg)](https://github.com/stm32duino/STM32Ethernet/releases/latest)
 9. [`LwIP library v2.1.2+`](https://github.com/stm32duino/LwIP) for STM32 using built-in Ethernet LAN8742A on (Nucleo-144, Discovery). [![GitHub release](https://img.shields.io/github/release/stm32duino/LwIP.svg)](https://github.com/stm32duino/LwIP/releases/latest)
10. [`STM32AsyncTCP library v1.0.0+`](https://github.com/philbowles/STM32AsyncTCP) for STM32 using built-in Ethernet LAN8742A on (Nucleo-144, Discovery).
11. [`ESPAsync_WiFiManager library v1.6.0+`](https://github.com/khoih-prog/ESPAsync_WiFiManager) for ESP32/ESP8266 using some examples. [![GitHub release](https://img.shields.io/github/release/khoih-prog/ESPAsync_WiFiManager.svg)](https://github.com/khoih-prog/ESPAsync_WiFiManager/releases)
12.  [`LittleFS_esp32 v1.0.5+`](https://github.com/lorol/LITTLEFS) for ESP32-based boards using LittleFS. To install, check [![arduino-library-badge](https://www.ardu-badge.com/badge/LittleFS_esp32.svg?)](https://www.ardu-badge.com/LittleFS_esp32).

---

## Installation

### Use Arduino Library Manager
The best and easiest way is to use `Arduino Library Manager`. Search for `AsyncHTTPRequest_Generic`, then select / install the latest version. You can also use this link [![arduino-library-badge](https://www.ardu-badge.com/badge/AsyncHTTPRequest_Generic.svg?)](https://www.ardu-badge.com/AsyncHTTPRequest_Generic) for more detailed instructions.

### Manual Install

1. Navigate to [AsyncHTTPRequest_Generic](https://github.com/khoih-prog/AsyncHTTPRequest_Generic) page.
2. Download the latest release `AsyncHTTPRequest_Generic-master.zip`.
3. Extract the zip file to `AsyncHTTPRequest_Generic-master` directory 
4. Copy the whole `AsyncHTTPRequest_Generic-master` folder to Arduino libraries' directory such as `~/Arduino/libraries/`.

### VS Code & PlatformIO

1. Install [VS Code](https://code.visualstudio.com/)
2. Install [PlatformIO](https://platformio.org/platformio-ide)
3. Install [**AsyncHTTPRequest_Generic** library](https://platformio.org/lib/show/11235/AsyncHTTPRequest_Generic) by using [Library Manager](https://platformio.org/lib/show/11235/AsyncHTTPRequest_Generic/installation). Search for AsyncHTTPRequest_Generic in [Platform.io Author's Libraries](https://platformio.org/lib/search?query=author:%22Khoi%20Hoang%22)
4. Use included [platformio.ini](platformio/platformio.ini) file from examples to ensure that all dependent libraries will installed automatically. Please visit documentation for the other options and examples at [Project Configuration File](https://docs.platformio.org/page/projectconf.html)

---
---

### Packages' Patches

#### 1. For Adafruit nRF52840 and nRF52832 boards

**To be able to compile, run and automatically detect and display BOARD_NAME on nRF52840/nRF52832 boards**, you have to copy the whole [nRF52 0.21.0](Packages_Patches/adafruit/hardware/nrf52/0.21.0) directory into Adafruit nRF52 directory (~/.arduino15/packages/adafruit/hardware/nrf52/0.21.0). 

Supposing the Adafruit nRF52 version is 0.21.0. These files must be copied into the directory:
- `~/.arduino15/packages/adafruit/hardware/nrf52/0.21.0/platform.txt`
- `~/.arduino15/packages/adafruit/hardware/nrf52/0.21.0/boards.txt`
- `~/.arduino15/packages/adafruit/hardware/nrf52/0.21.0/variants/NINA_B302_ublox/variant.h`
- `~/.arduino15/packages/adafruit/hardware/nrf52/0.21.0/variants/NINA_B302_ublox/variant.cpp`
- `~/.arduino15/packages/adafruit/hardware/nrf52/0.21.0/variants/NINA_B112_ublox/variant.h`
- `~/.arduino15/packages/adafruit/hardware/nrf52/0.21.0/variants/NINA_B112_ublox/variant.cpp`
- **`~/.arduino15/packages/adafruit/hardware/nrf52/0.21.0/cores/nRF5/Udp.h`**

Whenever a new version is installed, remember to copy these files into the new version directory. For example, new version is x.yy.z
These files must be copied into the directory:

- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/platform.txt`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/boards.txt`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/variants/NINA_B302_ublox/variant.h`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/variants/NINA_B302_ublox/variant.cpp`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/variants/NINA_B112_ublox/variant.h`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/variants/NINA_B112_ublox/variant.cpp`
- **`~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/cores/nRF5/Udp.h`**

#### 2. For Teensy boards
 
 **To be able to compile and run on Teensy boards**, you have to copy the files in [**Packages_Patches for Teensy directory**](Packages_Patches/hardware/teensy/avr) into Teensy hardware directory (./arduino-1.8.13/hardware/teensy/avr/boards.txt). 

Supposing the Arduino version is 1.8.13. These files must be copied into the directory:

- `./arduino-1.8.13/hardware/teensy/avr/boards.txt`
- `./arduino-1.8.13/hardware/teensy/avr/cores/teensy/Stream.h`
- `./arduino-1.8.13/hardware/teensy/avr/cores/teensy3/Stream.h`
- `./arduino-1.8.13/hardware/teensy/avr/cores/teensy4/Stream.h`

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
These files must be copied into the directory:

- `./arduino-x.yy.zz/hardware/teensy/avr/boards.txt`
- `./arduino-x.yy.zz/hardware/teensy/avr/cores/teensy/Stream.h`
- `./arduino-x.yy.zz/hardware/teensy/avr/cores/teensy3/Stream.h`
- `./arduino-x.yy.zz/hardware/teensy/avr/cores/teensy4/Stream.h`

#### 3. For Arduino SAM DUE boards
 
 **To be able to compile and run on SAM DUE boards**, you have to copy the whole [SAM DUE](Packages_Patches/arduino/hardware/sam/1.6.12) directory into Arduino sam directory (~/.arduino15/packages/arduino/hardware/sam/1.6.12). 

Supposing the Arduino SAM core version is 1.6.12. This file must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/sam/1.6.12/platform.txt`

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
This file must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/sam/x.yy.zz/platform.txt`

#### 4. For Arduino SAMD boards
 
 ***To be able to compile without error and automatically detect and display BOARD_NAME on Arduino SAMD (Nano-33-IoT, etc) boards***, you have to copy the whole [Arduino SAMD cores 1.8.10](Packages_Patches/arduino/hardware/samd/1.8.10) directory into Arduino SAMD directory (~/.arduino15/packages/arduino/hardware/samd/1.8.10).
 
#### For core version v1.8.10+

Supposing the Arduino SAMD version is 1.8.11. Now only one file must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/samd/1.8.11/platform.txt`

Whenever a new version is installed, remember to copy this files into the new version directory. For example, new version is x.yy.zz

This file must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/samd/x.yy.zz/platform.txt`
 
#### For core version v1.8.9-

Supposing the Arduino SAMD version is 1.8.9. These files must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/samd/1.8.9/platform.txt`
- ***`~/.arduino15/packages/arduino/hardware/samd/1.8.9/cores/arduino/Arduino.h`***

Whenever a new version is installed, remember to copy these files into the new version directory. For example, new version is x.yy.z

These files must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/samd/x.yy.z/platform.txt`
- ***`~/.arduino15/packages/arduino/hardware/samd/x.yy.z/cores/arduino/Arduino.h`***
 
 This is mandatory to fix the ***notorious Arduino SAMD compiler error***. See [Improve Arduino compatibility with the STL (min and max macro)](https://github.com/arduino/ArduinoCore-samd/pull/399)
 
```
 ...\arm-none-eabi\include\c++\7.2.1\bits\stl_algobase.h:243:56: error: macro "min" passed 3 arguments, but takes just 2
     min(const _Tp& __a, const _Tp& __b, _Compare __comp)
```

Whenever the above-mentioned compiler error issue is fixed with the new Arduino SAMD release, you don't need to copy the `Arduino.h` file anymore.

#### 5. For Adafruit SAMD boards
 
 ***To be able to automatically detect and display BOARD_NAME on Adafruit SAMD (Itsy-Bitsy M4, etc) boards***, you have to copy the file [Adafruit SAMD platform.txt](Packages_Patches/adafruit/hardware/samd/1.6.4) into Adafruit samd directory (~/.arduino15/packages/adafruit/hardware/samd/1.6.4). 

Supposing the Adafruit SAMD core version is 1.6.4. This file must be copied into the directory:

- `~/.arduino15/packages/adafruit/hardware/samd/1.6.4/platform.txt`

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
This file must be copied into the directory:

- `~/.arduino15/packages/adafruit/hardware/samd/x.yy.zz/platform.txt`

#### 6. For Seeeduino SAMD boards
 
 ***To be able to automatically detect and display BOARD_NAME on Seeeduino SAMD (XIAO M0, Wio Terminal, etc) boards***, you have to copy the file [Seeeduino SAMD platform.txt](Packages_Patches/Seeeduino/hardware/samd/1.8.1) into Adafruit samd directory (~/.arduino15/packages/Seeeduino/hardware/samd/1.8.1). 

Supposing the Seeeduino SAMD core version is 1.8.1. This file must be copied into the directory:

- `~/.arduino15/packages/Seeeduino/hardware/samd/1.8.1/platform.txt`

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
This file must be copied into the directory:

- `~/.arduino15/packages/Seeeduino/hardware/samd/x.yy.zz/platform.txt`

#### 7. For STM32 boards

**To use Serial1 on some STM32 boards without Serial1 definition (Nucleo-144 NUCLEO_F767ZI, Nucleo-64 NUCLEO_L053R8, etc.) boards**, you have to copy the files [STM32 variant.h](Packages_Patches/STM32/hardware/stm32/1.9.0) into STM32 stm32 directory (~/.arduino15/packages/STM32/hardware/stm32/1.9.0). You have to modify the files corresponding to your boards, this is just an illustration how to do.

Supposing the STM32 stm32 core version is 1.9.0. These files must be copied into the directory:

- `~/.arduino15/packages/STM32/hardware/stm32/1.9.0/variants/NUCLEO_F767ZI/variant.h` for Nucleo-144 NUCLEO_F767ZI.
- `~/.arduino15/packages/STM32/hardware/stm32/1.9.0/variants/NUCLEO_L053R8/variant.h` for Nucleo-64 NUCLEO_L053R8.

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz,
theses files must be copied into the corresponding directory:

- `~/.arduino15/packages/STM32/hardware/stm32/x.yy.zz/variants/NUCLEO_F767ZI/variant.h`
- `~/.arduino15/packages/STM32/hardware/stm32/x.yy.zz/variants/NUCLEO_L053R8/variant.h`

---
---

## HOWTO Install esp32-s2 core for ESP32-S2 (Saola, AI-Thinker ESP-12K) boards into Arduino IDE


These are instructions demonstrating the steps to install esp32-s2 core on Ubuntu machines. For Windows or other OS'es, just follow the the similar principles and steps.

Assuming you already installed Arduino IDE ESP32 core and the installed directory is

`/home/your_account/.arduino15/packages/esp32`


### 1. Save the original esp32 core

First, copy the whole original esp32 core to another safe place. Then delete all the sub-directories of

`/home/your_account/.arduino15/packages/esp32/hardware/esp32/1.0.4`

---

### 2. Download esp32-s2 core

#### 2.1 Download zip

Download [**esp32-s2 core**](https://github.com/espressif/arduino-esp32/tree/esp32s2) in the `zip` format: 

`arduino-esp32-esp32s2.zip`

#### 2.2 Unzip

<p align="center">
    <img src="https://github.com/khoih-prog/AsyncHTTPRequest_Generic/blob/master/Images/esp32_s2_Core_Unzipped.png">
</p>

#### 2.3 Update esp32-s2 core directories

Copy all subdirectories of esp32-s2 core into `/home/your_account/.arduino15/packages/esp32/hardware/esp32/1.0.4`

---

### 3 Download tools


#### 3.1 Download Toolchain for Xtensa (ESP32-S2) based on GCC

Download [**esp32-s2 Toolchain**](https://docs.espressif.com/projects/esp-idf/en/latest/esp32s2/api-guides/tools/idf-tools.html#xtensa-esp32s2-elf) corresponding to your environment (linux-amd64, win64, etc.).

For example `xtensa-esp32s2-elf-gcc8_4_0-esp-2020r3-linux-amd64.tar.gz`, then un-archive.


<p align="center">
    <img src="https://github.com/khoih-prog/AsyncHTTPRequest_Generic/blob/master/Images/esp32_s2_Toolchain.png">
</p>

#### 3.2 Download esptool


Download [esptool](https://github.com/espressif/esptool/releases) int the `zip` format:

`esptool-3.0.zip`

#### 3.3 Unzip

<p align="center">
    <img src="https://github.com/khoih-prog/AsyncHTTPRequest_Generic/blob/master/Images/esp32_s2_esptool.png">
</p>

---

### 4. Update tools

#### 4.1 Update Toolchain

Copy whole `xtensa-esp32s2-elf` directory into `/home/your_account/.arduino15/packages/esp32/hardware/esp32/1.0.4/tools`


#### 4.2 Update esptool

Rename `esptool-3.0` directory to `esptool`


Copy whole `esptool` directory into `/home/your_account/.arduino15/packages/esp32/hardware/esp32/1.0.4/tools`


<p align="center">
    <img src="https://github.com/khoih-prog/AsyncHTTPRequest_Generic/blob/master/Images/esp32_s2_tools.png">
</p>


### 5. esp32-s2 WebServer Library Patch

If you haven't installed a new version with [WebServer.handleClient delay PR #4350](https://github.com/espressif/arduino-esp32/pull/4350) or haven't applied the above mentioned PR, you have to use the following patch.


**To be able to run Config Portal on ESP32-S2 boards**, you have to copy the files in [esp32-s2 WebServer Patch](esp32s2_WebServer_Patch/) directory into esp32-s2 WebServer library directory (~/.arduino15/packages/esp32/hardware/esp32/1.0.4/libraries/WebServer).

Supposing the esp32-s2 version is 1.0.4, these files `WebServer.h/cpp` must be copied into the directory to replace:

- `~/.arduino15/packages/esp32/hardware/esp32/1.0.4/libraries/WebServer/src/WebServer.h`
- `~/.arduino15/packages/esp32/hardware/esp32/1.0.4/libraries/WebServer/src/WebServer.cpp`


---

That's it. You're now ready to compile and test for ESP32-S2 now

---
---

### Note for Platform IO using ESP32 LittleFS

In Platform IO, to fix the error when using [`LittleFS_esp32 v1.0`](https://github.com/lorol/LITTLEFS) for ESP32-based boards with ESP32 core v1.0.4- (ESP-IDF v3.2-), uncomment the following line

from

```
//#define CONFIG_LITTLEFS_FOR_IDF_3_2   /* For old IDF - like in release 1.0.4 */
```

to

```
#define CONFIG_LITTLEFS_FOR_IDF_3_2   /* For old IDF - like in release 1.0.4 */
```

It's advisable to use the latest [`LittleFS_esp32 v1.0.5+`](https://github.com/lorol/LITTLEFS) to avoid the issue.

Thanks to [Roshan](https://github.com/solroshan) to report the issue in [Error esp_littlefs.c 'utime_p'](https://github.com/khoih-prog/ESPAsync_WiFiManager/issues/28) 

---
---

### HOWTO Fix `Multiple Definitions` Linker Error

The current library implementation, using xyz-Impl.h instead of standard xyz.cpp, possibly creates certain `Multiple Definitions` Linker error in certain use cases. Although it's simple to just modify several lines of code, either in the library or in the application, the library is adding a separate source directory, named src_cpp, besides the standard src directory.

To use the old standard cpp way, just 

1. **Rename the h-only src directory into src_h.**
2. **Then rename the cpp src_cpp directory into src.**
3. Close then reopen the application code in Arduino IDE, etc. to recompile from scratch.

---
---

### Note for Platform IO using ESP32 LittleFS

In Platform IO, to fix the error when using [`LittleFS_esp32 v1.0`](https://github.com/lorol/LITTLEFS) for ESP32-based boards with ESP32 core v1.0.4- (ESP-IDF v3.2-), uncomment the following line

from

```
//#define CONFIG_LITTLEFS_FOR_IDF_3_2   /* For old IDF - like in release 1.0.4 */
```

to

```
#define CONFIG_LITTLEFS_FOR_IDF_3_2   /* For old IDF - like in release 1.0.4 */
```

It's advisable to use the latest [`LittleFS_esp32 v1.0.5+`](https://github.com/lorol/LITTLEFS) to avoid the issue.

Thanks to [Roshan](https://github.com/solroshan) to report the issue in [Error esp_littlefs.c 'utime_p'](https://github.com/khoih-prog/ESPAsync_WiFiManager/issues/28) 

---
---

### HOWTO Use analogRead() with ESP32 running WiFi and/or BlueTooth (BT/BLE)

Please have a look at [**ESP_WiFiManager Issue 39: Not able to read analog port when using the autoconnect example**](https://github.com/khoih-prog/ESP_WiFiManager/issues/39) to have more detailed description and solution of the issue.

#### 1.  ESP32 has 2 ADCs, named ADC1 and ADC2

#### 2. ESP32 ADCs functions

- ADC1 controls ADC function for pins **GPIO32-GPIO39**
- ADC2 controls ADC function for pins **GPIO0, 2, 4, 12-15, 25-27**

#### 3.. ESP32 WiFi uses ADC2 for WiFi functions

Look in file [**adc_common.c**](https://github.com/espressif/esp-idf/blob/master/components/driver/adc_common.c#L61)

> In ADC2, there're two locks used for different cases:
> 1. lock shared with app and Wi-Fi:
>    ESP32:
>         When Wi-Fi using the ADC2, we assume it will never stop, so app checks the lock and returns immediately if failed.
>    ESP32S2:
>         The controller's control over the ADC is determined by the arbiter. There is no need to control by lock.
> 
> 2. lock shared between tasks:
>    when several tasks sharing the ADC2, we want to guarantee
>    all the requests will be handled.
>    Since conversions are short (about 31us), app returns the lock very soon,
>    we use a spinlock to stand there waiting to do conversions one by one.
> 
> adc2_spinlock should be acquired first, then adc2_wifi_lock or rtc_spinlock.


- In order to use ADC2 for other functions, we have to **acquire complicated firmware locks and very difficult to do**
- So, it's not advisable to use ADC2 with WiFi/BlueTooth (BT/BLE).
- Use ADC1, and pins GPIO32-GPIO39
- If somehow it's a must to use those pins serviced by ADC2 (**GPIO0, 2, 4, 12, 13, 14, 15, 25, 26 and 27**), use the **fix mentioned at the end** of [**ESP_WiFiManager Issue 39: Not able to read analog port when using the autoconnect example**](https://github.com/khoih-prog/ESP_WiFiManager/issues/39) to work with ESP32 WiFi/BlueTooth (BT/BLE).

---
---

### Examples

Also see examples:
 1. [AsyncHTTPRequest_ESP](examples/AsyncHTTPRequest_ESP)
 2. [AsyncHTTPRequest_ESP_WiFiManager](examples/AsyncHTTPRequest_ESP_WiFiManager)
 3. [AsyncHTTPRequest_STM32](examples/AsyncHTTPRequest_STM32)
 4. [AsyncCustomHeader_STM32](examples/AsyncCustomHeader_STM32)
 5. [AsyncDweetGet_STM32](examples/AsyncDweetGet_STM32)
 6. [AsyncDweetPost_STM32](examples/AsyncDweetPost_STM32)
 7. [AsyncSimpleGET_STM32](examples/AsyncSimpleGET_STM32)
 8. [AsyncWebClientRepeating_STM32](examples/AsyncWebClientRepeating_STM32)

---

### Example [AsyncHTTPRequest_STM32](examples/AsyncHTTPRequest_STM32)

Please take a look at other examples, as well.

#### 1. File [AsyncHTTPRequest_STM32.ino](examples/AsyncHTTPRequest_STM32/AsyncHTTPRequest_STM32.ino)

```cpp
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
  while (!Serial);
  
  Serial.println("\nStart AsyncHTTPRequest_STM32 on " + String(BOARD_NAME));
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
```

---

#### 2. File [defines.h](examples/AsyncHTTPRequest_STM32/defines.h)


```cpp
/*
   Currently support
   1) STM32 boards with built-in Ethernet (to use USE_BUILTIN_ETHERNET = true) such as :
      - Nucleo-144 (F429ZI, F767ZI)
      - Discovery (STM32F746G-DISCOVERY)
      - STM32 boards (STM32F/L/H/G/WB/MP1) with 32K+ Flash, with Built-in Ethernet, 
      - See How To Use Built-in Ethernet at (https://github.com/khoih-prog/EthernetWebServer_STM32/issues/1)
   2) STM32F/L/H/G/WB/MP1 boards (with 32+K Flash) running ENC28J60 shields (to use USE_BUILTIN_ETHERNET = false)
   3) STM32F/L/H/G/WB/MP1 boards (with 32+K Flash) running W5x00 shields
*/

#ifndef defines_h
#define defines_h

#if !( defined(STM32F0) || defined(STM32F1) || defined(STM32F2) || defined(STM32F3)  ||defined(STM32F4) || defined(STM32F7) || \
       defined(STM32L0) || defined(STM32L1) || defined(STM32L4) || defined(STM32H7)  ||defined(STM32G0) || defined(STM32G4) || \
       defined(STM32WB) || defined(STM32MP1) )
  #error This code is designed to run on STM32F/L/H/G/WB/MP1 platform! Please check your Tools->Board setting.
#endif

#define ASYNC_HTTP_DEBUG_PORT           Serial

// Use from 0 to 4. Higher number, more debugging messages and memory usage.
#define _ASYNC_HTTP_LOGLEVEL_           1


#if defined(STM32F0)
  #warning STM32F0 board selected
  #define BOARD_TYPE  "STM32F0"
#elif defined(STM32F1)
  #warning STM32F1 board selected
  #define BOARD_TYPE  "STM32F1"
#elif defined(STM32F2)
  #warning STM32F2 board selected
  #define BOARD_TYPE  "STM32F2"
#elif defined(STM32F3)
  #warning STM32F3 board selected
  #define BOARD_TYPE  "STM32F3"
#elif defined(STM32F4)
  #warning STM32F4 board selected
  #define BOARD_TYPE  "STM32F4"
#elif defined(STM32F7)
  #warning STM32F7 board selected
  #define BOARD_TYPE  "STM32F7"
#elif defined(STM32L0)
  #warning STM32L0 board selected
  #define BOARD_TYPE  "STM32L0"
#elif defined(STM32L1)
  #warning STM32L1 board selected
  #define BOARD_TYPE  "STM32L1"
#elif defined(STM32L4)
  #warning STM32L4 board selected
  #define BOARD_TYPE  "STM32L4"
#elif defined(STM32H7)
  #warning STM32H7 board selected
  #define BOARD_TYPE  "STM32H7"
#elif defined(STM32G0)
  #warning STM32G0 board selected
  #define BOARD_TYPE  "STM32G0"
#elif defined(STM32G4)
  #warning STM32G4 board selected
  #define BOARD_TYPE  "STM32G4"
#elif defined(STM32WB)
  #warning STM32WB board selected
  #define BOARD_TYPE  "STM32WB"
#elif defined(STM32MP1)
  #warning STM32MP1 board selected
  #define BOARD_TYPE  "STM32MP1"
#else
  #warning STM32 unknown board selected
  #define BOARD_TYPE  "STM32 Unknown"
#endif

#ifndef BOARD_NAME
  #define BOARD_NAME    BOARD_TYPE
#endif

#include <LwIP.h>
#include <STM32Ethernet.h>

//#include <AsyncUDP_STM32.h>

// Enter a MAC address and IP address for your controller below.
#define NUMBER_OF_MAC      20

byte mac[][NUMBER_OF_MAC] =
{
  { 0xDE, 0xAD, 0xBE, 0xEF, 0x32, 0x01 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0x32, 0x02 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0x32, 0x03 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0x32, 0x04 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0x32, 0x05 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0x32, 0x06 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0x32, 0x07 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0x32, 0x08 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0x32, 0x09 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0x32, 0x0A },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0x32, 0x0B },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0x32, 0x0C },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0x32, 0x0D },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0x32, 0x0E },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0x32, 0x0F },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0x32, 0x10 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0x32, 0x11 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0x32, 0x12 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0x32, 0x13 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0x32, 0x14 },
};

// Select the static IP address according to your local network
IPAddress ip(192, 168, 2, 232);

#endif    //defines_h
```

---
---

### Debug Terminal Ouput Samples

#### 1. [AsyncHTTPRequest_STM32](examples/AsyncHTTPRequest_STM32) running on STM32F7 Nucleo-144 NUCLEO_F767ZI using built-in LAN8742A 

```
Start AsyncHTTPRequest_STM32 on NUCLEO_F767ZI
AsyncHTTPRequest_Generic v1.1.3
AsyncHTTPRequest @ IP : 192.168.2.72

**************************************
abbreviation: EDT
client_ip: aaa.bbb.ccc.ddd
datetime: 2020-09-13T18:22:59.555816-04:00
day_of_week: 0
day_of_year: 257
dst: true
dst_from: 2020-03-08T07:00:00+00:00
dst_offset: 3600
dst_until: 2020-11-01T06:00:00+00:00
raw_offset: -18000
timezone: America/Toronto
unixtime: 1600035779
utc_datetime: 2020-09-13T22:22:59.555816+00:00
utc_offset: -04:00
week_number: 37

**************************************
abbreviation: EDT
client_ip: aaa.bbb.ccc.ddd
datetime: 2020-09-13T18:27:57.586325-04:00
day_of_week: 0
day_of_year: 257
dst: true
dst_from: 2020-03-08T07:00:00+00:00
dst_offset: 3600
dst_until: 2020-11-01T06:00:00+00:00
raw_offset: -18000
timezone: America/Toronto
unixtime: 1600036077
utc_datetime: 2020-09-13T22:27:57.586325+00:00
utc_offset: -04:00
week_number: 37
**************************************
```

---

#### 2. [AsyncHTTPRequest_ESP_WiFiManager](examples/AsyncHTTPRequest_ESP_WiFiManager) running on ESP8266_NODEMCU

```
Starting AsyncHTTPRequest_ESP_WiFiManager using LittleFS on ESP8266_NODEMCU
AsyncHTTPRequest_Generic v1.1.3
Stored: SSID = HueNet1, Pass = 12345678
Got stored Credentials. Timeout 120s
ConnectMultiWiFi in setup
After waiting 3.43 secs more in setup(), connection result is connected. Local IP: 192.168.2.186
H
**************************************
abbreviation: EDT
client_ip: aaa.bbb.ccc.ddd
datetime: 2020-09-13T19:35:37.951609-04:00
day_of_week: 0
day_of_year: 257
dst: true
dst_from: 2020-03-08T07:00:00+00:00
dst_offset: 3600
dst_until: 2020-11-01T06:00:00+00:00
raw_offset: -18000
timezone: America/Toronto
unixtime: 1600040137
utc_datetime: 2020-09-13T23:35:37.951609+00:00
utc_offset: -04:00
week_number: 37
**************************************
HHHHHH

```

---

#### 3. [AsyncHTTPRequest_ESP_WiFiManager](examples/AsyncHTTPRequest_ESP_WiFiManager) running on ESP32_DEV

```
Starting AsyncHTTPRequest_ESP_WiFiManager using SPIFFS on ESP32_DEV
AsyncHTTPRequest_Generic v1.1.3
Stored: SSID = HueNet1, Pass = 12345678
Got stored Credentials. Timeout 120s
ConnectMultiWiFi in setup
After waiting 2.35 secs more in setup(), connection result is connected. Local IP: 192.168.2.232
H
**************************************
abbreviation: EDT
client_ip: aaa.bbb.ccc.ddd
datetime: 2020-09-13T19:37:02.118166-04:00
day_of_week: 0
day_of_year: 257
dst: true
dst_from: 2020-03-08T07:00:00+00:00
dst_offset: 3600
dst_until: 2020-11-01T06:00:00+00:00
raw_offset: -18000
timezone: America/Toronto
unixtime: 1600040222
utc_datetime: 2020-09-13T23:37:02.118166+00:00
utc_offset: -04:00
week_number: 37
**************************************
HHHHHHHHH HHHHHHHHHH HHHHHHHHHH H
**************************************
abbreviation: EDT
client_ip: aaa.bbb.ccc.ddd
datetime: 2020-09-13T19:42:01.507586-04:00
day_of_week: 0
day_of_year: 257
dst: true
dst_from: 2020-03-08T07:00:00+00:00
dst_offset: 3600
dst_until: 2020-11-01T06:00:00+00:00
raw_offset: -18000
timezone: America/Toronto
unixtime: 1600040521
utc_datetime: 2020-09-13T23:42:01.507586+00:00
utc_offset: -04:00
week_number: 37
**************************************
HHHHHHHHH HHHHHHHHHH HHHHHHHHHH 

```

---

#### 4. [AsyncHTTPRequest_ESP](examples/AsyncHTTPRequest_ESP) running on ESP8266_NODEMCU

```
Starting AsyncHTTPRequest_ESP using ESP8266_NODEMCU
AsyncHTTPRequest_Generic v1.1.3
Connecting to WiFi SSID: HueNet1
...........
HTTP WebServer is @ IP : 192.168.2.81

**************************************
abbreviation: EDT
client_ip: aaa.bbb.ccc.ddd
datetime: 2020-09-13T19:56:28.295033-04:00
day_of_week: 0
day_of_year: 257
dst: true
dst_from: 2020-03-08T07:00:00+00:00
dst_offset: 3600
dst_until: 2020-11-01T06:00:00+00:00
raw_offset: -18000
timezone: America/Toronto
unixtime: 1600041388
utc_datetime: 2020-09-13T23:56:28.295033+00:00
utc_offset: -04:00
week_number: 37
**************************************
HHHHHHHHH HHHHHHHHHH HHHHHHHHHH H
```

---

#### 5. [AsyncWebClientRepeating_STM32](examples/AsyncWebClientRepeating_STM32) running on STM32F7 Nucleo-144 NUCLEO_F767ZI using built-in LAN8742A


```
Start AsyncWebClientRepeating_STM32 on NUCLEO_F767ZI
AsyncHTTPRequest_Generic v1.1.3
AsyncHTTPRequest @ IP : 192.168.2.72

**************************************

           `:;;;,`                      .:;;:.           
        .;;;;;;;;;;;`                :;;;;;;;;;;:     TM 
      `;;;;;;;;;;;;;;;`            :;;;;;;;;;;;;;;;
     :;;;;;;;;;;;;;;;;;;         `;;;;;;;;;;;;;;;;;;
    ;;;;;;;;;;;;;;;;;;;;;       .;;;;;;;;;;;;;;;;;;;;
   ;;;;;;;;:`   `;;;;;;;;;     ,;;;;;;;;.`   .;;;;;;;;
  .;;;;;;,         :;;;;;;;   .;;;;;;;          ;;;;;;;
  ;;;;;;             ;;;;;;;  ;;;;;;,            ;;;;;;. 
 ,;;;;;               ;;;;;;.;;;;;;`              ;;;;;; 
 ;;;;;.                ;;;;;;;;;;;`      ```       ;;;;;`
 ;;;;;                  ;;;;;;;;;,       ;;;       .;;;;;
`;;;;:                  `;;;;;;;;        ;;;        ;;;;;
,;;;;`    `,,,,,,,,      ;;;;;;;      .,,;;;,,,     ;;;;;
:;;;;`    .;;;;;;;;       ;;;;;,      :;;;;;;;;     ;;;;;
:;;;;`    .;;;;;;;;      `;;;;;;      :;;;;;;;;     ;;;;;
.;;;;.                   ;;;;;;;.        ;;;        ;;;;;
 ;;;;;                  ;;;;;;;;;        ;;;        ;;;;;
 ;;;;;                 .;;;;;;;;;;       ;;;       ;;;;;,
 ;;;;;;               `;;;;;;;;;;;;                ;;;;; 
 `;;;;;,             .;;;;;; ;;;;;;;              ;;;;;; 
  ;;;;;;:           :;;;;;;.  ;;;;;;;            ;;;;;;
   ;;;;;;;`       .;;;;;;;,    ;;;;;;;;        ;;;;;;;:
    ;;;;;;;;;:,:;;;;;;;;;:      ;;;;;;;;;;:,;;;;;;;;;;
    `;;;;;;;;;;;;;;;;;;;.        ;;;;;;;;;;;;;;;;;;;;
      ;;;;;;;;;;;;;;;;;           :;;;;;;;;;;;;;;;;:
       ,;;;;;;;;;;;;;,              ;;;;;;;;;;;;;;
         .;;;;;;;;;`                  ,;;;;;;;;:         
                                                         
                                                         
                                                         
                                                         
    ;;;   ;;;;;`  ;;;;:  .;;  ;; ,;;;;;, ;;. `;,  ;;;;
    ;;;   ;;:;;;  ;;;;;; .;;  ;; ,;;;;;: ;;; `;, ;;;:;;
   ,;:;   ;;  ;;  ;;  ;; .;;  ;;   ,;,   ;;;,`;, ;;  ;;
   ;; ;:  ;;  ;;  ;;  ;; .;;  ;;   ,;,   ;;;;`;, ;;  ;;. 
   ;: ;;  ;;;;;:  ;;  ;; .;;  ;;   ,;,   ;;`;;;, ;;  ;;` 
  ,;;;;;  ;;`;;   ;;  ;; .;;  ;;   ,;,   ;; ;;;, ;;  ;;
  ;;  ,;, ;; .;;  ;;;;;:  ;;;;;: ,;;;;;: ;;  ;;, ;;;;;;
  ;;   ;; ;;  ;;` ;;;;.   `;;;:  ,;;;;;, ;;  ;;,  ;;;;


```

---
---

### Debug

Debug is enabled by default on Serial.

You can also change the debugging level from 0 to 4

```cpp
#define ASYNC_HTTP_DEBUG_PORT           Serial

// Use from 0 to 4. Higher number, more debugging messages and memory usage.
#define _ASYNC_HTTP_LOGLEVEL_           1
```
---

### Troubleshooting

If you get compilation errors, more often than not, you may need to install a newer version of the `ESP32 / ESP8266 / STM32` core for Arduino.

Sometimes, the library will only work if you update the `ESP32 / ESP8266 / STM32` core to the latest version because I am using newly added functions.

---

### Issues ###

Submit issues to: [AsyncHTTPRequest_Generic issues](https://github.com/khoih-prog/AsyncHTTPRequest_Generic/issues)

---

## TO DO

 1. Fix bug. Add enhancement
 2. Add support to more Ethernet / WiFi shields
 3. Add support to more boards.
 4. Add many more examples.


## DONE

 1. Initially add support to STM32 using built-in LAN8742A Etnernet. Tested on **STM32F7 Nucleo-144 F767ZI**.
 2. Add more examples.
 3. Add debugging features.
 4. Add PUT, PATCH, DELETE and HEAD besides GET and POST.

---
---

## Releases

### Releases v1.1.3

1. Fix non-persistent Connection header bug. Check [**'Connection' header expects 'disconnect' instead 'close' ? #13**](https://github.com/khoih-prog/AsyncHTTPRequest_Generic/issues/13)
2. Add ESP32-S2 support
3. Tested with [**Latest ESP32 Core 1.0.5**](https://github.com/espressif/arduino-esp32) for ESP32-based boards.

### Releases v1.1.2

1. Rename _lock and _unlock to avoid conflict with [**ESP32/ESP8266 AsyncWebServer**](https://github.com/me-no-dev/ESPAsyncWebServer) library. Check [**compatibility with ESPAsyncWebServer #11**](https://github.com/khoih-prog/AsyncHTTPRequest_Generic/issues/11)
2. Fix compiler warnings.

### Releases v1.1.1

1. Prevent crash if request and/or method not correct.

### Releases v1.1.0

1. Add HTTP PUT, PATCH, DELETE and HEAD methods. Check [Add support for sending PUT, PATCH, DELETE request](https://github.com/khoih-prog/AsyncHTTPRequest_Generic/issues/5)

### Releases v1.0.2

1. Make Mutex Lock and delete more reliable and error-proof to prevent random crash.

### Releases v1.0.1

1. Restore cpp code besides Impl.h code to use in case of `multiple definition` linker error. Thanks to [Daniel Brunner](https://github.com/0xFEEDC0DE64) to report and make PR in [**Fixed linker errors when included in multiple .cpp files**](https://github.com/khoih-prog/AsyncHTTPRequest_Generic/pull/1). See [**HOWTO Fix `Multiple Definitions` Linker Error**](https://github.com/khoih-prog/AsyncHTTPRequest_Generic#HOWTO-Fix-Multiple-Definitions-Linker-Error)

### Releases v1.0.0

1. Initial coding to add support to **STM32F/L/H/G/WB/MP1** using built-in LAN8742A Ethernet (Nucleo-144, DISCOVERY, etc).
2. Add examples using STM32 boards.

---
---

### Contributions and Thanks

This library is based on, modified, bug-fixed and improved from:

1. [Bob Lemaire's **asyncHTTPrequest Library**](https://github.com/boblemaire/asyncHTTPrequest) to use the better **asynchronous** features of these following Async TCP Libraries : ( [`ESPAsyncTCP`](https://github.com/me-no-dev/ESPAsyncTCP), [`AsyncTCP`](https://github.com/me-no-dev/AsyncTCP), and [`STM32AsyncTCP`](https://github.com/philbowles/STM32AsyncTCP) ).

2. Thanks to [Daniel Brunner](https://github.com/0xFEEDC0DE64) to report and make PR in [Fixed linker errors when included in multiple .cpp files](https://github.com/khoih-prog/AsyncHTTPRequest_Generic/pull/1) leading to v1.0.1. See [**HOWTO Fix `Multiple Definitions` Linker Error**](https://github.com/khoih-prog/AsyncHTTPRequest_Generic#HOWTO-Fix-Multiple-Definitions-Linker-Error)

3. Thanks to [gleniat](https://github.com/gleniat) to make enhancement request in [Add support for sending PUT, PATCH, DELETE request](https://github.com/khoih-prog/AsyncHTTPRequest_Generic/issues/5) leading to v1.1.0.

4. Thanks to [BadDwarf](https://github.com/baddwarf) to report [**compatibility with ESPAsyncWebServer #11**](https://github.com/khoih-prog/AsyncHTTPRequest_Generic/issues/11) leading to the enhancement in v1.1.2.

5. Thanks to [spdi](https://github.com/spdi) to report [**'Connection' header expects 'disconnect' instead 'close' ? #13**](https://github.com/khoih-prog/AsyncHTTPRequest_Generic/issues/13) leading to new release v1.1.3 to fix bug.


<table>
  <tr>
    <td align="center"><a href="https://github.com/boblemaire"><img src="https://github.com/boblemaire.png" width="100px;" alt="boblemaire"/><br /><sub><b>⭐️ Bob Lemaire</b></sub></a><br /></td>
    <td align="center"><a href="https://github.com/0xFEEDC0DE64"><img src="https://github.com/0xFEEDC0DE64.png" width="100px;" alt="0xFEEDC0DE64"/><br /><sub><b>Daniel Brunner</b></sub></a><br /></td>
    <td align="center"><a href="https://github.com/gleniat"><img src="https://github.com/gleniat.png" width="100px;" alt="gleniat"/><br /><sub><b>gleniat</b></sub></a><br /></td>
    <td align="center"><a href="https://github.com/baddwarf"><img src="https://github.com/baddwarf.png" width="100px;" alt="baddwarf"/><br /><sub><b>BadDwarf</b></sub></a><br /></td>
    <td align="center"><a href="https://github.com/spdi"><img src="https://github.com/spdi.png" width="100px;" alt="spdi"/><br /><sub><b>spdi</b></sub></a><br /></td>
  </tr> 
</table>

---

### Contributing

If you want to contribute to this project:
- Report bugs and errors
- Ask for enhancements
- Create issues and pull requests
- Tell other people about this library

---

### License and credits ###

- The library is licensed under [GPLv3](https://github.com/khoih-prog/AsyncHTTPRequest_Generic/blob/master/LICENSE)

---

## Copyright

Copyright (C) <2018>  <Bob Lemaire, IoTaWatt, Inc.>

Copyright 2020- Khoi Hoang



