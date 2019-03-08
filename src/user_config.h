#ifndef USER_CONFIG_H
#define USER_CONFIG_H


// System config
#define ENABLE_DEBUG 1
#define SERIAL_BAUD 115200
#define BGEIGIE_CONNECTION_BAUD 9600

// Hardware pins settings
#define RGB_LED_PIN_R A18
#define RGB_LED_PIN_G A4
#define RGB_LED_PIN_B A5

#define MODE_BUTTON_PIN 22

// API connector settings
#define API_HOST "tt.safecast.org"
#define API_ENDPOINT "http://tt.safecast.org/measurements.json"
#define API_SEND_FREQUENCY_MINUTES 5
// max 3 with sending every 5 minutes would mean saving the last 15 minutes if connection failed
#define MAX_MISSED_READINGS 3

// Access point settings
#define SERVER_WIFI_PORT    80
#define SERVER_MAX_CLIENTS  4
#define ACCESS_POINT_IP     {192, 168, 5, 1}
#define ACCESS_POINT_NMASK  {255, 255, 255, 0}

// Default ESP user configurations
#define D_ACCESS_POINT_SSID     "bGeigie-ESP32"
#define D_ACCESS_POINT_PASSWORD "safecast"
#define D_WIFI_SSID             "Loftwork COOOP3 Free"
#define D_WIFI_PASSWORD         ""
#define D_APIKEY                ""
#define D_USE_DEV_SERVER        true

#endif