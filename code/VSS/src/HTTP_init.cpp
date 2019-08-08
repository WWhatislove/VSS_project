#include <set.h>

void genPage()
{
  String html = "{ \"configs\": [ \"/config.setup.json\", \"/lang/lang.ru.json\", \"/white_list.json\" ], \"title\": \"White List\", \"class\":\"col-sm-offset-1 col-sm-10 col-md-offset-2 col-md-8 col-lg-offset-3 col-lg-6\", \"headers\":\"Test Footer\", \"content\": [ { \"type\": \"h5\", \"title\": \"White List\", \"class\":\"alert-warning\", \"style\":\"\" }, { \"type\": \"link\", \"action\":\"/\", \"title\": \"Main\", \"class\":\"btn btn-block btn-success\", \"style\": \"width:25%\" }, { \"type\": \"button\", \"action\":\"/refresh\", \"title\": \"Refresh data\", \"class\":\"btn btn-block btn-warning\", \"style\": \"width:45%;display:inline;margin-right:10px;\" }, { \"type\": \"link\", \"action\":\"/index.htm?list\", \"title\": \"Refresh page\", \"class\":\"btn btn-block btn-warning\", \"style\": \"width:45%;float:right;\" }, {\"type\":\"hr\"}";
  ;

  if (sizeJson(white_list) <= 0)
    html += ", { \"type\": \"text\", \"title\": \"Тут ви можете бачити список телефонів на які буде реагувати система.\", \"class\": \"alert alert-info\", \"style\": \"width:50%;margin-left:auto;margin-right:auto;text-align:center\" }";
  else
  {
    int i = 0;
    for (i; i < sizeJson(white_list); i++)
    {
      html += ",{ \"type\": \"h4\", \"style\":\"width:50%;display:inline;border: 3px solid #ff8c00; border-radius: 10px;padding: 5px\", \"title\":\"'" + String(jsonReadNum(white_list, i)) + "'\" },";
      html += "{ \"type\":\"button\", \"title\":\"Delete\", \"style\":\"display:inline;margin-left:25px\", \"class\":\"btn btn-danger\", \"action\":\"/delete?id=" + String(i) + "\" },";
      html += "{\"type\":\"hr\"}";
    }
  }
  html += "] }";
  writeFile("list.json", html);
}

String prepareHtmlPage()
{
  int x = sizeJson(white_list);
  String htmlPage = "<html>";
  htmlPage += "<style> .input {background-color: #555555;;";
  htmlPage += " border: none;";
  htmlPage += " color: white; padding: 20px; text-align: center; text-decoration: none; display: inline-block; font-size: 16px; margin: 4px 2px; cursor: pointer;}";

  htmlPage += "<h3>Telephone numbers that are on the white list</h2>";
  for (int i = 0; i <= x; i++)
  {
    htmlPage += "<div class=\"card\">\n <div class=\"card-body\">\n" + String(jsonReadNum(white_list, i)) + "</div>\n</div>";
  }
  htmlPage += "</html>";

  return htmlPage;
}

void HTTP_init(void)
{
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
