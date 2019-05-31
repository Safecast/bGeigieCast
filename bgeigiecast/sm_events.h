#ifndef BGEIGIECAST_EVENTS_H
#define BGEIGIECAST_EVENTS_H

typedef enum {
  e_undefined = -1,

  // Controller events
  e_c_button_pressed,
  e_c_button_long_pressed,
  e_c_controller_initialized,
  e_c_reading_initialized,
  e_c_post_init_time_passed,
  e_c_server_initialized,

  e_c_report_success,
  e_c_report_failed,


  // Reporter events
  e_r_reading_expected,
  e_r_reading_received,
  e_r_reading_invalid,
  e_r_reading_reported,

  e_r_bluetooth_initialized,
  e_r_api_connector_initialized,
  e_r_reading_reported_bt,
  e_r_reading_reported_api_no_change,
  e_r_reading_reported_api_success,
  e_r_reading_reported_api_failed,


  // Api conn states
  e_a_report_reading,
  e_a_not_reporting,
  e_a_wifi_connected,
  e_a_endpoint_available,
  e_a_endpoint_unavailable,
  e_a_reading_posted,

  e_a_wifi_connection_error,
  e_a_api_post_failed,
  e_a_reading_saved,


} Event_enum;

#endif //BGEIGIECAST_EVENTS_H
