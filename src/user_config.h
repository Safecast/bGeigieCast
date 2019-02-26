#ifndef USER_CONFIG_H
#define USER_CONFIG_H


// System config
#define ENABLE_DEBUG 1
#define SERIAL_BAUD 115200

// Hardware pins settings
#define RGB_LED_PIN 16
#define MODE_BUTTON_PIN 17

// API settings
#define API_PING_TEST_ADDRESS "dev.safecast.org"

// Access point settings
#define SERVER_WIFI_PORT 80
#define SERVER_MAX_CLIENTS 4
#define ACCESS_POINT_IP     192, 168, 5, 1
#define ACCESS_POINT_NMASK  255, 255, 255, 0

// Default settings
#define D_ACCESS_POINT_SSID "bGeigie-ESP32"
#define D_ACCESS_POINT_PASSWORD "safecast"
#define D_WIFI_SSID "Loftwork COOOP3 Free"
#define D_WIFI_PASSWORD ""
#define D_APIKEY "YE_KEY"
#define D_USE_DEV_SERVER true

#endif