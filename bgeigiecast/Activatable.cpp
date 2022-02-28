//
// Created by Jelle Bouwhuis on 12/27/19.
//

#include <Activatable.hpp>

void Activatable::set_active(bool _activate, _Status& status) {
  if(status.active_state == _Status::e_state_inactive && _activate) {
    status.active_state = activate(false) ? _Status::e_state_active : _Status::e_state_activating_failed;
  } else if(status.active_state != _Status::e_state_inactive && !_activate) {
    deactivate();
    status.active_state = _Status::e_state_inactive;
  }
}

bool Activatable::activate(bool retry) {
  return true;
}

void Activatable::deactivate() {}
