#include "inc/Globals.h"

#include "inc/ConfigurationManager.h"

const uint8_t c_BUTTON_DOWN_PIN = 13;
const uint8_t c_BUTTON_S_PIN = 33;
const uint8_t c_BUTTON_RIGHT_PIN = 14;
const uint8_t c_BUTTON_ON_PIN = 26;

const uint8_t c_BUTTON_SINGLE_CLICK_HOLD_DURATION = 240;
const uint16_t c_BUTTON_COMBO_CLICK_HOLD_DURATION = 3000;

const char* c_FLASH_LOG_FREQ_PARAM_NAME = "flashLogFreq";
const char* c_WIFI_RT_LOG_FREQ_PARAM_NAME = "wifiRtLogFreq";
const char* c_WIFI_SSID_PARAM_NAME = "wifiSsid";
const char* c_WIFI_PASSWORD_PARAM_NAME = "wifiPassword";
const char* c_MQTT_SERVER_URL_PARAM_NAME = "mqttServerUrl";

const char* c_SLOPE_PARAM_NAME = "SLOPE";
const char* c_GASINDEX_PARAM_NAME = "GASINDEX";

const char* c_INTERCEPT_PARAM_NAME = "INTERCEPT";
const char* c_SECONDP_PARAM_NAME = "SECONDP";

const char* c_INTERCEPT2_PARAM_NAME = "INTERCEPT2";
const char* c_SECONDP2_PARAM_NAME = "SECONDP2";

const char* c_INTERCEPT3_PARAM_NAME = "INTERCEPT3";
const char* c_SECONDP3_PARAM_NAME = "SECONDP3";

const char* c_INTERCEPT4_PARAM_NAME = "INTERCEPT4";
const char* c_SECONDP4_PARAM_NAME = "SECONDP4";


const char* c_GAS_AIR_PARAM_NAME = "Air";
const char* c_GAS_O2_PARAM_NAME = "O2";
const char* c_GAS_N2_PARAM_NAME = "N2";
const char* c_GAS_He_PARAM_NAME = "He";
const char* c_GAS_H2_PARAM_NAME = "H2";
const char* c_GAS_ARCH4_PARAM_NAME = "ArCH4";


ConfigurationManager g_configurationManager;
