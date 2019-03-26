#include <string.h>
#include <stdio.h>
#include <HardwareSerial.h>

#include <dms_dd.h>

#include "reading.h"
#include "reading_parser/nsscanf.h"

Reading::Reading() :
    _reading_str(""),
    _validity(e_unparsed),
    _average_of(0),
    _device_id(0),
    _iso_timestr(""),
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
}

Reading::Reading(const char* reading_str) :
    _reading_str(""),
    _validity(e_unparsed),
    _average_of(1),
    _device_id(0),
    _iso_timestr(""),
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
  parse_values();
}

Reading::Reading(const Reading& copy) :
    _reading_str(""),
    _validity(copy._validity),
    _average_of(copy._average_of),
    _device_id(copy._device_id),
    _iso_timestr(""),
    _cpm(copy._cpm),
    _cpb(copy._cpb),
    _total_count(copy._total_count),
    _geiger_status(copy._geiger_status),
    _latitude(copy._latitude),
    _longitude(copy._longitude),
    _altitude(copy._altitude),
    _gps_status(copy._gps_status),
    _sat_count(copy._sat_count),
    _precision(copy._precision),
    _checksum(copy._checksum) {
  strcpy(_reading_str, copy._reading_str);
  strcpy(_iso_timestr, copy._iso_timestr);
}

Reading& Reading::operator+=(const Reading& o) {
  if(o._validity == e_unparsed || o._validity == e_invalid_string) {
    return *this;
  }
  if(_average_of == 0) {
    strcpy(_reading_str, o._reading_str);
    _validity = o._validity;
    _device_id = o._device_id;
    strcpy(_iso_timestr, o._iso_timestr);
    _cpm = o._cpm;
    _cpb = o._cpb;
    _total_count = o._total_count;
    _geiger_status = o._geiger_status;
    _latitude = o._latitude;
    _longitude = o._longitude;
    _altitude = o._altitude;
    _gps_status = o._gps_status;
    _sat_count = o._sat_count;
    _precision = o._precision;
    _checksum = o._checksum;
  } else {
    // Use latest datetime and total count
    strcpy(_iso_timestr, o._iso_timestr);
    _total_count = o._total_count;

    // If either is valid, its valid (sensor and gps)
    _geiger_status = _geiger_status == 'V' ? o._geiger_status : _geiger_status;
    _gps_status = _gps_status == 'V' ? o._gps_status : _gps_status;

    // Take averages of all other data
    _cpm = ((_cpm * _average_of) + (o._cpm * o._average_of)) / (_average_of + o._average_of);
    _cpb = ((_cpb * _average_of) + (o._cpb * o._average_of)) / (_average_of + o._average_of);
    _latitude = ((_latitude * _average_of) + (o._latitude * o._average_of)) / (_average_of + o._average_of);
    _longitude = ((_longitude * _average_of) + (o._longitude * o._average_of)) / (_average_of + o._average_of);
    _altitude = ((_altitude * _average_of) + (o._altitude * o._average_of)) / (_average_of + o._average_of);
    _sat_count = ((_sat_count * _average_of) + (o._sat_count * o._average_of)) / (_average_of + o._average_of);
    _precision = ((_precision * _average_of) + (o._precision * o._average_of)) / (_average_of + o._average_of);

    // TODO: update checksum? only if required in API
//    _checksum = black magic

    // Update count of readings merged with this
    _average_of += o._average_of;

    // Maybe do something smarter with the validity...?
    _validity = o._validity;
  }
  return *this;
}

bool Reading::as_json(char* out) {
  if(_validity != ReadingValidity::e_valid) {
    return false;
  }

  uint32_t device_id = _device_id + 60000; // Stationary bGeigie sensors in 60k-70k range
  sprintf(
      out,
      "{\"captured_at\":\"%s\","
      "\"device_id\":%d,"
      "\"value\":%d,"
      "\"unit\":\"cpm\","
      "\"longitude\":%.4f,"
      "\"latitude\":%.4f}\n",
      _iso_timestr,
      device_id,
      _cpm,
      _longitude,
      _latitude
  );
  return true;
}

void Reading::reset() {
  _average_of = 0;
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

  if(parse_result != 15) { // 15 values to be parsed
    _validity = ReadingValidity::e_invalid_string;
  } else if(_gps_status != 'A') {
    _validity = ReadingValidity::e_invalid_gps;
  } else if(_geiger_status != 'A') {
    _validity = ReadingValidity::e_invalid_sensor;
  } else {
    _validity = ReadingValidity::e_valid;
  }


  if(NorS == 'S') { _latitude *= -1; }
  if(WorE == 'W') { _longitude *= -1; }



  _latitude = dms_to_dd(_latitude);
  _longitude = dms_to_dd(_longitude);
  _latitude = dms_to_dd(_latitude);
  _altitude /= 100;
}

bool Reading::correctly_parsed() const {
  return _validity != e_unparsed && _validity != e_invalid_string && _device_id > 0;
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
