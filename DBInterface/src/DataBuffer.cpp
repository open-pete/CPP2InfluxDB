/**
 * DataBuffer.cpp
 * Purpose: implements struct DataBuffer and DataBufferProperties
 *
 * @author Wall.Of.Death
 * @version 1.0 20160704
 */

#include "../include/DataBuffer.h"

/**
 * operator <<
 * @brief operator << allows it two shift out DataBuffer-objects
 *                    into a std::ostream
 * @param oStream_    ostream-object before writing dataBuffer_ into stream
 * @param dataBuffer_ DataBuffer which is to write into the stream
 * @return            ostream-object after writing dataBuffer_ into stream
 */
ostream& operator<<(ostream& oStream_,DataBuffer dataBuffer_) {
    // iterate through all <string,double>-pairs
    for (auto& x : dataBuffer_.data) {
        // output : [String ==> Double]
        oStream_ << "[" << x.first << " ==> " << x.second << "]" << endl;
    }
    return oStream_;
}
