

#include <set.h>

void setup()
{
    FS_init();
    HTTP_init();
    WIFIinit();
    OTA_init();
    configSetup = readFile("config.json", 4096);
}

void loop()
{
    HTTP.handleClient();
    ArduinoOTA.handle();
}