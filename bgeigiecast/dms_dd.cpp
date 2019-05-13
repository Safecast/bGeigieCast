#include "dms_dd.h"


double dms_to_dd(double dms) {
  double degree = static_cast<int>(dms / 100);
  double minutes = static_cast<int>(dms - (degree * 100));
  double seconds = static_cast<int>((dms - (degree * 100) - minutes) * 100);
  return degree + minutes/60 + seconds/3600;
}

double dm_to_dd(double dm) {
  double degree = static_cast<int>(dm / 100);
  double minutes = dm - (degree * 100);
  return degree + minutes/60;
}

