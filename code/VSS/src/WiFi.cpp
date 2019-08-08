#include <set.h>
extern String configSetup;
void reconn_wifi()
{
  String _ssid = jsonRead(configSetup, "ssid");
  String _password = jsonRead(configSetup, "password");
  byte tries = 11;

  if (_ssid == "" && _password == "")
  {
    WiFi.begin();
  }
  else
  {
    WiFi.begin(_ssid.c_str(), _password.c_str());
  }

  while (--tries && WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(5000);

    if ((WiFi.status() != WL_CONNECTED))
    {

      Serial.println("");
      Serial.println("WiFi connected");
      Serial.println("__________");
      Serial.println(_ssid.c_str());
      Serial.println(_password.c_str());
      Serial.println("______ ____");
      Serial.println("IP address: ");
      Serial.println(WiFi.localIP());
    }
  }
}

void WIFIinit()
{
  extern ESP8266WebServer HTTP;
  HTTP.on("/ssid", HTTP_GET, []() {
    jsonWrite(configSetup, "ssid", HTTP.arg("ssid"));
    jsonWrite(configSetup, "password", HTTP.arg("password"));
    saveConfig();
    HTTP.send(200, "text/plain", "OK");
  });

  HTTP.on("/ssidap", HTTP_GET, []() {
    jsonWrite(configSetup, "ssidAP", HTTP.arg("ssidAP"));
    jsonWrite(configSetup, "passwordAP", HTTP.arg("passwordAP"));
    saveConfig();
    HTTP.send(200, "text/plain", "OK");
  });

  WiFi.disconnect();
  WiFi.softAPdisconnect();
  WiFi.mode(WIFI_OFF);
  delay(100);
  WiFi.mode(WIFI_STA);
  // WiFi.config(IPAddress(192, 168, 4, 4), IPAddress(192, 168, 4, 1), IPAddress(255, 255, 255, 0), IPAddress(192, 168, 4, 4));
  byte tries = 11;
  String _ssid = jsonRead(configSetup, "ssid");
  String _password = jsonRead(configSetup, "password");
  if (_ssid == "" && _password == "")
  {
    WiFi.begin();
  }
  else
  {
    WiFi.begin(_ssid.c_str(), _password.c_str());
  }

  while (--tries && WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  if (WiFi.status() != WL_CONNECTED)
  {
    StartAPMode();
  }
  else
  {

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("__________");
    Serial.println(_ssid.c_str());
    Serial.println(_password.c_str());
    Serial.println("______ ____");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
  }
}

bool StartAPMode()
{
  IPAddress apIP(192, 168, 4, 1);
  WiFi.disconnect();
  WiFi.config(IPAddress(192, 168, 4, 1), IPAddress(192, 168, 4, 1), IPAddress(255, 255, 255, 0), IPAddress(192, 168, 4, 4));
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
  String _ssidAP = jsonRead(configSetup, "ssidAP");
  String _passwordAP = jsonRead(configSetup, "passwordAP");
  WiFi.softAP(_ssidAP.c_str(), _passwordAP.c_str(), 13);
  return true;
}
