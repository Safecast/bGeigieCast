#ifndef BGEIGIE_POINTCAST_EVENT_H
#define BGEIGIE_POINTCAST_EVENT_H

typedef enum {
  e_undefined = -1,

  // Controller events
  e_button_pressed,
  e_button_long_pressed,
  e_controller_initialized,
  e_post_init_time_passed,
  e_server_initialized,

  e_api_report_success,
  e_api_report_failed,


  // Reporter events
  e_reading_expected,
  e_reading_received,
  e_reading_reported,

  e_bluetooth_initialized,
  e_reading_reported_bt,
  e_wifi_connected,
  e_api_available,
  e_reading_reported_api,
  e_wifi_connection_error,
  e_api_connection_error,
  e_api_post_failed,

} Event_enum;

#endif //BGEIGIE_POINTCAST_EVENT_H
