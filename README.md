# AsyncHTTPRequest_Generic

[![arduino-library-badge](https://www.ardu-badge.com/badge/AsyncHTTPRequest_Generic.svg?)](https://www.ardu-badge.com/AsyncHTTPRequest_Generic)
[![GitHub release](https://img.shields.io/github/release/khoih-prog/AsyncHTTPRequest_Generic.svg)](https://github.com/khoih-prog/AsyncHTTPRequest_Generic/releases)
[![GitHub](https://img.shields.io/github/license/mashape/apistatus.svg)](https://github.com/khoih-prog/AsyncHTTPRequest_Generic/blob/master/LICENSE)
[![contributions welcome](https://img.shields.io/badge/contributions-welcome-brightgreen.svg?style=flat)](#Contributing)
[![GitHub issues](https://img.shields.io/github/issues/khoih-prog/AsyncHTTPRequest_Generic.svg)](http://github.com/khoih-prog/AsyncHTTPRequest_Generic/issues)

<a href="https://www.buymeacoffee.com/khoihprog6" title="Donate to my libraries using BuyMeACoffee"><img src="https://cdn.buymeacoffee.com/buttons/v2/default-yellow.png" alt="Donate to my libraries using BuyMeACoffee" style="height: 50px !important;width: 181px !important;" ></a>
<a href="https://www.buymeacoffee.com/khoihprog6" title="Donate to my libraries using BuyMeACoffee"><img src="https://img.shields.io/badge/buy%20me%20a%20coffee-donate-orange.svg?logo=buy-me-a-coffee&logoColor=FFDD00" style="height: 20px !important;width: 200px !important;" ></a>

---
---

## Table of Contents

* [Important Change from v1.6.0](#Important-Change-from-v160)
* [Why do we need the new Async AsyncHTTPRequest_Generic library](#why-do-we-need-this-async-asynchttprequest_generic-library)
  * [Features](#features)
  * [Supports](#supports)
  * [Principles of operation](#principles-of-operation)
  * [Currently supported Boards](#currently-supported-boards)
* [Changelog](changelog.md)
* [Prerequisites](#prerequisites)
* [Installation](#installation)
  * [Use Arduino Library Manager](#use-arduino-library-manager)
  * [Manual Install](#manual-install)
  * [VS Code & PlatformIO](#vs-code--platformio)
* [Packages' Patches](#packages-patches)
  * [1. For STM32 boards to use LAN8720](#1-for-stm32-boards-to-use-lan8720)
  * [2. For STM32 boards to use Serial1](#2-for-stm32-boards-to-use-serial1)
* [Note for Platform IO using ESP32 LittleFS](#note-for-platform-io-using-esp32-littlefs) 
* [HOWTO Fix `Multiple Definitions` Linker Error](#howto-fix-multiple-definitions-linker-error)
* [Note for Platform IO using ESP32 LittleFS](#note-for-platform-io-using-esp32-littlefs)
* [HOWTO Use analogRead() with ESP32 running WiFi and/or BlueTooth (BT/BLE)](#howto-use-analogread-with-esp32-running-wifi-andor-bluetooth-btble)
  * [1. ESP32 has 2 ADCs, named ADC1 and ADC2](#1--esp32-has-2-adcs-named-adc1-and-adc2)
  * [2. ESP32 ADCs functions](#2-esp32-adcs-functions)
  * [3. ESP32 WiFi uses ADC2 for WiFi functions](#3-esp32-wifi-uses-adc2-for-wifi-functions)
* [HOWTO use STM32F4 with LAN8720](#howto-use-stm32f4-with-lan8720)
  * [1. Wiring](#1-wiring)
  * [2. HOWTO program using STLink V-2 or V-3](#2-howto-program-using-stlink-v-2-or-v-3)
  * [3. HOWTO use Serial Port for Debugging](#3-howto-use-serial-port-for-debugging)
* [HOWTO use ESP8266 with W5x00 Ethernet](#HOWTO-use-ESP8266-with-W5x00-Ethernet)
	* [1. ESP8266 Wiring](#1-ESP8266-wiring)
* [Examples](#examples)
  * [For ESP32 and ESP8266](#for-esp32-and-esp8266)
    * [1. AsyncHTTPRequest_ESP](examples/AsyncHTTPRequest_ESP)
    * [2. AsyncHTTPRequest_ESP_WiFiManager](examples/AsyncHTTPRequest_ESP_WiFiManager)
    * [3. AsyncHTTPMultiRequests_ESP](examples/AsyncHTTPMultiRequests_ESP)
    * [4. AsyncHTTPRequest_ESP_Multi](examples/AsyncHTTPRequest_ESP_Multi) **New**
    * [5. AsyncHTTPRequest_ESP8266_Ethernet](examples/AsyncHTTPRequest_ESP8266_Ethernet) **New**
  * [For STM32 using LAN8742A](#for-stm32-using-lan8742a)
    * [1. AsyncHTTPRequest_STM32](examples/AsyncHTTPRequest_STM32)
    * [2. AsyncCustomHeader_STM32](examples/AsyncCustomHeader_STM32)
    * [3. AsyncDweetGet_STM32](examples/AsyncDweetGet_STM32)
    * [4. AsyncDweetPost_STM32](examples/AsyncDweetPost_STM32)
    * [5. AsyncSimpleGET_STM32](examples/AsyncSimpleGET_STM32)
    * [6. AsyncWebClientRepeating_STM32](examples/AsyncWebClientRepeating_STM32)
  * [For WT32_ETH01](#for-wt32_eth01)
    * [1. AsyncHTTPRequest_WT32_ETH01](examples/WT32_ETH01/AsyncHTTPRequest_WT32_ETH01)
    * [2. AsyncHTTPMultiRequests_WT32_ETH01](examples/WT32_ETH01/AsyncHTTPMultiRequests_WT32_ETH01)
  * [For ESP or STM32](#For-ESP-or-STM32)
    * [1. **multiFileProject**](examples/multiFileProject) **New** 
* [Example AsyncHTTPRequest_STM32](#example-asynchttprequest_stm32)
  * [1. File AsyncHTTPRequest_STM32.ino](#1-file-asynchttprequest_stm32ino)
  * [2. File defines.h](#2-file-definesh) 
* [Debug Terminal Output Samples](#debug-termimal-output-samples)
  * [1. AsyncHTTPRequest_STM32 running on STM32F7 Nucleo-144 NUCLEO_F767ZI using built-in LAN8742A ](#1-asynchttprequest_stm32-running-on-stm32f7-nucleo-144-nucleo_f767zi-using-built-in-lan8742a)
  * [2. AsyncHTTPRequest_ESP_WiFiManager running on ESP8266_NODEMCU](#2-asynchttprequest_esp_wifimanager-running-on-esp8266_nodemcu)
  * [3. AsyncHTTPRequest_ESP_WiFiManager running on ESP32_DEV](#3-asynchttprequest_esp_wifimanager-running-on-esp32_dev)
  * [4. AsyncHTTPRequest_ESP running on ESP8266_NODEMCU](#4-asynchttprequest_esp-running-on-esp8266_nodemcu)
  * [5. AsyncWebClientRepeating_STM32 running on STM32F7 Nucleo-144 NUCLEO_F767ZI using built-in LAN8742A](#5-asyncwebclientrepeating_stm32-running-on-stm32f7-nucleo-144-nucleo_f767zi-using-built-in-lan8742a)
  * [6. AsyncHTTPRequest_WT32_ETH01 on ESP32_DEV with ETH_PHY_LAN8720](#6-asynchttprequest_wt32_eth01-on-esp32_dev-with-eth_phy_lan8720)
  * [7. AsyncHTTPRequest_ESP_WiFiManager running on ESP32C3_DEV](#7-asynchttprequest_esp_wifimanager-running-on-ESP32C3_DEV) **New**
  * [8. AsyncHTTPRequest_ESP_WiFiManager running on ESP32S3_DEV](#8-asynchttprequest_esp_wifimanager-running-on-ESP32S3_DEV) **New**
  * [9. AsyncHTTPRequest_ESP_Multi running on ESP32_DEV](#9-AsyncHTTPRequest_ESP_Multi-running-on-ESP32_DEV) **New**
  * [10. AsyncHTTPRequest_ESP8266_Ethernet running on ESP8266_NODEMCU_ESP12E using ESP8266_W5500 Ethernet](#10-AsyncHTTPRequest_ESP8266_Ethernet-running-on-ESP8266_NODEMCU_ESP12E-using-ESP8266_W5500-Ethernet) **New**
  * [11. AsyncHTTPRequest_ESP8266_Ethernet running on ESP8266_NODEMCU_ESP12E using ESP8266_ENC28J60 Ethernet](#11-AsyncHTTPRequest_ESP8266_Ethernet-running-on-ESP8266_NODEMCU_ESP12E-using-ESP8266_ENC28J60-Ethernet) **New**
* [Debug](#debug)
* [Troubleshooting](#troubleshooting)
* [Issues](#issues)
* [TO DO](#to-do)
* [DONE](#done)
* [Contributions and Thanks](#contributions-and-thanks)
* [Contributing](#contributing)
* [License and credits](#license-and-credits)
* [Copyright](#copyright)

---
---

### Important Change from v1.6.0

Please have a look at [HOWTO Fix `Multiple Definitions` Linker Error](#howto-fix-multiple-definitions-linker-error)

---
---

## Why do we need this Async [AsyncHTTPRequest_Generic library](https://github.com/khoih-prog/AsyncHTTPRequest_Generic)

### Features

1. Asynchronous HTTP Request library for ESP8266, including ESP32-S2 (ESP32-S2 Saola, AI-Thinker ESP-12K, etc.) using built-in WiFi, WT32_ETH01 (ESP32 + LAN8720) and STM32 boards using LAN8720 or built-in LAN8742A Ethernet. 
2. Providing a subset of HTTP.
3. Relying on on **[`ESPAsyncTCP`](https://github.com/me-no-dev/ESPAsyncTCP) for ESP8266, [`AsyncTCP`](https://github.com/me-no-dev/AsyncTCP) for ESP32** using built-in WiFi
4. Relying on **[`STM32duino LwIP`](https://github.com/stm32duino/LwIP)/[`STM32duino STM32Ethernet`](https://github.com/stm32duino/STM32Ethernet)/[`STM32AsyncTCP`](https://github.com/philbowles/STM32AsyncTCP) for STM32 using LAN8720 or built-in LAN8742A Ethernet.**
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

#### 1. ESP32 including ESP32_S2 (ESP32_S2 Saola, AI-Thinker ESP-12K, etc.), ESP32_S3 and ESP32_C3

1. **ESP32-S2 (ESP32-S2 Saola, AI-Thinker ESP-12K, etc.) using EEPROM, SPIFFS or LittleFS**.
2. **ESP32-C3 (ARDUINO_ESP32C3_DEV) using EEPROM, SPIFFS or LittleFS**.
3. **ESP32-S3 (ESP32S3_DEV, ESP32_S3_BOX, UM TINYS3, UM PROS3, UM FEATHERS3, etc.) using EEPROM, SPIFFS or LittleFS**.

#### 2. ESP8266

1. Using WiFi
2. Using **W5x00** with [**lwIP_w5100**](https://github.com/esp8266/Arduino/tree/master/libraries/lwIP_w5100) or [**lwIP_w5500**](https://github.com/esp8266/Arduino/tree/master/libraries/lwIP_w5500) library
3. Using **ENC28J60** with [**lwIP_enc28j60**](https://github.com/esp8266/Arduino/tree/master/libraries/lwIP_enc28j60) library

#### 3. STM32F/L/H/G/WB/MP1 with built-in LAN8742A Ethernet.

1. Nucleo-144 (F429ZI, F746ZG, F756ZG, F767ZI)
2. Discovery STM32F746G-DISCOVERY
3. Any STM32 boards with enough flash/memory and already configured to run LAN8742A Ethernet.

#### 4. STM32 boards using Ethernet LAN8720

Support for LAN8720 has been **removed** from STM32 core v2.3.0
 
1. **Nucleo-144 (F429ZI, NUCLEO_F746NG, NUCLEO_F746ZG, NUCLEO_F756ZG)**
2. **Discovery (DISCO_F746NG)**
3. **STM32F4 boards (BLACK_F407VE, BLACK_F407VG, BLACK_F407ZE, BLACK_F407ZG, BLACK_F407VE_Mini, DIYMORE_F407VGT, FK407M1)**


#### 5. **WT32_ETH01** using ESP32-based boards and LAN8720 Ethernet

---
---

## Prerequisites

 1. [`Arduino IDE 1.8.19+` for Arduino](https://github.com/arduino/Arduino). [![GitHub release](https://img.shields.io/github/release/arduino/Arduino.svg)](https://github.com/arduino/Arduino/releases/latest)
 2. [`ESP8266 Core 3.0.2+`](https://github.com/esp8266/Arduino) for ESP8266-based boards. [![Latest release](https://img.shields.io/github/release/esp8266/Arduino.svg)](https://github.com/esp8266/Arduino/releases/latest/)
 3. [`ESP32 Core 2.0.5+`](https://github.com/espressif/arduino-esp32) for ESP32-based boards. [Latest stable release ![Release Version](https://img.shields.io/github/release/espressif/arduino-esp32.svg?style=plastic)
 5. [`Arduino Core for STM32 2.3.0+`](https://github.com/stm32duino/Arduino_Core_STM32) for for STM32 using built-in Ethernet LAN8742A. [![GitHub release](https://img.shields.io/github/release/stm32duino/Arduino_Core_STM32.svg)](https://github.com/stm32duino/Arduino_Core_STM32/releases/latest)
 6. [`ESPAsyncTCP v1.2.2+`](https://github.com/me-no-dev/ESPAsyncTCP) for ESP8266.
 7. [`AsyncTCP v1.1.1+`](https://github.com/me-no-dev/AsyncTCP) for ESP32.
 8. [`STM32Ethernet library v1.3.0+`](https://github.com/stm32duino/STM32Ethernet) for STM32 using built-in Ethernet LAN8742A on (Nucleo-144, Discovery). [![GitHub release](https://img.shields.io/github/release/stm32duino/STM32Ethernet.svg)](https://github.com/stm32duino/STM32Ethernet/releases/latest)
 9. [`LwIP library v2.1.2+`](https://github.com/stm32duino/LwIP) for STM32 using built-in Ethernet LAN8742A on (Nucleo-144, Discovery). [![GitHub release](https://img.shields.io/github/release/stm32duino/LwIP.svg)](https://github.com/stm32duino/LwIP/releases/latest)
10. [`STM32AsyncTCP library v1.0.1+`](https://github.com/khoih-prog/STM32AsyncTCP) for built-in Ethernet on (Nucleo-144, Discovery). To install manually for Arduino IDE.
11. [`ESPAsync_WiFiManager library v1.15.0+`](https://github.com/khoih-prog/ESPAsync_WiFiManager) for ESP32/ESP8266 using some examples. [![GitHub release](https://img.shields.io/github/release/khoih-prog/ESPAsync_WiFiManager.svg)](https://github.com/khoih-prog/ESPAsync_WiFiManager/releases)
12. [`LittleFS_esp32 v1.0.6+`](https://github.com/lorol/LITTLEFS) for ESP32-based boards using LittleFS with ESP32 core **v1.0.5-**. To install, check [![arduino-library-badge](https://www.ardu-badge.com/badge/LittleFS_esp32.svg?)](https://www.ardu-badge.com/LittleFS_esp32). **Notice**: This [`LittleFS_esp32 library`](https://github.com/lorol/LITTLEFS) has been integrated to Arduino [ESP32 core v1.0.6+](https://github.com/espressif/arduino-esp32/tree/master/libraries/LITTLEFS) and **you don't need to install it if using ESP32 core v1.0.6+**
13. [`WebServer_WT32_ETH01 library v1.5.1+`](https://github.com/khoih-prog/WebServer_WT32_ETH01) if necessary to use WT32_ETH01 boards. To install, check [![arduino-library-badge](https://www.ardu-badge.com/badge/WebServer_WT32_ETH01.svg?)](https://www.ardu-badge.com/WebServer_WT32_ETH01)

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
3. Install [**AsyncHTTPRequest_Generic** library](https://registry.platformio.org/libraries/khoih-prog/AsyncHTTPRequest_Generic) by using [Library Manager](https://registry.platformio.org/libraries/khoih-prog/AsyncHTTPRequest_Generic/installation). Search for AsyncHTTPRequest_Generic in [Platform.io Author's Libraries](https://platformio.org/lib/search?query=author:%22Khoi%20Hoang%22)
4. Use included [platformio.ini](platformio/platformio.ini) file from examples to ensure that all dependent libraries will installed automatically. Please visit documentation for the other options and examples at [Project Configuration File](https://docs.platformio.org/page/projectconf.html)

---
---

### Packages' Patches

#### 1. For STM32 boards to use LAN8720

To use LAN8720 on some STM32 boards 

- **Nucleo-144 (F429ZI, NUCLEO_F746NG, NUCLEO_F746ZG, NUCLEO_F756ZG)**
- **Discovery (DISCO_F746NG)**
- **STM32F4 boards (BLACK_F407VE, BLACK_F407VG, BLACK_F407ZE, BLACK_F407ZG, BLACK_F407VE_Mini, DIYMORE_F407VGT, FK407M1)**

you have to copy the files [stm32f4xx_hal_conf_default.h](Packages_Patches/STM32/hardware/stm32/2.3.0/system/STM32F4xx) and [stm32f7xx_hal_conf_default.h](Packages_Patches/STM32/hardware/stm32/2.3.0/system/STM32F7xx) into STM32 stm32 directory (~/.arduino15/packages/STM32/hardware/stm32/2.3.0/system) to overwrite the old files.

Supposing the STM32 stm32 core version is 2.3.0. These files must be copied into the directory:

- `~/.arduino15/packages/STM32/hardware/stm32/2.3.0/system/STM32F4xx/stm32f4xx_hal_conf_default.h` for STM32F4.
- `~/.arduino15/packages/STM32/hardware/stm32/2.3.0/system/STM32F7xx/stm32f7xx_hal_conf_default.h` for Nucleo-144 STM32F7.

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz,
theses files must be copied into the corresponding directory:

- `~/.arduino15/packages/STM32/hardware/stm32/x.yy.zz/system/STM32F4xx/stm32f4xx_hal_conf_default.h`
- `~/.arduino15/packages/STM32/hardware/stm32/x.yy.zz/system/STM32F7xx/stm32f7xx_hal_conf_default.h


#### 2. For STM32 boards to use Serial1

**To use Serial1 on some STM32 boards without Serial1 definition (Nucleo-144 NUCLEO_F767ZI, Nucleo-64 NUCLEO_L053R8, etc.) boards**, you have to copy the files [STM32 variant.h](Packages_Patches/STM32/hardware/stm32/2.3.0) into STM32 stm32 directory (~/.arduino15/packages/STM32/hardware/stm32/2.3.0). You have to modify the files corresponding to your boards, this is just an illustration how to do.

Supposing the STM32 stm32 core version is 2.3.0. These files must be copied into the directory:

- `~/.arduino15/packages/STM32/hardware/stm32/2.3.0/variants/STM32F7xx/F765Z(G-I)T_F767Z(G-I)T_F777ZIT/NUCLEO_F767ZI/variant.h` for Nucleo-144 NUCLEO_F767ZI.
- `~/.arduino15/packages/STM32/hardware/stm32/2.3.0/variants/STM32L0xx/L052R(6-8)T_L053R(6-8)T_L063R8T/NUCLEO_L053R8/variant.h` for Nucleo-64 NUCLEO_L053R8.

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz,
theses files must be copied into the corresponding directory:

- `~/.arduino15/packages/STM32/hardware/stm32/x.yy.zz/variants/STM32F7xx/F765Z(G-I)T_F767Z(G-I)T_F777ZIT/NUCLEO_F767ZI/variant.h`
- `~/.arduino15/packages/STM32/hardware/stm32/x.yy.zz/variants/STM32L0xx/L052R(6-8)T_L053R(6-8)T_L063R8T/NUCLEO_L053R8/variant.h`

---
---


### Note for Platform IO using ESP32 LittleFS

In Platform IO, to fix the error when using [`LittleFS_esp32 v1.0.6`](https://github.com/lorol/LITTLEFS) for ESP32-based boards with ESP32 core v1.0.4- (ESP-IDF v3.2-), uncomment the following line

from

```cpp
//#define CONFIG_LITTLEFS_FOR_IDF_3_2   /* For old IDF - like in release 1.0.4 */
```

to

```cpp
#define CONFIG_LITTLEFS_FOR_IDF_3_2   /* For old IDF - like in release 1.0.4 */
```

It's advisable to use the latest [`LittleFS_esp32 v1.0.5+`](https://github.com/lorol/LITTLEFS) to avoid the issue.

Thanks to [Roshan](https://github.com/solroshan) to report the issue in [Error esp_littlefs.c 'utime_p'](https://github.com/khoih-prog/ESPAsync_WiFiManager/issues/28) 

---
---

### HOWTO Fix `Multiple Definitions` Linker Error

The current library implementation, using `xyz-Impl.h` instead of standard `xyz.cpp`, possibly creates certain `Multiple Definitions` Linker error in certain use cases.

You can include this `.hpp` file

```cpp
// Can be included as many times as necessary, without `Multiple Definitions` Linker Error
#include "AsyncHTTPRequest_Generic.hpp"     //https://github.com/khoih-prog/AsyncHTTPRequest_Generic
```

in many files. But be sure to use the following `.h` file **in just 1 `.h`, `.cpp` or `.ino` file**, which must **not be included in any other file**, to avoid `Multiple Definitions` Linker Error

```cpp
// To be included only in main(), .ino with setup() to avoid `Multiple Definitions` Linker Error
#include "AsyncHTTPRequest_Generic.h"           //https://github.com/khoih-prog/AsyncHTTPRequest_Generic
```

Check the new [**multiFileProject** example](examples/multiFileProject) for a `HOWTO` demo.

Have a look at the discussion in [Different behaviour using the src_cpp or src_h lib #80](https://github.com/khoih-prog/ESPAsync_WiFiManager/discussions/80)

---
---

### Note for Platform IO using ESP32 LittleFS

In Platform IO, to fix the error when using [`LittleFS_esp32 v1.0`](https://github.com/lorol/LITTLEFS) for ESP32-based boards with ESP32 core v1.0.4- (ESP-IDF v3.2-), uncomment the following line

from

```cpp
//#define CONFIG_LITTLEFS_FOR_IDF_3_2   /* For old IDF - like in release 1.0.4 */
```

to

```cpp
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

### HOWTO use STM32F4 with LAN8720

#### 1. Wiring

This is the Wiring for STM32F4 (BLACK_F407VE, etc.) using LAN8720


|LAN8720 PHY|<--->|STM32F4|
|:-:|:-:|:-:|
|TX1|<--->|PB_13|
|TX_EN|<--->|PB_11|
|TX0|<--->|PB_12|
|RX0|<--->|PC_4|
|RX1|<--->|PC_5|
|nINT/RETCLK|<--->|PA_1|
|CRS|<--->|PA_7|
|MDIO|<--->|PA_2|
|MDC|<--->|PC_1|
|GND|<--->|GND|
|VCC|<--->|+3.3V|

---

#### 2. HOWTO program using STLink V-2 or V-3

Connect as follows. To program, use **STM32CubeProgrammer** or Arduino IDE with 

- **U(S)ART Support: "Enabled (generic Serial)"**
- **Upload Method : "STM32CubeProgrammer (SWD)"**


|STLink|<--->|STM32F4|
|:-:|:-:|:-:|
|SWCLK|<--->|SWCLK|
|SWDIO|<--->|SWDIO|
|RST|<--->|NRST|
|GND|<--->|GND|
|5v|<--->|5V|


<p align="center">
    <img src="https://github.com/khoih-prog/AsyncHTTPRequest_Generic/blob/master/Images/STM32F407VET6.png">
</p>

---

#### 3. HOWTO use Serial Port for Debugging

Connect FDTI (USB to Serial) as follows:

|FDTI|<--->|STM32F4|
|:-:|:-:|:-:|
|RX|<--->|TX=PA_9|
|TX|<--->|RX=PA_10|
|GND|<--->|GND|

---

### HOWTO use ESP8266 with W5x00 Ethernet

#### 1. ESP8266 Wiring

This is the wiring for EP8266 `W5x00` or `ENC28J60` Ethernet when using `SS = GPIO16`

https://github.com/khoih-prog/AsyncHTTPRequest_Generic/blob/e3dd512e7aa9e60c85043893d4527d3b052077c0/examples/AsyncHTTPRequest_ESP8266_Ethernet/AsyncHTTPRequest_ESP8266_Ethernet.ino#L65


|W5x00/ENC28J60 Ethernet|<--->|ESP8266|
|:-:|:-:|:-:|
|MOSI|<--->|MOSI = GPIO13|
|MISO|<--->|MISO = GPIO12|
|SCK|<--->|SCK = GPIO14|
|SS|<--->|GPIO16|
|GND|<--->|GND|
|VCC|<--->|+3.3V|


---
---

### Examples

#### For ESP32 and ESP8266

 1. [AsyncHTTPRequest_ESP](examples/AsyncHTTPRequest_ESP)
 2. [AsyncHTTPRequest_ESP_WiFiManager](examples/AsyncHTTPRequest_ESP_WiFiManager)
 3. [AsyncHTTPMultiRequests_ESP](examples/AsyncHTTPMultiRequests_ESP)
 4. [AsyncHTTPRequest_ESP_Multi](examples/AsyncHTTPRequest_ESP_Multi) **New**
 5. [AsyncHTTPRequest_ESP8266_Ethernet](examples/AsyncHTTPRequest_ESP8266_Ethernet) **New**

#### For STM32 using LAN8742A

 1. [AsyncHTTPRequest_STM32](examples/AsyncHTTPRequest_STM32)
 2. [AsyncCustomHeader_STM32](examples/AsyncCustomHeader_STM32)
 3. [AsyncDweetGet_STM32](examples/AsyncDweetGet_STM32)
 4. [AsyncDweetPost_STM32](examples/AsyncDweetPost_STM32)
 5. [AsyncSimpleGET_STM32](examples/AsyncSimpleGET_STM32)
 6. [AsyncWebClientRepeating_STM32](examples/AsyncWebClientRepeating_STM32)

#### For WT32_ETH01

 1. [AsyncHTTPRequest_WT32_ETH01](examples/WT32_ETH01/AsyncHTTPRequest_WT32_ETH01)
 2. [AsyncHTTPMultiRequests_WT32_ETH01](examples/WT32_ETH01/AsyncHTTPMultiRequests_ESP)
 
#### For ESP or STM32

 1. [**multiFileProject**](examples/multiFileProject) **New** 


---

### Example [AsyncHTTPRequest_STM32](examples/AsyncHTTPRequest_STM32)

Please take a look at other examples, as well.

#### 1. File [AsyncHTTPRequest_STM32.ino](examples/AsyncHTTPRequest_STM32/AsyncHTTPRequest_STM32.ino)

https://github.com/khoih-prog/AsyncHTTPRequest_Generic/blob/40e15e30f934e4b269b16a8ab8727558f0ab7b03/examples/AsyncHTTPRequest_STM32/AsyncHTTPRequest_STM32.ino#L43-L148


---

#### 2. File [defines.h](examples/AsyncHTTPRequest_STM32/defines.h)

https://github.com/khoih-prog/AsyncHTTPRequest_Generic/blob/40e15e30f934e4b269b16a8ab8727558f0ab7b03/examples/AsyncHTTPRequest_STM32/defines.h#L22-L134


---
---

### Debug Terminal Ouput Samples

#### 1. [AsyncHTTPRequest_STM32](examples/AsyncHTTPRequest_STM32) running on STM32F7 Nucleo-144 NUCLEO_F767ZI using built-in LAN8742A 

```
Start AsyncHTTPRequest_STM32 on NUCLEO_F767ZI
AsyncHTTPRequest_Generic v1.10.1
AsyncHTTPRequest @ IP : 192.168.2.178

**************************************
abbreviation: EDT
client_ip: aaa.bbb.ccc.ddd
datetime: 2022-10-20T16:16:16.759058-04:00
day_of_week: 4
day_of_year: 293
dst: true
dst_from: 2022-03-13T07:00:00+00:00
dst_offset: 3600
dst_until: 2022-11-06T06:00:00+00:00
raw_offset: -18000
timezone: America/Toronto
unixtime: 1666296976
utc_datetime: 2022-10-20T20:16:16.759058+00:00
utc_offset: -04:00
week_number: 42
*********************

**************************************
abbreviation: EDT
client_ip: aaa.bbb.ccc.ddd
datetime: 2022-10-20T16:17:16.713722-04:00
day_of_week: 4
day_of_year: 293
dst: true
dst_from: 2022-03-13T07:00:00+00:00
dst_offset: 3600
dst_until: 2022-11-06T06:00:00+00:00
raw_offset: -18000
timezone: America/Toronto
unixtime: 1666297036
utc_datetime: 2022-10-20T20:17:16.713722+00:00
utc_offset: -04:00
week_number: 42
```

---

#### 2. [AsyncHTTPRequest_ESP_WiFiManager](examples/AsyncHTTPRequest_ESP_WiFiManager) running on ESP8266_NODEMCU

```
Starting AsyncHTTPRequest_ESP_WiFiManager using LittleFS on ESP8266_NODEMCU
AsyncHTTPRequest_Generic v1.10.1
Stored: SSID = HueNet1, Pass = 12345678
Got stored Credentials. Timeout 120s
ConnectMultiWiFi in setup
After waiting 3.43 secs more in setup(), connection result is connected. Local IP: 192.168.2.186
H
**************************************
abbreviation: EDT
client_ip: aaa.bbb.ccc.ddd
datetime: 2022-10-20T16:19:16.751279-04:00
day_of_week: 4
day_of_year: 293
dst: true
dst_from: 2022-03-13T07:00:00+00:00
dst_offset: 3600
dst_until: 2022-11-06T06:00:00+00:00
raw_offset: -18000
timezone: America/Toronto
unixtime: 1666297156
utc_datetime: 2022-10-20T20:19:16.751279+00:00
utc_offset: -04:00
week_number: 42
**************************************
HHHHHH
```

---

#### 3. [AsyncHTTPRequest_ESP_WiFiManager](examples/AsyncHTTPRequest_ESP_WiFiManager) running on ESP32_DEV

```
Starting AsyncHTTPRequest_ESP_WiFiManager using SPIFFS on ESP32_DEV
AsyncHTTPRequest_Generic v1.10.1
Stored: SSID = HueNet1, Pass = 12345678
Got stored Credentials. Timeout 120s
ConnectMultiWiFi in setup
After waiting 2.35 secs more in setup(), connection result is connected. Local IP: 192.168.2.232
H
**************************************
abbreviation: EDT
client_ip: aaa.bbb.ccc.ddd
datetime: 2022-10-20T16:20:16.719881-04:00
day_of_week: 4
day_of_year: 293
dst: true
dst_from: 2022-03-13T07:00:00+00:00
dst_offset: 3600
dst_until: 2022-11-06T06:00:00+00:00
raw_offset: -18000
timezone: America/Toronto
unixtime: 1666297216
utc_datetime: 2022-10-20T20:20:16.719881+00:00
utc_offset: -04:00
week_number: 42
**************************************
HHHHHHHHH HHHHHHHHHH HHHHHHHHHH H
**************************************
abbreviation: EDT
client_ip: aaa.bbb.ccc.ddd
datetime: 2022-10-20T16:21:16.728312-04:00
day_of_week: 4
day_of_year: 293
dst: true
dst_from: 2022-03-13T07:00:00+00:00
dst_offset: 3600
dst_until: 2022-11-06T06:00:00+00:00
raw_offset: -18000
timezone: America/Toronto
unixtime: 1666297276
utc_datetime: 2022-10-20T20:21:16.728312+00:00
utc_offset: -04:00
week_number: 42
**************************************
HHHHHHHHH HHHHHHHHHH HHHHHHHHHH 
```

---

#### 4. [AsyncHTTPRequest_ESP](examples/AsyncHTTPRequest_ESP) running on ESP8266_NODEMCU

```
Starting AsyncHTTPRequest_ESP using ESP8266_NODEMCU
AsyncHTTPRequest_Generic v1.10.1
Connecting to WiFi SSID: HueNet1
...........
HTTP WebServer is @ IP : 192.168.2.81

**************************************
abbreviation: EDT
client_ip: aaa.bbb.ccc.ddd
datetime: 2022-10-20T16:22:16.769386-04:00
day_of_week: 4
day_of_year: 293
dst: true
dst_from: 2022-03-13T07:00:00+00:00
dst_offset: 3600
dst_until: 2022-11-06T06:00:00+00:00
raw_offset: -18000
timezone: America/Toronto
unixtime: 1666297336
utc_datetime: 2022-10-20T20:22:16.769386+00:00
utc_offset: -04:00
week_number: 42
**************************************
HHHHHHHHH HHHHHHHHHH HHHHHHHHHH H
```

---

#### 5. [AsyncWebClientRepeating_STM32](examples/AsyncWebClientRepeating_STM32) running on STM32F7 Nucleo-144 NUCLEO_F767ZI using built-in LAN8742A


```
Start AsyncWebClientRepeating_STM32 on NUCLEO_F767ZI
AsyncHTTPRequest_Generic v1.10.1
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

#### 6. [AsyncHTTPRequest_WT32_ETH01](examples/WT32_ETH01/AsyncHTTPRequest_WT32_ETH01) on ESP32_DEV with ETH_PHY_LAN8720

```
Starting AsyncHTTPRequest_WT32_ETH01 on ESP32_DEV with ETH_PHY_LAN8720
WebServer_WT32_ETH01 v1.5.1
AsyncHTTPRequest_Generic v1.10.1
ETH MAC: A8:03:2A:A1:61:73, IPv4: 192.168.2.232, FULL_DUPLEX, 100Mbps
AsyncHTTPRequest @ IP : 192.168.2.232

**************************************
abbreviation: EDT
client_ip: aaa.bbb.ccc.ddd
datetime: 2022-10-20T16:23:16.733395-04:00
day_of_week: 4
day_of_year: 293
dst: true
dst_from: 2022-03-13T07:00:00+00:00
dst_offset: 3600
dst_until: 2022-11-06T06:00:00+00:00
raw_offset: -18000
timezone: America/Toronto
unixtime: 1666297396
utc_datetime: 2022-10-20T20:23:16.733395+00:00
utc_offset: -04:00
week_number: 42
**************************************
```

---

#### 7. [AsyncHTTPRequest_ESP_WiFiManager](examples/AsyncHTTPRequest_ESP_WiFiManager) running on ESP32C3_DEV

```
Starting AsyncHTTPRequest_ESP_WiFiManager using LittleFS on ESP32C3_DEV
ESPAsync_WiFiManager v1.15.0
AsyncHTTPRequest_Generic v1.10.1
Stored: SSID = HueNet1, Pass = password
Got stored Credentials. Timeout 120s
ConnectMultiWiFi in setup
After waiting 9.23 secs more in setup(), connection result is connected. Local IP: 192.168.2.85
H
**************************************
abbreviation: EDT
client_ip: aaa.bbb.ccc.ddd
datetime: 2022-10-20T16:25:16.750043-04:00
day_of_week: 4
day_of_year: 293
dst: true
dst_from: 2022-03-13T07:00:00+00:00
dst_offset: 3600
dst_until: 2022-11-06T06:00:00+00:00
raw_offset: -18000
timezone: America/Toronto
unixtime: 1666297516
utc_datetime: 2022-10-20T20:25:16.750043+00:00
utc_offset: -04:00
week_number: 42
**************************************
HHHHHH
**************************************
abbreviation: EDT
client_ip: aaa.bbb.ccc.ddd
datetime: 2022-10-20T16:26:16.747520-04:00
day_of_week: 4
day_of_year: 293
dst: true
dst_from: 2022-03-13T07:00:00+00:00
dst_offset: 3600
dst_until: 2022-11-06T06:00:00+00:00
raw_offset: -18000
timezone: America/Toronto
unixtime: 1666297576
utc_datetime: 2022-10-20T20:26:16.747520+00:00
utc_offset: -04:00
week_number: 42
**************************************
```

---

#### 8. [AsyncHTTPRequest_ESP_WiFiManager](examples/AsyncHTTPRequest_ESP_WiFiManager) running on ESP32S3_DEV


```
Starting AsyncHTTPRequest_ESP_WiFiManager using LittleFS on ESP32S3_DEV
ESPAsync_WiFiManager v1.15.0
AsyncHTTPRequest_Generic v1.10.1
Stored: SSID = HueNet1, Pass = password
Got stored Credentials. Timeout 120s
ConnectMultiWiFi in setup
After waiting 7.77 secs more in setup(), connection result is connected. Local IP: 192.168.2.83
H
**************************************
abbreviation: EDT
client_ip: aaa.bbb.ccc.ddd
datetime: 2022-10-20T16:22:16.769386-04:00
day_of_week: 4
day_of_year: 293
dst: true
dst_from: 2022-03-13T07:00:00+00:00
dst_offset: 3600
dst_until: 2022-11-06T06:00:00+00:00
raw_offset: -18000
timezone: America/Toronto
unixtime: 1666297336
utc_datetime: 2022-10-20T20:22:16.769386+00:00
utc_offset: -04:00
week_number: 42
**************************************

HHHHHH
**************************************
abbreviation: EDT
client_ip: aaa.bbb.ccc.ddd
datetime: 2022-10-20T16:23:16.733395-04:00
day_of_week: 4
day_of_year: 293
dst: true
dst_from: 2022-03-13T07:00:00+00:00
dst_offset: 3600
dst_until: 2022-11-06T06:00:00+00:00
raw_offset: -18000
timezone: America/Toronto
unixtime: 1666297396
utc_datetime: 2022-10-20T20:23:16.733395+00:00
utc_offset: -04:00
week_number: 42
**************************************
```

---

#### 9. [AsyncHTTPRequest_ESP_Multi](examples/AsyncHTTPRequest_ESP_Multi) running on ESP32_DEV

The terminal output of [AsyncHTTPRequest_ESP_Multi example](examples/AsyncHTTPRequest_ESP_Multi) running on `ESP32_DEV` to demonstrate how to send requests to multiple addresses and receive responses from them. 

```
Starting AsyncHTTPRequest_ESP_Multi using ESP32_DEV
AsyncHTTPRequest_Generic v1.10.1
Connecting to WiFi SSID: HueNet1
.......
AsyncHTTPSRequest @ IP : 192.168.2.88

Sending request: http://worldtimeapi.org/api/timezone/Europe/Prague.txt

Sending request: http://www.myexternalip.com/raw

**************************************
abbreviation: CEST
client_ip: aaa.bbb.ccc.ddd
datetime: 2022-10-19T04:06:40.111091+02:00
day_of_week: 3
day_of_year: 292
dst: true
dst_from: 2022-03-27T01:00:00+00:00
dst_offset: 3600
dst_until: 2022-10-30T01:00:00+00:00
raw_offset: 3600
timezone: Europe/Prague
unixtime: 1666145200
utc_datetime: 2022-10-19T02:06:40.111091+00:00
utc_offset: +02:00
week_number: 42
**************************************

**************************************
aaa.bbb.ccc.ddd
**************************************

Sending request: http://worldtimeapi.org/api/timezone/America/Toronto.txt

**************************************
abbreviation: EDT
client_ip: aaa.bbb.ccc.ddd
datetime: 2022-10-18T22:06:42.109821-04:00
day_of_week: 2
day_of_year: 291
dst: true
dst_from: 2022-03-13T07:00:00+00:00
dst_offset: 3600
dst_until: 2022-11-06T06:00:00+00:00
raw_offset: -18000
timezone: America/Toronto
unixtime: 1666145202
utc_datetime: 2022-10-19T02:06:42.109821+00:00
utc_offset: -04:00
week_number: 42
**************************************
HHH
```

---

#### 10. [AsyncHTTPRequest_ESP8266_Ethernet](examples/AsyncHTTPRequest_ESP8266_Ethernet) running on ESP8266_NODEMCU_ESP12E using ESP8266_W5500 Ethernet

The terminal output of [AsyncHTTPRequest_ESP8266_Ethernet example](examples/AsyncHTTPRequest_ESP8266_Ethernet) running on `ESP8266_NODEMCU_ESP12E` to demonstrate how to use ESP8266_W5500 Ethernet Async feature.

```
Starting AsyncHTTPRequest_ESP8266_Ethernet on ESP8266_NODEMCU_ESP12E using ESP8266_W5500 Ethernet
AsyncHTTPRequest_Generic v1.10.1
Connecting ethernet..
Ethernet IP address: 192.168.2.187

**************************************
abbreviation: EDT
client_ip: aaa.bbb.ccc.ddd
datetime: 2022-10-20T16:24:16.747577-04:00
day_of_week: 4
day_of_year: 293
dst: true
dst_from: 2022-03-13T07:00:00+00:00
dst_offset: 3600
dst_until: 2022-11-06T06:00:00+00:00
raw_offset: -18000
timezone: America/Toronto
unixtime: 1666297456
utc_datetime: 2022-10-20T20:24:16.747577+00:00
utc_offset: -04:00
week_number: 42
**************************************
HHHHHH
**************************************
abbreviation: EDT
client_ip: aaa.bbb.ccc.ddd
datetime: 2022-10-20T16:25:16.750043-04:00
day_of_week: 4
day_of_year: 293
dst: true
dst_from: 2022-03-13T07:00:00+00:00
dst_offset: 3600
dst_until: 2022-11-06T06:00:00+00:00
raw_offset: -18000
timezone: America/Toronto
unixtime: 1666297516
utc_datetime: 2022-10-20T20:25:16.750043+00:00
utc_offset: -04:00
week_number: 42
**************************************
HH
```

---

#### 11. [AsyncHTTPRequest_ESP8266_Ethernet](examples/AsyncHTTPRequest_ESP8266_Ethernet) running on ESP8266_NODEMCU_ESP12E using ESP8266_ENC28J60 Ethernet

The terminal output of [AsyncHTTPRequest_ESP8266_Ethernet example](examples/AsyncHTTPRequest_ESP8266_Ethernet) running on `ESP8266_NODEMCU_ESP12E` to demonstrate how to use ESP8266_ENC28J60 Ethernet Async feature.

```
Starting AsyncHTTPRequest_ESP8266_Ethernet on ESP8266_NODEMCU_ESP12E using ESP8266_ENC28J60 Ethernet
AsyncHTTPRequest_Generic v1.10.1
Connecting to network : ..........................................................
Ethernet IP address: 192.168.2.187

**************************************
abbreviation: EDT
client_ip: aaa.bbb.ccc.ddd
datetime: 2022-10-20T16:16:16.759058-04:00
day_of_week: 4
day_of_year: 293
dst: true
dst_from: 2022-03-13T07:00:00+00:00
dst_offset: 3600
dst_until: 2022-11-06T06:00:00+00:00
raw_offset: -18000
timezone: America/Toronto
unixtime: 1666296976
utc_datetime: 2022-10-20T20:16:16.759058+00:00
utc_offset: -04:00
week_number: 42
**************************************
HHHHHH
**************************************
abbreviation: EDT
client_ip: aaa.bbb.ccc.ddd
datetime: 2022-10-20T16:17:16.713722-04:00
day_of_week: 4
day_of_year: 293
dst: true
dst_from: 2022-03-13T07:00:00+00:00
dst_offset: 3600
dst_until: 2022-11-06T06:00:00+00:00
raw_offset: -18000
timezone: America/Toronto
unixtime: 1666297036
utc_datetime: 2022-10-20T20:17:16.713722+00:00
utc_offset: -04:00
week_number: 42
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
 2. Add support to more Ethernet / WiFi shields with lwIP-based feature.
 3. Add support to more boards.
 4. Add many more examples.


## DONE

 1. Initially add support to STM32 using built-in LAN8742A Etnernet. Tested on **STM32F7 Nucleo-144 F767ZI**.
 2. Add more examples.
 3. Add debugging features.
 4. Add PUT, PATCH, DELETE and HEAD besides GET and POST.
 5. Add support to **Ethernet LAN8720** using [STM32Ethernet library](https://github.com/stm32duino/STM32Ethernet), for boards such as **Nucleo-144 (F429ZI, NUCLEO_F746NG, NUCLEO_F746ZG, NUCLEO_F756ZG), Discovery (DISCO_F746NG)** and **STM32F4 boards (BLACK_F407VE, BLACK_F407VG, BLACK_F407ZE, BLACK_F407ZG, BLACK_F407VE_Mini, DIYMORE_F407VGT, FK407M1)**
 6. Add support to **WT32_ETH01** using ESP32-based boards and LAN8720 Ethernet
 7. Auto detect ESP32 core to use for WT32_ETH01
 8. Fix bug in WT32_ETH01 examples to reduce connection time
 9. Fix `multiple-definitions` linker error and weird bug related to `src_cpp`.
10. Optimize library code by using `reference-passing` instead of `value-passing`
11. Enable compatibility with old code to include only `AsyncHTTPRequest_Generic.h`
12. Add support to **ESP32-S3 (ESP32S3_DEV, ESP32_S3_BOX, UM TINYS3, UM PROS3, UM FEATHERS3, etc.) using EEPROM, SPIFFS or LittleFS**
13. Add `LittleFS` support to **ESP32-C3**
14. Use `ESP32-core's LittleFS` library instead of `Lorol's LITTLEFS` library for ESP32 core v2.0.0+
15. Add example [AsyncHTTPRequest_ESP_Multi](https://github.com/khoih-prog/AsyncHTTPRequest_Generic/tree/master/examples/AsyncHTTPRequest_ESP_Multi) to demonstrate how to send requests to multiple addresses and receive responses from them.
16. Add support to ESP8266 using **W5x00** with [**lwIP_w5100**](https://github.com/esp8266/Arduino/tree/master/libraries/lwIP_w5100) or [**lwIP_w5500**](https://github.com/esp8266/Arduino/tree/master/libraries/lwIP_w5500) library
17. Add support to ESP8266 using **ENC28J60** with [**lwIP_enc28j60**](https://github.com/esp8266/Arduino/tree/master/libraries/lwIP_enc28j60) library
18. Fix long timeout if using `IPAddress`.
19. Remove support to STM32 using **LAN8720** due to problem with new STM32 core v2.3.0
20. Fix ESP32 chipID for example`AsyncHTTPRequest_ESP_WiFiManager`
21. Remove dependency on `LittleFS_esp32` library to prevent PIO error when using new ESP32 core v1.0.6+
22. Not try to reconnect to the same `host:port` after connected
23. Fix bug of wrong `reqStates` introduced from `v1.9.0`

---
---

### Contributions and Thanks

This library is based on, modified, bug-fixed and improved from:

 1. [Bob Lemaire's **asyncHTTPrequest Library**](https://github.com/boblemaire/asyncHTTPrequest) to use the better **asynchronous** features of these following Async TCP Libraries : ( [`ESPAsyncTCP`](https://github.com/me-no-dev/ESPAsyncTCP), [`AsyncTCP`](https://github.com/me-no-dev/AsyncTCP), and [`STM32AsyncTCP`](https://github.com/philbowles/STM32AsyncTCP) ).
 2. Thanks to [Daniel Brunner](https://github.com/0xFEEDC0DE64) to report and make PR in [Fixed linker errors when included in multiple .cpp files](https://github.com/khoih-prog/AsyncHTTPRequest_Generic/pull/1) leading to v1.0.1. See [**HOWTO Fix `Multiple Definitions` Linker Error**](https://github.com/khoih-prog/AsyncHTTPRequest_Generic#HOWTO-Fix-Multiple-Definitions-Linker-Error)
 3. Thanks to [gleniat](https://github.com/gleniat) to make enhancement request in [Add support for sending PUT, PATCH, DELETE request](https://github.com/khoih-prog/AsyncHTTPRequest_Generic/issues/5) leading to v1.1.0.
 4. Thanks to [BadDwarf](https://github.com/baddwarf) to report [**compatibility with ESPAsyncWebServer #11**](https://github.com/khoih-prog/AsyncHTTPRequest_Generic/issues/11) leading to the enhancement in v1.1.2.
 5. Thanks to [spdi](https://github.com/spdi) to report [**'Connection' header expects 'disconnect' instead 'close' ? #13**](https://github.com/khoih-prog/AsyncHTTPRequest_Generic/issues/13) leading to new release v1.1.3 to fix bug.
 6. Thanks to [andrewk123](https://github.com/andrewk123) to report [**Http GET polling causes crash when host disconnected #22**](https://github.com/khoih-prog/AsyncHTTPRequest_Generic/issues/22) leading to new release v1.4.0 to fix bug.
 7. Thanks to [DavidAntonin](https://github.com/DavidAntonin) to report [Cannot send requests to different addresses #4](https://github.com/khoih-prog/AsyncHTTPSRequest_Generic/issues/4) leading to new release v1.7.1 to demonstrate how to send requests to multiple addresses and receive responses from them.
 8. Thanks to [per1234](https://github.com/per1234) to make PR [Remove unavailable items from depends field of library.properties](https://github.com/khoih-prog/AsyncHTTPRequest_Generic/pull/35) leading to v1.8.2
 9. Thanks to [miwied](https://github.com/miwied) to report [setTimeout() hasn't any effect #38](https://github.com/khoih-prog/AsyncHTTPRequest_Generic/issues/38) leading to new release v1.9.0
10. Thanks to [ValentinsStorre](https://github.com/ValentinsStorre) to report [Release 1.9 breakes previously running code #39](https://github.com/khoih-prog/AsyncHTTPRequest_Generic/issues/39) leading to new release v1.10.1
11. Thanks to [Dirk Vranckaert](https://github.com/dirkvranckaert) to report [Callback behaviour is buggy (ESP8266) #43](https://github.com/khoih-prog/AsyncHTTPRequest_Generic/issues/43) leading to new release v1.10.1

<table>
  <tr>
    <td align="center"><a href="https://github.com/boblemaire"><img src="https://github.com/boblemaire.png" width="100px;" alt="boblemaire"/><br /><sub><b>⭐️ Bob Lemaire</b></sub></a><br /></td>
    <td align="center"><a href="https://github.com/0xFEEDC0DE64"><img src="https://github.com/0xFEEDC0DE64.png" width="100px;" alt="0xFEEDC0DE64"/><br /><sub><b>Daniel Brunner</b></sub></a><br /></td>
    <td align="center"><a href="https://github.com/gleniat"><img src="https://github.com/gleniat.png" width="100px;" alt="gleniat"/><br /><sub><b>gleniat</b></sub></a><br /></td>
    <td align="center"><a href="https://github.com/baddwarf"><img src="https://github.com/baddwarf.png" width="100px;" alt="baddwarf"/><br /><sub><b>BadDwarf</b></sub></a><br /></td>
    <td align="center"><a href="https://github.com/spdi"><img src="https://github.com/spdi.png" width="100px;" alt="spdi"/><br /><sub><b>spdi</b></sub></a><br /></td>
    <td align="center"><a href="https://github.com/andrewk123"><img src="https://github.com/andrewk123.png" width="100px;" alt="andrewk123"/><br /><sub><b>andrewk123</b></sub></a><br /></td>
  </tr>
  <tr>
    <td align="center"><a href="https://github.com/DavidAntonin"><img src="https://github.com/DavidAntonin.png" width="100px;" alt="DavidAntonin"/><br /><sub><b>DavidAntonin</b></sub></a><br /></td>
    <td align="center"><a href="https://github.com/per1234"><img src="https://github.com/per1234.png" width="100px;" alt="per1234"/><br /><sub><b>per1234</b></sub></a><br /></td>
    <td align="center"><a href="https://github.com/miwied"><img src="https://github.com/miwied.png" width="100px;" alt="miwied"/><br /><sub><b>miwied</b></sub></a><br /></td>
    <td align="center"><a href="https://github.com/ValentinsStorre"><img src="https://github.com/ValentinsStorre.png" width="100px;" alt="ValentinsStorre"/><br /><sub><b>ValentinsStorre</b></sub></a><br /></td>
    <td align="center"><a href="https://github.com/dirkvranckaert"><img src="https://github.com/dirkvranckaert.png" width="100px;" alt="dirkvranckaert"/><br /><sub><b>Dirk Vranckaert</b></sub></a><br /></td>
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
---

### License and credits ###

- The library is licensed under [GPLv3](https://github.com/khoih-prog/AsyncHTTPRequest_Generic/blob/master/LICENSE)

---

## Copyright

Copyright (C) <2018>  <Bob Lemaire, IoTaWatt, Inc.>

Copyright 2020- Khoi Hoang



