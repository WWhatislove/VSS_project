#include <set.h>
extern ESP8266WebServer HTTP;
extern String configSetup;
void genPage()
{
  String html = "{ \"configs\": [ \"/config.setup.json\", \"/lang/lang.ru.json\", \"/white_list.json\" ], \"title\": \"White List\", \"class\":\"col-sm-offset-1 col-sm-10 col-md-offset-2 col-md-8 col-lg-offset-3 col-lg-6\", \"headers\":\"Test Footer\", \"content\": [ { \"type\": \"h5\", \"title\": \"White List\", \"class\":\"alert-warning\", \"style\":\"\" }, { \"type\": \"link\", \"action\":\"/\", \"title\": \"Main\", \"class\":\"btn btn-block btn-success\", \"style\": \"width:25%\" }, { \"type\": \"button\", \"action\":\"/refresh\", \"title\": \"Refresh data\", \"class\":\"btn btn-block btn-warning\", \"style\": \"width:45%;display:inline;margin-right:10px;\" }, { \"type\": \"link\", \"action\":\"/index.htm?list\", \"title\": \"Refresh page\", \"class\":\"btn btn-block btn-warning\", \"style\": \"width:45%;float:right;\" }, {\"type\":\"hr\"}";
  ;

  html += "] }";
  writeFile("list.json", html);
}


void HTTP_init(void)
{ ESP8266HTTPUpdateServer httpUpdater;
  HTTP.on("/config.setup.json", HTTP_GET, []() {
    HTTP.send(200, "application/json", configSetup);
  });

  HTTP.on("/restart", HTTP_GET, []() {
    String restart = HTTP.arg("device");
    if (restart == "ok")
    {
      HTTP.send(200, "text / plain", "Reset OK");
      ESP.restart();
    }
    else
    {
      HTTP.send(200, "text / plain", "No Reset");
    }
  });

  httpUpdater.setup(&HTTP);

  HTTP.begin();
}
