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


} Event_enum;

#endif //BGEIGIE_POINTCAST_EVENT_H
