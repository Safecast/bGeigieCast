#include <string.h>
#include <stdio.h>
#include <HardwareSerial.h>

#include "reading.h"
#include "reading_parser/nsscanf.h"

Reading::Reading(const char* reading_str) :
    _reading_str(),
    _validity(e_unparsed),
    _device_id(0),
    _iso_timestr(),
    _cpm(0),
    _cpb(0),
    _total_count(0),
    _geiger_status(),
    _latitude(),
    _longitude(),
    _altitude(),
    _gps_status(),
    _sat_count(),
    _precision(0),
    _checksum(0) {
  strcpy(_reading_str, reading_str);
}

void Reading::parse_values() {
  char NorS;
  char WorE;

  int parse_result = nsscanf(
      _reading_str,
      "$BNRDD,%04d,%[^,],%d,%d,%d,%c,%f,%c,%f,%c,%f,%c,%d,%f*%x",
      &_device_id,
      _iso_timestr,
      &_cpm,
      &_cpb,
      &_total_count,
      &_geiger_status,
      &_latitude,
      &NorS,
      &_longitude,
      &WorE,
      &_altitude,
      &_gps_status,
      &_sat_count,
      &_precision,
      &_checksum
  );

  if(parse_result != 15) { // 14 values to be parsed
    _validity = ReadingValidity::e_invalid_string;
  }
  else if(_gps_status != 'A') {
    _validity = ReadingValidity::e_invalid_gps;
  }
  else if(_geiger_status != 'A') {
    _validity = ReadingValidity::e_invalid_sensor;
  }
  else {
    if(NorS == 'S') { _latitude *= -1; }
    if(WorE == 'W') { _longitude *= -1; }

    _validity = ReadingValidity::e_valid;
  }
}

bool Reading::as_json(char* out, bool stationary) {
  if(_validity != ReadingValidity::e_valid) {
    return false;
  }

  uint32_t device_id = stationary && _device_id < 10000 ? _device_id + 60000 : _device_id;
  sprintf(
      out,
      "{\"captured_at\":\"%s\","
      "\"device_id\":\"%d\","
      "\"value\":\"%d\","
      "\"unit\":\"cpm\","
      "\"longitude\":\"%.4f\","
      "\"latitude\":\"%.4f\"}\n",
      _iso_timestr,
      device_id,
      _cpm,
      _longitude,
      _latitude
  );
  return true;
}

const char* Reading::get_reading_str() const {
  return _reading_str;
}
ReadingValidity Reading::get_validity() const {
  return _validity;
}
uint16_t Reading::get_device_id() const {
  return _device_id;
}
const char* Reading::get_iso_timestr() const {
  return _iso_timestr;
}
uint16_t Reading::get_cpm() const {
  return _cpm;
}
uint16_t Reading::get_cpb() const {
  return _cpb;
}
uint16_t Reading::get_total_count() const {
  return _total_count;
}
char Reading::get_geiger_status() const {
  return _geiger_status;
}
float Reading::get_latitude() const {
  return _latitude;
}
float Reading::get_longitude() const {
  return _longitude;
}
float Reading::get_altitude() const {
  return _altitude;
}
char Reading::get_gps_status() const {
  return _gps_status;
}
int Reading::get_sat_count() const {
  return _sat_count;
}
float Reading::get_precision() const {
  return _precision;
}
uint16_t Reading::get_checksum() const {
  return _checksum;
}
