/**
 * DataBuffer.h
 * Purpose: defines constants, enums and structs
 *
 * @author Wall.Of.Death
 * @version 1.0 20160704
 */

#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include <float.h>

using namespace std;

// constants
const string URL_OF_DATABASE = "http://localhost:8086";
const string NAME_OF_DATBASE = "WeatherData2";
const string PATH_OF_LOGFILE = "LogFile.txt";
const double INFLUXDB_MAX    =  1.79769e+308;
const double INFLUXDB_MIN    = -1.79769e+308;

#endif // CONFIG_H
