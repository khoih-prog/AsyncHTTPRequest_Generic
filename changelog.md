# AsyncHTTPRequest_Generic Library

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

* [Changelog](#changelog)
	* [Releases v1.13.0](#releases-v1130)
	* [Releases v1.12.0](#releases-v1120)
	* [Releases v1.11.0](#releases-v1110)
	* [Releases v1.10.2](#releases-v1102)
	* [Releases v1.10.1](#releases-v1101)
	* [Releases v1.10.0](#releases-v1100)
	* [Releases v1.9.2](#releases-v192)
	* [Releases v1.9.1](#releases-v191)
	* [Releases v1.9.0](#releases-v190)
	* [Releases v1.8.2](#releases-v182)
	* [Releases v1.8.1](#releases-v181)
	* [Releases v1.8.0](#releases-v180)
  * [Releases v1.7.1](#releases-v171)
  * [Releases v1.7.0](#releases-v170)
  * [Releases v1.6.0](#releases-v160)
  * [Releases v1.5.0](#releases-v150)
  * [Releases v1.4.1](#releases-v141)
  * [Releases v1.4.0](#releases-v140)
  * [Releases v1.3.1](#releases-v131)
  * [Releases v1.3.0](#releases-v130)
  * [Releases v1.2.0](#releases-v120)
  * [Releases v1.1.5](#releases-v115)
  * [Releases v1.1.4](#releases-v114)
  * [Releases v1.1.3](#releases-v113)
  * [Releases v1.1.2](#releases-v112)
  * [Releases v1.1.1](#releases-v111)
  * [Releases v1.1.0](#releases-v110)
  * [Releases v1.0.2](#releases-v102)
  * [Releases v1.0.1](#releases-v101)
  * [Releases v1.0.0](#releases-v100)

---
---

## Changelog

### Releases v1.13.0

1. Add support to ESP32 boards using `LwIP W6100 Ethernet`
2. Fix bug of `_parseURL()`. Check [Bug with _parseURL() #21](https://github.com/khoih-prog/AsyncHTTPSRequest_Generic/issues/21)
3. Improve `README.md` so that links can be used in other sites, such as `PIO`

### Releases v1.12.0

1. Add support to ESP32 boards using `LwIP W5500 Ethernet`
2. Fix bug. Check [Fix "blank new line in chunk" bug #50](https://github.com/khoih-prog/AsyncHTTPRequest_Generic/pull/50)

### Releases v1.11.0

1. Add support to ESP32 boards using `LwIP ENC28J60 Ethernet`
2. Use `allman astyle` and add `utils`. Restyle the library

### Releases v1.10.2

1. Default to reconnect to the same `host:port` after connected for new HTTP sites. Check [Host/Headers not always sent with 1.10.1 #44](https://github.com/khoih-prog/AsyncHTTPRequest_Generic/issues44)
2. Update `Packages' Patches`

### Releases v1.10.1

1. Fix bug of wrong `reqStates`. Check [Release 1.9 breaks previously running code #39](https://github.com/khoih-prog/AsyncHTTPRequest_Generic/issues/39) and [Callback behaviour is buggy (ESP8266) #43](https://github.com/khoih-prog/AsyncHTTPRequest_Generic/issues/43)
2. Optional larger `DEFAULT_RX_TIMEOUT` from default 3s, for slower networks

### Releases v1.10.0

1. Fix bug.
2. Clean up

### Releases v1.9.2

1. Not try to reconnect to the same host:port after connected. Check [setReuse feature #12](https://github.com/khoih-prog/AsyncHTTPSRequest_Generic/issues/12)
2. Update `Packages' Patches`

### Releases v1.9.1

1. Fix ESP32 chipID for example `AsyncHTTPRequest_ESP_WiFiManager`
2. Remove dependency on `LittleFS_esp32` library to prevent PIO error when using new ESP32 core v1.0.6+

### Releases v1.9.0

1. Fix long timeout if using `IPAddress`. Check [setTimeout() hasn't any effect #38](https://github.com/khoih-prog/AsyncHTTPRequest_Generic/issues/38)
2. Optimize code
3. Display only successful responseText in examples
4. Improve debug messages by adding functions to display error messages instead of `cryptic error number`
5. Remove support to STM32 using **LAN8720** due to problem with new STM32 core v2.3.0
5. Update `Packages' Patches`

### Releases v1.8.2

1. Fix library.properties to remove unavailable items from depends. Check [Remove unavailable items from depends field of library.properties #35](https://github.com/khoih-prog/AsyncHTTPRequest_Generic/pull/35)
2. Remove lorol's LittleFS_esp32 library dependency as LittleFS has been included in new ESP32 cores v1.0.6+
3. Fix compile error for [AsyncHTTPRequest_ESP_WiFiManager example](https://github.com/khoih-prog/AsyncHTTPRequest_Generic/tree/master/examples/AsyncHTTPRequest_ESP_WiFiManager)
4. Update `Packages' Patches`

### Releases v1.8.1

1. Add support to ESP8266 using ENC28J60 with [lwIP_enc28j60](https://github.com/esp8266/Arduino/tree/master/libraries/lwIP_enc28j60) library

### Releases v1.8.0

1. Add support to ESP8266 using W5x00 with [lwIP_w5100](https://github.com/esp8266/Arduino/tree/master/libraries/lwIP_w5100) or [lwIP_w5500](https://github.com/esp8266/Arduino/tree/master/libraries/lwIP_w5500) library
2. Add example [AsyncHTTPRequest_ESP8266_Ethernet](https://github.com/khoih-prog/AsyncHTTPRequest_Generic/tree/master/examples/AsyncHTTPRequest_ESP8266_Ethernet) to demo the new feature.
3. Update `Packages' Patches`

### Releases v1.7.1

1. Add example [AsyncHTTPRequest_ESP_Multi](https://github.com/khoih-prog/AsyncHTTPRequest_Generic/tree/master/examples/AsyncHTTPRequest_ESP_Multi) to demo connection to multiple addresses.
2. Update `Packages' Patches`

### Releases v1.7.0

1. Add support to new `ESP32-S3` 
2. Add `LittleFS` support to `ESP32-C3`
3. Use ESP32-core's LittleFS library instead of Lorol's LITTLEFS library for v2.0.0+

### Releases v1.6.0

1. Reduce the breaking effect of v1.5.0 by enabling compatibility with old code to include only `AsyncHTTPRequest_Generic.h`
2. Update `Packages' Patches`

### Releases v1.5.0

1. Fix `multiple-definitions` linker error and weird bug related to `src_cpp`. Check [Different behaviour using the src_cpp or src_h lib #80](https://github.com/khoih-prog/ESPAsync_WiFiManager/discussions/80)
2. Optimize library code by using `reference-passing` instead of `value-passing`
3. Update all examples

#### Releases v1.4.1

##### Warning: Releases v1.4.1+ can be used and autodetect ESP32 core v2.0.0+ or v1.0.6- for WT32_ETH01

1. Auto detect ESP32 core to use for WT32_ETH01
2. Fix bug in WT32_ETH01 examples to reduce connection time

### Releases v1.4.0

1. Fix crashing bug when request a non-existing IP. Check [Http GET polling causes crash when host disconnected #22](https://github.com/khoih-prog/AsyncHTTPRequest_Generic/issues/22)
2. Modify `platform.ini` to avoid compile error with PIO when using ESP8266/ESP32

### Releases v1.3.1

1. Update `platform.ini` and `library.json` to use original `khoih-prog` instead of `khoih.prog` after PIO fix
2. Update `Packages' Patches`

### Releases v1.3.0

1. Add support to WT32_ETH01 (ESP32 + LAN8720) boards
2. Add examples with new features

### Releases v1.2.0

1. Add support to **LAN8720** Ethernet for many **STM32F4** (F407xx, NUCLEO_F429ZI) and **STM32F7** (DISCO_F746NG, NUCLEO_F746ZG, NUCLEO_F756ZG) boards.
2. Add LAN8720 examples
3. Add Packages' Patches for STM32 to use LAN8720 with STM32Ethernet and LwIP libraries
4. Update ESP_WiFiManager-related example to fix multiWiFi timings to work better with latest esp32 core v1.0.6

### Releases v1.1.5

1. Fix dependency on unpublished [**STM32AsyncTCP Library**](https://github.com/philbowles/STM32AsyncTCP). Check [Compilation broken due to error in STM32AsyncTCP dependency](https://github.com/khoih-prog/AsyncWebServer_STM32/issues/4) and [how to run one of the examples?](https://github.com/khoih-prog/AsyncWebServer_STM32/issues/2).

### Releases v1.1.4

1. Fix `library.properties` dependency

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


