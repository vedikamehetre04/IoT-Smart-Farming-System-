#include <ArduinoIoTCloud.h>
#include <Arduino_ConnectionHandler.h>

const char DEVICE_LOGIN_NAME[]  = "723b604c-f300-4017-bb1b-8304e9b82971";

const char SSID[]               = SECRET_SSID;    // Network SSID (name)
const char PASS[]               = SECRET_OPTIONAL_PASS;    // Network password (use for WPA, or use as key for WEP)
const char DEVICE_KEY[]  = SECRET_DEVICE_KEY;    // Secret device password

void onWaterChange();

int moisture;
bool sunlight;
bool water;

void initProperties(){

  ArduinoCloud.setBoardId(DEVICE_LOGIN_NAME);
  ArduinoCloud.setSecretDeviceKey(DEVICE_KEY);
  ArduinoCloud.addProperty(moisture, READ, ON_CHANGE, NULL);
  ArduinoCloud.addProperty(sunlight, READ, ON_CHANGE, NULL);
  ArduinoCloud.addProperty(water, READWRITE, ON_CHANGE, onWaterChange);

}

WiFiConnectionHandler ArduinoIoTPreferredConnection(SSID, PASS);
