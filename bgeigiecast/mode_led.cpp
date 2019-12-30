
#include "mode_led.h"
#include "user_config.h"
#include "debugger.h"
#include "identifiers.h"
#include "sm_c_state.h"
#include "bluetooth_reporter.h"
#include "api_connector.h"

// Set this to true if we use anode LED
#define RGB_STATE_LED_REVERSED true

ModeLED::ModeLED(LocalStorage& config) :
    RGBLed(RGB_LED_PIN_R, RGB_LED_PIN_G, RGB_LED_PIN_B, RGB_STATE_LED_REVERSED),
    Supervisor(),
    _config(config),
    color(ModeColor::mode_color_off),
    frequency(0),
    percentage_on(0),
    _colorTypes{
        // Normal            Colorblind
        // R    G    B   ,   R    G    B
        {{000, 000, 000}, {000, 000, 000}}, // off
        {{063, 127, 063}, {063, 127, 063}}, // init
        {{127, 000, 127}, {127, 000, 127}}, // config
        {{000, 100, 255}, {000, 100, 255}}, // mobile
        {{000, 255, 000}, {000, 255, 000}}, // fixed_connected
        {{127, 127, 000}, {127, 127, 000}}, // fixed_soft_error
        {{255, 000, 000}, {255, 000, 000}}, // fixed_hard_error
    } {
}

void ModeLED::set_values(ModeLED::ModeColor _color, double _frequency, uint8_t _percentage_on) {
  frequency = _frequency;
  percentage_on = _percentage_on;
  color = _color;
  if(frequency == 0)
    set_color(color);
}

void ModeLED::set_color(ModeLED::ModeColor _color) {
  static ModeColor _last = mode_color_off;
  if(_color != _last) {
    _last = _color;
    DEBUG_PRINT("Changed LED to ");
    DEBUG_PRINTLN(_color);
    set(_config.is_led_color_blind() ? _colorTypes[_color].color_blind : _colorTypes[_color].normal);
  }
}

void ModeLED::loop() {
  if(frequency > 0) {
    // Blink LED
    double blink_millis = 1000 / frequency;
    auto cycle_now = millis() % static_cast<uint32_t>(blink_millis);
    auto threshold = static_cast<uint32_t>(blink_millis * (percentage_on / 100.0));
    if(cycle_now < threshold) {
      set_color(color);
    } else if(cycle_now > threshold) {
      set_color(ModeLED::mode_color_off);
    }
  }
}

uint8_t ModeLED::get_intensity() const {
  return _config.get_led_color_intensity();
}

bool ModeLED::activate() {
  init();
  return true;
}

void ModeLED::handle_report(const Report& report) {
  auto& worker_stats = report.get_worker_stats();
  auto& handler_stats = report.get_handler_stats();

  // Switch controller system state
  switch(handler_stats.at(k_handler_controller_handler).status) {
    case ControllerState::k_state_InitializeState:
    case ControllerState::k_state_InitReadingState:
      /// Initializing, blink every 1 second
      set_values(mode_color_init, 1, 10);
      break;
    case ControllerState::k_state_PostInitializeState:
      /// Post initializing, blink every 0.8 second ( this lasts for 3 seconds total )
      set_values(mode_color_init, 1.5, 15);
      break;
    case ControllerState::k_state_ConfigurationModeState:
      switch(worker_stats.at(k_worker_configuration_server).active_state) {
        case WorkerStatus::e_state_active:
          /// Configuration mode - up and running. no blink
          set_values(mode_color_config);
          break;
        case WorkerStatus::e_state_activating_failed:
        default:
          /// Configuration mode - connecting to wifi / settings up access point. blink
          set_values(mode_color_config, 1, 50);
          break;
      }
      break;
    case ControllerState::k_state_MobileModeState:
      switch(handler_stats.at(k_handler_bluetooth_reporter).status) {
        case BluetoothReporter::e_handler_clients_available:
          /// Mobile mode - Clients connected
          set_values(mode_color_mobile);
          break;
        case BluetoothReporter::e_handler_idle:
        case BluetoothReporter::e_handler_no_clients:
        default:
          /// Mobile mode - No clients connected
          set_values(mode_color_mobile, 0.33, 5);
          break;
      }
      break;
    case ControllerState::k_state_FixedModeState:
      if(handler_stats.at(k_handler_api_reporter).active_state == HandlerStatus::e_state_activating_failed) {
        /// Fixed mode - Connecting to wifi, blink connected
        set_values(mode_color_fixed_connected, 1, 25);
        break;
      }
      switch(handler_stats.at(k_handler_api_reporter).status) {
        case ApiReporter::e_api_reporter_error_not_connected:
          /// Fixed mode - Lost connection to wifi, blink connected again
          set_values(mode_color_fixed_connected, 1, 25);
          break;
        case ApiReporter::e_api_reporter_error_invalid_reading:
          /// Fixed mode - Invalid reading (no good gps) TODO: add additional check for gps
          set_values(mode_color_fixed_hard_error, 0.33, 15);
          break;
        case ApiReporter::e_api_reporter_error_remote_not_available:
        case ApiReporter::e_api_reporter_error_server_rejected_post:
          /// Fixed mode - Remote is not available
          set_values(mode_color_fixed_soft_error);
          break;
        case ApiReporter::e_api_reporter_send_success:
        default:
          /// Fixed mode - All good and connected
          set_values(mode_color_fixed_connected);
          break;
      }
      break;
    case ControllerState::k_state_ResetState:
      /// Reset - Display red because its least used TODO: custom color
      set_values(mode_color_fixed_hard_error);
      break;
    default:
      break;
  }
}
