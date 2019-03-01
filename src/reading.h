#ifndef BGEIGIE_POINTCAST_READING_H
#define BGEIGIE_POINTCAST_READING_H

#include <stdint.h>

typedef enum {
  e_unparsed,
  e_valid,
  e_invalid_string,
  e_invalid_sensor,
  e_invalid_gps,
} ReadingValidity;

class Reading {
 public:
  explicit Reading(const char* reading_str);
  virtual ~Reading() = default;

  /**
   * Parse values from the reading_str
   */
  void parse_values();

  /**
   * Get this reading as a json object in string
   * @param out: output param
   * @param stationary: if the device is in stationary mode, it will add 60000 to the device id
   * @return: succes / not
   */
  bool as_json(char* out, bool stationary);

  const char* get_reading_str() const;
  ReadingValidity get_validity() const;
  uint16_t get_device_id() const;
  const char* get_iso_timestr() const;
  uint16_t get_cpm() const;
  uint16_t get_cpb() const;
  uint16_t get_total_count() const;
  char get_geiger_status() const;
  float get_latitude() const;
  float get_longitude() const;
  float get_altitude() const;
  char get_gps_status() const;
  int get_sat_count() const;
  float get_precision() const;
  uint16_t get_checksum() const;
 protected:
  char _reading_str[100];
  ReadingValidity _validity;

  // Reading content
  uint16_t _device_id;
  char _iso_timestr[30];
  uint16_t _cpm;
  uint16_t _cpb;
  uint16_t _total_count;
  char _geiger_status;
  float _latitude;
  float _longitude;
  float _altitude;
  char _gps_status;
  int _sat_count;
  float _precision;
  uint16_t _checksum;

};

#endif //BGEIGIE_POINTCAST_READING_H
