#ifndef _WEATHER_UTILS
#define _WEATHER_UTILS

#include "weather.h"
#include "array_helpers.h"

// Función que devuelve la temperatura mínima histórica
int minTempHistorica (WeatherTable a);

void maxTempAnual (WeatherTable a,int maxTemp[YEARS]);

void maxMesPrecAnual (WeatherTable a, month_t maxPrecAnual[YEARS]);

const char* getMonthName(month_t month);

#endif