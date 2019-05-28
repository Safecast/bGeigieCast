#ifndef BGEIGIECAST_HTTP_PAGES_H
#define BGEIGIECAST_HTTP_PAGES_H

#define PURE_CSS_SIZE 3929
#define FAVICON_SIZE 696

class HttpPages {
 public:
  HttpPages() = delete;

  /**
   * Render the home page
   * @param device_id : To display the device id on the page
   * @return complete page rendered
   */
  static const char* get_home_page(
      uint32_t device_id
  );

  /**
   * Render the update firmware page
   * @param device_id : To display the device id on the page
   * @return complete page rendered
   */
  static const char* get_update_page(
      uint32_t device_id
  );

  /**
   * Render the configuration page for device settings
   * @param display_success 
   * @param device_id 
   * @param led_intensity 
   * @param colorblind 
   * @return complete page rendered
   */
  static const char* get_config_device_page(
      bool display_success,
      uint32_t device_id,
      uint8_t led_intensity,
      bool colorblind
  );

  /**
   * Render the configuration page for connection settings
   * @param display_success 
   * @param device_id 
   * @param device_password 
   * @param wifi_ssid 
   * @param wifi_password 
   * @param api_key 
   * @param use_dev 
   * @param sped_up 
   * @return complete page rendered
   */
  static const char* get_config_connection_page(
      bool display_success,
      uint32_t device_id,
      const char* device_password,
      const char* wifi_ssid,
      const char* wifi_password,
      const char* api_key,
      bool use_dev,
      bool sped_up
  );

  /**
   * Render the configuration page for location settings
   * @param display_success
   * @param device_id
   * @param use_home_location
   * @param home_latitude
   * @param home_longitude
   * @param last_latitude
   * @param last_longitude
   * @return complete page rendered
   */
  static const char* get_config_location_page(
      bool display_success,
      uint32_t device_id,
      bool use_home_location,
      double home_latitude,
      double home_longitude,
      double last_latitude,
      double last_longitude
  );

  static const uint8_t pure_css[PURE_CSS_SIZE];
  static const uint8_t favicon[FAVICON_SIZE];

 private:

  static const char* render_full_page(uint32_t device_id, const char* page_name, const char* content);
  static char transmission_buffer[4096];
  static char content_buffer[2048];

};

#endif //BGEIGIECAST_HTTP_PAGES_H
