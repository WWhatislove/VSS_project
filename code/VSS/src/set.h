#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <FS.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include <ESP8266HTTPUpdateServer.h>
#include <SoftwareSerial.h>


// all functions in this project

//File system
void FS_init(void);
String getContentType(String filename);
bool handleFileRead(String path);
void handleFileUpload();
void handleFileDelete();
void handleFileCreate();
void handleFileList();

//HTTP
void genPage();
String prepareHtmlPage();
void HTTP_init(void);

//Json
String jsonRead(String &json, String name);
bool whiteNumber(String number);
void removeNumber(int index);
int sizeJson(String &json);
String jsonReadNum(String &json, int count);
int jsonReadtoInt(String &json, String name);
String jsonWriteNumber(String &json, String number);
String jsonWrite(String &json, String name, String volume);
String jsonWrite(String &json, String name, int volume);
void saveConfig();
String readFile(String fileName, size_t len);
String writeFile(String fileName, String strings);

//WiFi
void reconn_wifi();
void WIFIinit();
bool StartAPMode();

//OTA
void OTA_init();