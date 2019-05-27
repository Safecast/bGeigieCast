#ifndef BGEIGIECAST_HTTP_PAGES_H
#define BGEIGIECAST_HTTP_PAGES_H

class HttpPages {
 public:
  HttpPages() = delete;

  static const char* get_home_page(uint32_t device_id);
  static const char* get_upload_page();
  static const char* get_config_device_page(
      bool display_success,
      uint32_t device_id,
      uint8_t led_intensity,
      bool colorblind
  );
  static const char* get_config_network_page(
      bool display_success,
      uint32_t device_id,
      const char* device_password,
      const char* wifi_ssid,
      const char* wifi_password,
      const char* api_key,
      bool use_dev,
      bool sped_up
  );
  static const char* get_config_location_page(
      bool display_success,
      uint32_t device_id,
      bool use_home_location,
      double home_latitude,
      double home_longtitude,
      double last_latitude,
      double last_longtitude
  );

  // Non-pages

 private:
  static char transmission_buffer[4096];

};

#endif //BGEIGIECAST_HTTP_PAGES_H
