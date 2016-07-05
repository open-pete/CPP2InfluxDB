/**
 * DataBuffer.h
 * Purpose: defines struct DataBuffer, DataBufferProperties and
 *          constant map possibleBufferValues
 *
 * @author Wall.Of.Death
 * @version 1.0 20160704
 */

#ifndef DATABUFFER_H
#define DATABUFFER_H

#include <map>
#include <string>
#include <iostream>

using namespace std;

/**
 * DataBuffer
 * @brief The DataBuffer is a data-exchange interface
 *
 * DataBuffer provides "data" (a map of string and double),
 * which can be used by two software modules to exchange data.
 */
struct DataBuffer{

    map<string,double> data;

    // operators
    friend ostream& operator<<(ostream& oStream_,DataBuffer dataBuffer_);
};

/**
 * DataBufferProperties
 * @brief The DataBufferProperties struct provides information
 *        about the content within a data buffer
 *
 * DataBufferProperties consists of the
 *  - two 'double' values minValue and maxValue
 *  -     'string' value  unitOfMeasure
 */
struct DataBufferProperties {
    double minValue;
    double maxValue;
    string unitOfMeasure;
};

/**
 * possibleDataBufferValues
 * @brief The constant map possibleDataBufferValues contains information
 *        about the range and the unit of measure of the values within
 *        the DataBuffer-struct. This is needen for the scaling of input
 *        and output values within the neural network
 *
 */
const map<string,DataBufferProperties> possibleDataBufferValues = {
   // name         | min | max | unit of measure
   //------------------------------------------
    {"Temperature",{    0,   10, "Degree Celsius"  }},
    {"Airpressure",{  800, 1200, "Hektopascal"     }}
};



#endif // DATABUFFER_H
