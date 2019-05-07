#include "dms_dd.h"


float dms_to_dd(float dms) {
  float degree = static_cast<int>(dms / 100);
  float minutes = static_cast<int>(dms - (degree * 100));
  float seconds = static_cast<int>((dms - (degree * 100) - minutes) * 100);
  return degree + minutes/60 + seconds/3600;
}


float dm_to_dd(float dms) {
  float degree = static_cast<int>(dms / 100);
  float minutes = static_cast<int>(dms - (degree * 100));
  return degree + minutes/60;
}

