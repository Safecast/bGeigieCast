#ifndef BGEIGIE_POINTCAST_EVENT_H
#define BGEIGIE_POINTCAST_EVENT_H

typedef enum {
  e_undefined = -1,
  e_button_pressed,
  e_button_long_pressed,
  e_controller_initialized,
  e_post_init_time_passed,
  e_server_initialized,
  e_start_stationary,
  e_connected,
  e_API_available,
  e_connection_lost,
  e_connection_failed,
} Event_enum;

#endif //BGEIGIE_POINTCAST_EVENT_H
