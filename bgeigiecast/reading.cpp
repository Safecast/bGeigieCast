#include <string.h>
#include <stdio.h>
#include <math.h>

#include "reading.h"
#include "debugger.h"

#define D2R (PI / 180.0)
#define EXPECTED_PARSE_RESULT_COUNT 15
#define VALID_BGEIGIE_ID(id) (id >= 1000 && id < 10000)
#define HOME_LOCATION_PRECISION_KM 0.2


/**
 * Convert degree minutes to decimal degree
 * @param dm
 * @return
 */
double dm_to_dd(double dm) {
  double degree = static_cast<int>(dm / 100);
  double minutes = dm - (degree * 100);
  return degree + minutes / 60;
}

/**
 * Calculate distance using haversine formula
 * @param lat1
 * @param long1
 * @param lat2
 * @param long2
 * @return distance in km
 */
double haversine_km(double lat1, double long1, double lat2, double long2) {
  double dlong = (long2 - long1) * D2R;
  double dlat = (lat2 - lat1) * D2R;
  double a = pow(sin(dlat / 2.0), 2) + cos(lat1 * D2R) * cos(lat2 * D2R) * pow(sin(dlong / 2.0), 2);
  double c = 2 * atan2(sqrt(a), sqrt(1 - a));
  return 6367 * c;
}

Reading::Reading() :
    _reading_str(""),
    _status(0x0),
    _device_id(0),
    _iso_timestamp(""),
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
    _device_id(0),
    _iso_timestamp(""),
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
    _device_id(copy._device_id),
    _iso_timestamp(""),
    _cpm(copy._cpm),
    _cpb(copy._cpb),
    _total_count(copy._total_count),
    _latitude(copy._latitude),
    _longitude(copy._longitude),
    _altitude(copy._altitude),
    _sat_count(copy._sat_count),
    _precision(copy._precision) {
  strcpy(_reading_str, copy._reading_str);
  strcpy(_iso_timestamp, copy._iso_timestamp);
}

Reading& Reading::operator=(const char* reading_str) {
  reset();
  strcpy(_reading_str, reading_str);
  parse_values();
  return *this;
}

Reading& Reading::operator=(const Reading& other) {
  if(&other != this) {
    _status = other._status;
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
    strcpy(_iso_timestamp, other._iso_timestamp);
  }
  return *this;
}

void Reading::reset() {
  _status = 0;
}

bool Reading::near_location(double home_lat, double home_long) const {
  return haversine_km(_latitude, _longitude, home_lat, home_long) < HOME_LOCATION_PRECISION_KM;
}

void Reading::parse_values() {
  reset();
  double lat_dm = 0, long_dm = 0;
  char n_or_s, w_or_e, sensor_status, gps_status;
  uint16_t checksum;

  int parse_result = sscanf(
      _reading_str,
      "$BNRDD,%hu,%[^,],%hu,%hu,%hu,%c,%lf,%c,%lf,%c,%lf,%c,%d,%f*%hx",
      &_device_id,
      _iso_timestamp,
      &_cpm,
      &_cpb,
      &_total_count,
      &sensor_status,
      &lat_dm,
      &n_or_s,
      &long_dm,
      &w_or_e,
      &_altitude,
      &gps_status,
      &_sat_count,
      &_precision,
      &checksum
  );

  if(parse_result == EXPECTED_PARSE_RESULT_COUNT && VALID_BGEIGIE_ID(_device_id)) { // 15 values to be parsed
    _status |= k_reading_parsed;

    uint16_t c = 0;
    char* str = _reading_str + 1;  // Excluding the dollar sign
    while(*str && *str != '*')
      c ^= *str++;
    if(checksum == c) {
      _status |= k_reading_valid;
    }

    uint16_t year;
    char date_rest[25];

    sscanf(_iso_timestamp, "%hu-%s", &year, date_rest);

    if(year < 2021) {
      // Year in the past, set reading invalid
      _status &= _status ^ k_reading_valid;
    }

    if(sensor_status == 'A') {
      _status |= k_reading_sensor_ok;
    }

    if(gps_status == 'A') {
      _status |= k_reading_gps_ok;

      _latitude = dm_to_dd(lat_dm);
      _longitude = dm_to_dd(long_dm);

      if(n_or_s == 'S') { _latitude *= -1; }
      if(w_or_e == 'W') { _longitude *= -1; }
    }
  }
}

bool Reading::valid_reading() const {
  return _status & k_reading_sensor_ok && _status & k_reading_gps_ok;
}

const char* Reading::get_reading_str() const {
  return _reading_str;
}

uint8_t Reading::get_status() const {
  return _status;
}

uint16_t Reading::get_device_id() const {
  return _device_id;
}

uint32_t Reading::get_fixed_device_id() const {
  return 60000 + _device_id;
}

const char* Reading::get_iso_timestamp() const {
  return _iso_timestamp;
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

