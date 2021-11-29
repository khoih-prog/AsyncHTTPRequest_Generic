# AsyncHTTPRequest_Generic

[![arduino-library-badge](https://www.ardu-badge.com/badge/AsyncHTTPRequest_Generic.svg?)](https://www.ardu-badge.com/AsyncHTTPRequest_Generic)
[![GitHub release](https://img.shields.io/github/release/khoih-prog/AsyncHTTPRequest_Generic.svg)](https://github.com/khoih-prog/AsyncHTTPRequest_Generic/releases)
[![GitHub](https://img.shields.io/github/license/mashape/apistatus.svg)](https://github.com/khoih-prog/AsyncHTTPRequest_Generic/blob/master/LICENSE)
[![contributions welcome](https://img.shields.io/badge/contributions-welcome-brightgreen.svg?style=flat)](#Contributing)
[![GitHub issues](https://img.shields.io/github/issues/khoih-prog/AsyncHTTPRequest_Generic.svg)](http://github.com/khoih-prog/AsyncHTTPRequest_Generic/issues)

---
---

## Table of Contents

* [Changelog](#changelog)
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


