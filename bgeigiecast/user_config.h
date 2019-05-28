#ifndef USER_CONFIG_H
#define USER_CONFIG_H


/** System config **/
#define ENABLE_DEBUG 1 // 00974
#define DEBUG_LOG_STATE_TRANSITIONS 0
#define SERIAL_BAUD 115200
#define BGEIGIE_CONNECTION_BAUD 9600
#define USE_SLEEP 0

/** Hardware pins settings **/
#define RGB_LED_PIN_R A18
#define RGB_LED_PIN_G A4
#define RGB_LED_PIN_B A5

#define MODE_BUTTON_PIN 0

/** API connector settings **/
#define API_HOST "tt.safecast.org"
#define HEADER_API_CONTENT_TYPE "application/json"
#define HEADER_API_USER_AGENT "ESP32"
#define API_MEASUREMENTS_ENDPOINT "http://" API_HOST "/measurements.json"
#define API_SEND_FREQUENCY_SECONDS 300 // 5 minutes
#define API_SEND_FREQUENCY_SECONDS_ALERT 60 // 1 minute
#define API_SEND_FREQUENCY_SECONDS_DEV 30 // 30 seconds
#define API_SEND_FREQUENCY_SECONDS_ALERT_DEV 10 // 10 seconds
#define MAX_MISSED_READINGS 20 // Keep up to 20 readings in memory if connection to the api failed

/** Access point settings **/
#define ACCESS_POINT_SSID       "bgeigie%d" // With device id
#define SERVER_WIFI_PORT        80
#define ACCESS_POINT_IP         {192, 168, 5, 1}
#define ACCESS_POINT_NMASK      {255, 255, 255, 0}

/** Default ESP configurations **/
#define D_DEVICE_ID             0
#define D_ACCESS_POINT_PASSWORD "safecast"
#define D_WIFI_SSID             "your wifi ssid"
#define D_WIFI_PASSWORD         "yourwifipassword"
#define D_APIKEY                ""
#define D_USE_DEV_SERVER        true
#define D_LED_COLOR_BLIND       false
#define D_LED_COLOR_INTENSITY   30
#define D_SAVED_STATE           0


#endif