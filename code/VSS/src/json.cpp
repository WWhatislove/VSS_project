#include <set.h>

String jsonRead(String &json, String name)
{
  DynamicJsonBuffer jsonBuffer;
  JsonObject &root = jsonBuffer.parseObject(json);
  return root[name].as<String>();
}

bool whiteNumber(String number)
{
  for (int i = 0; i < sizeJson(white_list); i++)
  {
    if (jsonReadNum(white_list, i) == number)
    {
      return true;
    }
  }
  return false;
}

void removeNumber(int index)
{
  DynamicJsonBuffer jsonBuffer;
  JsonArray &root = jsonBuffer.parseArray(white_list);
  root.remove(index);
  white_list = "";
  root.printTo(white_list);
  writeFile("white_list.json", white_list);
}

int sizeJson(String &json)
{
  DynamicJsonBuffer jsonBuffer;
  JsonArray &root = jsonBuffer.parseArray(json);
  return root.size();
}

String jsonReadNum(String &json, int count)
{
  DynamicJsonBuffer jsonBuffer;
  JsonArray &root = jsonBuffer.parseArray(json);
  return root.get<String>(count);
}

int jsonReadtoInt(String &json, String name)
{
  DynamicJsonBuffer jsonBuffer;
  JsonObject &root = jsonBuffer.parseObject(json);
  return root[name].as<int>();
}

String jsonWriteNumber(String &json, String number)
{
  DynamicJsonBuffer jsonBuffer;
  JsonArray &root = jsonBuffer.parseArray(json);
  root.add(number);
  json = "";
  root.printTo(json);
  return json;
}

String jsonWrite(String &json, String name, String volume)
{
  DynamicJsonBuffer jsonBuffer;
  JsonObject &root = jsonBuffer.parseObject(json);
  root[name] = volume;
  json = "";
  root.printTo(json);
  return json;
}

String jsonWrite(String &json, String name, int volume)
{
  DynamicJsonBuffer jsonBuffer;
  JsonObject &root = jsonBuffer.parseObject(json);
  root[name] = volume;
  json = "";
  root.printTo(json);
  return json;
}

void saveConfig()
{
  writeFile("config.json", configSetup);
}

String readFile(String fileName, size_t len)
{
  File configFile = SPIFFS.open("/" + fileName, "r");
  if (!configFile)
  {
    return "Failed";
  }
  size_t size = configFile.size();
  if (size > len)
  {
    configFile.close();
    return "Large";
  }
  String temp = configFile.readString();
  configFile.close();
  return temp;
}

String writeFile(String fileName, String strings)
{
  File configFile = SPIFFS.open("/" + fileName, "w");
  if (!configFile)
  {
    return "Failed to open config file";
  }
  configFile.print(strings);
  //strings.printTo(configFile);
  configFile.close();
  return "Write sucsses";
}
