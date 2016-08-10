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


/**
 DataBuffer::operator ==
 * @brief checks if attributes and data of (*this) and other_ are equal
 * @param other_ DataBuffer to compare with
 * @return returns true if all attributes and all data are equal, otherwise false
 */
bool DataBuffer::operator==(DataBuffer &other_) {
   bool result = true;

   // make ctime compare-able
   time_t startDateTimeThis  = mktime(&((*this).startDateTime));
   time_t startDateTimeOther = mktime(&( other_.startDateTime));
   time_t   endDateTimeThis  = mktime(&((*this).endDateTime));
   time_t   endDateTimeOther = mktime(&( other_.endDateTime));

   // check attributes
   if ( ( (*this).dataSource    != other_.dataSource   ) ||
        ( (*this).useDataSource != other_.useDataSource) ||
        ( (*this).useDateTimes  != other_.useDateTimes ) ||
        (     startDateTimeThis != startDateTimeOther  ) ||
        (       endDateTimeThis !=   endDateTimeOther  ) ){
       result = false;
   }

   // check data
   typedef std::map<string, double>::iterator it_type;
   for(it_type iterator = (*this).data.begin(); iterator != (*this).data.end(); iterator++) {
       string name  = iterator->first;
       double value = iterator->second;
       if (value != other_.data[name]) {
           result = false;
           break;
       }
   }


   return result;

}


/**
 * @brief DataBuffer::operator ==
 * @param time1_
 * @param time2
 * @return
 *
bool struct tm::operator==(tm time1_, tm time2) {
    bool result = true;
    if ( ( time1_.tm_year != time2_.tm_year) ||
         ( time1_.tm_mon  != time2_.tm_mon ) ||
         ( time1_.tm_mday != time2_.tm_mday) ||
         ( time1_.tm_hour != time2_.tm_hour) ||
         ( time1_.tm_min  != time2_.tm_min ) ||
         ( time1_.tm_sec  != time2_.tm_sec ) ){
        result = false;
    }
    return result;
}
*/
