#if !( defined(ESP8266) ||  defined(ESP32) )
  #error This code is intended to run on the ESP8266 or ESP32 platform! Please check your Tools->Board setting.
#endif

// Level from 0-4
#define ASYNC_HTTP_DEBUG_PORT      Serial

#define _ASYNC_HTTP_LOGLEVEL_      1

// 300s = 5 minutes to not flooding
#define HTTP_REQUEST_INTERVAL      300

// 10s
#define HEARTBEAT_INTERVAL          10

int status;     // the Wifi radio's status

const char* ssid        = "your_ssid";
const char* password    = "your_pass";

#if (ESP8266)
  #include <ESP8266WiFi.h>
#elif (ESP32)
  #include <WiFi.h>
#endif

// To be included only in main(), .ino with setup() to avoid `Multiple Definitions` Linker Error
#include <AsyncHTTPRequest_Generic.h>            // http://github.com/khoih-prog/AsyncHTTPRequest_Generic

#include <Ticker.h>

#define NUM_DIFFERENT_SITES     2

const char* addreses[][NUM_DIFFERENT_SITES] = 
{
  {"http://worldtimeapi.org/api/timezone/America/Toronto.txt", "http://worldtimeapi.org/api/timezone/Europe/Prague.txt"},
  {"http://www.myexternalip.com/raw"}
};

#define NUM_ENTRIES_SITE_0        2
#define NUM_ENTRIES_SITE_1        1

byte reqCount[NUM_DIFFERENT_SITES]  = { NUM_ENTRIES_SITE_0, NUM_ENTRIES_SITE_1 };
bool readySend[NUM_DIFFERENT_SITES] = { true, true };

AsyncHTTPRequest request[NUM_DIFFERENT_SITES];

void requestCB0(void* optParm, AsyncHTTPRequest* thisRequest, int readyState);
void requestCB1(void* optParm, AsyncHTTPRequest* thisRequest, int readyState);

void sendRequest0();
void sendRequest1();

typedef void (*requestCallback)(void* optParm, AsyncHTTPRequest* thisRequest, int readyState);
typedef void (*sendCallback)();

requestCallback requestCB     [NUM_DIFFERENT_SITES] = { requestCB0,   requestCB1   };
sendCallback    sendRequestCB [NUM_DIFFERENT_SITES] = { sendRequest0, sendRequest1 };

Ticker ticker;
Ticker ticker1;

void heartBeatPrint()
{
  static int num = 1;

  if (WiFi.status() == WL_CONNECTED)
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

void sendRequest(uint16_t index)
{
  static bool requestOpenResult;

  reqCount[index]--;
  readySend[index] = false;
  
  requestOpenResult = request[index].open("GET", addreses[index][reqCount[index]]);

  if (requestOpenResult)
  {
    // Only send() if open() returns true, or crash
    Serial.print("\nSending request: ");
    request[index].send();
  }
  else
  {
    Serial.print("\nCan't send bad request : ");
  }

  Serial.println(addreses[index][reqCount[index]]);
}

void sendRequest0()
{
  sendRequest(0);
}

void sendRequest1()
{
  sendRequest(1);
}

void sendRequests()
{
  for (int index = 0; index < NUM_DIFFERENT_SITES; index++)
  {
    reqCount[index] = 2;
  }
  reqCount[0] = NUM_ENTRIES_SITE_0;
  reqCount[1] = NUM_ENTRIES_SITE_1;
}


void requestCB0(void* optParm, AsyncHTTPRequest* thisRequest, int readyState)
{
  (void) optParm;

  if (readyState == readyStateDone)
  {
    Serial.println("\n**************************************");
    Serial.println(thisRequest->responseText());
    Serial.println("**************************************");

    thisRequest->setDebug(false);
    readySend[0] = true;
  }
}

void requestCB1(void* optParm, AsyncHTTPRequest* thisRequest, int readyState)
{
  (void) optParm;

  if (readyState == readyStateDone)
  {
    Serial.println("\n**************************************");
    Serial.println(thisRequest->responseText());
    Serial.println("**************************************");

    thisRequest->setDebug(false);
    readySend[1] = true;
  }
}

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  while (!Serial);

  Serial.println("\nStarting AsyncHTTPRequest_ESP_Multi using " + String(ARDUINO_BOARD));
  Serial.println(ASYNC_HTTP_REQUEST_GENERIC_VERSION);

  WiFi.mode(WIFI_STA);

  WiFi.begin(ssid, password);

  Serial.println("Connecting to WiFi SSID: " + String(ssid));

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.print(F("\nAsyncHTTPSRequest @ IP : "));
  Serial.println(WiFi.localIP());

  for (int index = 0; index < NUM_DIFFERENT_SITES; index++)
  {
    request[index].setDebug(false);

    request[index].onReadyStateChange(requestCB[index]); 
  }

  ticker.attach(HTTP_REQUEST_INTERVAL, sendRequests);

  ticker1.attach(HEARTBEAT_INTERVAL, heartBeatPrint);
}

void loop()
{
  for (int index = 0; index < NUM_DIFFERENT_SITES; index++)
  {
    if ((reqCount[index] > 0) && readySend[index])
    // OK but have to use delay(100)
    //if ( reqCount[index] > 0 )
    {
      sendRequestCB[index]();
  
      //delay(100);
    }
  }
}
