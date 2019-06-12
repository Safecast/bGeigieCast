#include <string.h>
#include <stdio.h>
#include <HardwareSerial.h>

#include "dms_dd.h"

#include "reading.h"
#include "debugger.h"

#define EXPECTED_PARSE_RESULT_COUNT 15
#define VALID_BGEIGIE_ID(id) (id >= 1000 && id < 10000)

#define LONG_LAT_PRECISION 0.001

Reading::Reading() :
    _reading_str(""),
    _status(0x0),
    _average_of(0),
    _device_id(0),
    _iso_timestr(""),
    _cpm(0),
    _cpb(0),
    _total_count(0),
    _latitude(),
    _longitude(),
    _altitude(),
    _sat_count(),
    _precision(0) {
}

Reading::Reading(const char* reading_str) :
    _reading_str(""),
    _status(0x0),
    _average_of(1),
    _device_id(0),
    _iso_timestr(""),
    _cpm(0),
    _cpb(0),
    _total_count(0),
    _latitude(),
    _longitude(),
    _altitude(),
    _sat_count(),
    _precision(0) {
  strcpy(_reading_str, reading_str);
  parse_values();
}

Reading::Reading(const Reading& copy) :
    _reading_str(""),
    _status(copy._status),
    _average_of(copy._average_of),
    _device_id(copy._device_id),
    _iso_timestr(""),
    _cpm(copy._cpm),
    _cpb(copy._cpb),
    _total_count(copy._total_count),
    _latitude(copy._latitude),
    _longitude(copy._longitude),
    _altitude(copy._altitude),
    _sat_count(copy._sat_count),
    _precision(copy._precision) {
  strcpy(_reading_str, copy._reading_str);
  strcpy(_iso_timestr, copy._iso_timestr);
}

Reading& Reading::operator=(const Reading& other) {
  if(&other != this) {
    _status = other._status;
    _average_of = other._average_of;
    _device_id = other._device_id;
    _cpm = other._cpm;
    _cpb = other._cpb;
    _total_count = other._total_count;
    _latitude = other._latitude;
    _longitude = other._longitude;
    _altitude = other._altitude;
    _sat_count = other._sat_count;
    _precision = other._precision;
    strcpy(_reading_str, other._reading_str);
    strcpy(_iso_timestr, other._iso_timestr);
  }
  return *this;
}

Reading& Reading::operator+=(const Reading& o) {
  if(!(o._status & k_reading_valid)) {
    // Do nothing with the other, not valid
    return *this;
  }
  if(_average_of == 0) {
    // Assign other to this
    return operator=(o);
  }
  // Else, merge other with this

  // Use latest datetime and total count
  strcpy(_iso_timestr, o._iso_timestr);
  _total_count = o._total_count;

  // Maybe do something smarter with the validity...?
  _status |= o._status & k_reading_valid;

  uint16_t o_cpm = o._cpm, o_cpb = o._cpb;

  if(!(_status & k_reading_sensor_ok) && o._status & k_reading_sensor_ok) {
    _status |= k_reading_sensor_ok;
    _cpm = o_cpm;
    _cpb = o_cpb;
  } else if(_status & k_reading_sensor_ok && !(o._status & k_reading_sensor_ok)) {
    o_cpm = _cpm;
    o_cpb = _cpb;
  }

  // Sensor data
  _cpm = ((_cpm * _average_of) + (o_cpm * o._average_of)) / (_average_of + o._average_of);
  _cpb = ((_cpb * _average_of) + (o_cpb * o._average_of)) / (_average_of + o._average_of);

  double o_lat = o._latitude, o_long = o._longitude, o_alt = o._altitude;

  if(!(_status & k_reading_gps_ok) && o._status & k_reading_gps_ok) {
    _status |= k_reading_gps_ok;
    _latitude = o_lat;
    _longitude = o_long;
    _altitude = o_alt;
  } else if(_status & k_reading_gps_ok && !(o._status & k_reading_gps_ok)) {
    o_lat = _latitude;
    o_long = _longitude;
    o_alt = _altitude;
  }

  // Location data
  _latitude = ((_latitude * _average_of) + (o_lat * o._average_of)) / (_average_of + o._average_of);
  _longitude = ((_longitude * _average_of) + (o_long * o._average_of)) / (_average_of + o._average_of);
  _altitude = ((_altitude * _average_of) + (o_alt * o._average_of)) / (_average_of + o._average_of);
  _sat_count = ((_sat_count * _average_of) + (o._sat_count * o._average_of)) / (_average_of + o._average_of);
  _precision = ((_precision * _average_of) + (o._precision * o._average_of)) / (_average_of + o._average_of);

  // Update count of readings merged with this
  _average_of += o._average_of;

  return *this;
}

bool Reading::as_json(char* out) {
  if(!valid_reading()) {
    return false;
  }

  sprintf(
      out,
      "{\"captured_at\":\"%s\","
      "\"device_id\":%d,"
      "\"value\":%d,"
      "\"unit\":\"cpm\","
      "\"longitude\":%.5f,"
      "\"latitude\":%.5f}\n",
      _iso_timestr,
      get_fixed_device_id(),
      _cpm,
      _longitude,
      _latitude
  );
  return true;
}

void Reading::reset() {
  _average_of = 0;
}

void Reading::apply_home_location(double home_lat, double home_long) {
  if(_latitude < home_lat + LONG_LAT_PRECISION && _latitude > home_lat - LONG_LAT_PRECISION
      && _longitude < home_long + LONG_LAT_PRECISION && _longitude > home_long - LONG_LAT_PRECISION) {
    DEBUG_PRINTF("Gps in home location, setting reading location to %.5f , %.5f\n", home_lat, home_long);
    _latitude = home_lat;
    _longitude = home_long;
  } else {
    DEBUG_PRINTLN("Gps not in home location");
    _status &= ~(k_reading_gps_ok);
  }
}

void Reading::parse_values() {
  double lat_dms = 0, long_dms = 0;
  char n_or_s, w_or_e, sensor_status, gps_status;
  int16_t checksum;

  int parse_result = sscanf(
      _reading_str,
      "$BNRDD,%hu,%[^,],%hu,%hu,%hu,%c,%lf,%c,%lf,%c,%lf,%c,%d,%f*%hx",
      &_device_id,
      _iso_timestr,
      &_cpm,
      &_cpb,
      &_total_count,
      &sensor_status,
      &lat_dms,
      &n_or_s,
      &long_dms,
      &w_or_e,
      &_altitude,
      &gps_status,
      &_sat_count,
      &_precision,
      &checksum
  );

  _status |= k_reading_parsed;

  if(parse_result == EXPECTED_PARSE_RESULT_COUNT && VALID_BGEIGIE_ID(_device_id)) { // 15 values to be parsed
    _status |= k_reading_valid;
    if(sensor_status == 'A') {
      _status |= k_reading_sensor_ok;
    }
    if(gps_status == 'A') {
      _status |= k_reading_gps_ok;

      _latitude = dm_to_dd(lat_dms);
      _longitude = dm_to_dd(long_dms);

      if(n_or_s == 'S') { _latitude *= -1; }
      if(w_or_e == 'W') { _longitude *= -1; }
    }

    // TODO Validate checksum?
    if(checksum > 0) {
      _status |= k_reading_checksum_ok;
    }
  }
}

bool Reading::valid_reading() const {
  return _status & k_reading_sensor_ok && _status & k_reading_gps_ok;
}

const char* Reading::get_reading_str() const {
  return _reading_str;
}
int8_t Reading::get_status() const {
  return _status;
}
uint16_t Reading::get_device_id() const {
  return _device_id;
}
uint32_t Reading::get_fixed_device_id() const {
  return 60000 + _device_id;
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
double Reading::get_latitude() const {
  return _latitude;
}
double Reading::get_longitude() const {
  return _longitude;
}
double Reading::get_altitude() const {
  return _altitude;
}
int Reading::get_sat_count() const {
  return _sat_count;
}
float Reading::get_precision() const {
  return _precision;
}
