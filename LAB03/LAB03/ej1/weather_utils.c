#include <stdio.h>
#include <stdlib.h>
#include "weather_utils.h"

/* Función que da el mínimo de temperatura a nivel histórico*/
int minTempHistorica (WeatherTable a) {
    int minT = 100;
    for (unsigned int year = 0u; year < YEARS; ++year) {
        for (month_t month = january; month <= december; ++month) {
            for (unsigned int day = 0u; day < DAYS; ++day) {
                if (a[year][month][day]._min_temp < minT) {
                    minT =  a[year][month][day]._min_temp;
                }
            }
        }
    }
    return minT;
}

/* Función que da el máximo de temperatura por año*/
void maxTempAnual (WeatherTable a,int maxTemp[YEARS]) {
    for (unsigned int year = 0u; year < YEARS; ++year) {
        int maxT = -100;
        for (month_t month = january; month <= december; ++month) {
            for (unsigned int day = 0u; day < DAYS; ++day) {
                if (a[year][month][day]._max_temp > maxT) {
                    maxT = a[year][month][day]._max_temp;
                }
            }
        }
        maxTemp[year] = maxT;
    }
}

/* Función que devuelve el mes con máxima precipitación de cada año*/
void maxMesPrecAnual (WeatherTable a, month_t maxPrecAnual[YEARS]) {
      for (unsigned int year = 0u; year < YEARS; ++year) {
        month_t mesMaxPrec;
        unsigned int maxPrec = 0;

        for (month_t month = january; month <= december; ++month) {
            unsigned int Prec = 0;
            
            for (unsigned int day = 0u; day < DAYS; ++day) {
                Prec = Prec + a[year][month][day]._rainfall;
            }

            if (Prec > maxPrec) {
                    maxPrec = Prec;
                    mesMaxPrec = month;
                }
        }
        maxPrecAnual[year] = mesMaxPrec;
    }
}

const char* getMonthName(month_t month) {
    switch (month)
    {
    case january: return "january";
    case february: return "february";
    case march: return "march";
    case april: return "april";
    case may: return "may";
    case june: return "june";
    case july: return "july";
    case august: return "august";
    case september: return "september";
    case october: return "october";
    case november: return "november";
    case december: return "december"; 
    }
    return "";
}
