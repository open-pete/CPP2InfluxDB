/**
 * DBInterface.cpp
 * Purpose: implements class DBInterface
 *
 * @author Wall.Of.Death
 * @version 1.0 20160704
 */


#include "../include/dbinterface.h"

/**
 * DBInterface::init
 * @brief creates a LogWriter-object
 */
void DBInterface::init() {
    createIfNotCreatedDataBase();

    // create LogWriter-object
    log = LogWriter("DBInterface", PATH_OF_LOGFILE);

    log << SLevel(INFO) << "Initialized DBInterface with url : " << URL_OF_DATABASE << "." << endl;

}

/**
 * DBInterface::writeToDataBase
 * @brief writeToDataBase writes content of dataBuffer_ to database
 * @param dataBuffer_ data which is written to database
 */
void DBInterface::writeToDataBase(DataBuffer& dataBuffer_) {
    if (readStatusOK()) {

        stringstream httpRequestUrl;

        httpRequestUrl << URL_OF_DATABASE << "/write?db=" << NAME_OF_DATBASE << "&precision=s";
        stringstream httpRequestPostFields;
        if (!dataBuffer_.useDataSource) {
            log << SLevel(ERROR) << "Aborted writing to database because there was either no DataSource specified";
            log << " or the useDataSource-flag was not set to true." << endl;
        } else {
            string dataSource = cleanString(dataBuffer_.dataSource);
            httpRequestPostFields << "point,DataSource=" << dataSource << " ";

            bool printComma = false;
            typedef std::map<string, double>::iterator it_type;
            for(it_type iterator = dataBuffer_.data.begin(); iterator != dataBuffer_.data.end(); iterator++) {
                if (printComma) {
                    httpRequestPostFields << ",";
                } else {
                    printComma = true;
                }
                string name = cleanString(iterator->first);
                double value = iterator->second;
                httpRequestPostFields << name << "=" << value;
            }
            // create datetime-string
            if (dataBuffer_.useDateTimes) {
                string startDateTime = cTimeToString(dataBuffer_.startDateTime,true);
                httpRequestPostFields << " " << startDateTime;
            }
            HTTPRequest req;
            req.post(httpRequestUrl.str(),httpRequestPostFields.str());
        }
    } else {
        log << SLevel(ERROR) << "Aborted writing to database because of status not OK" << endl;
    }
}

/**
 * DBInterface::readFromDataBase
 * @brief readFromDataBase reads the data which is requested by dataBuffer_ from database
 * @param dataBuffer_ requested data (is only filled with requested strings)
 * @return returns the requested dataBuffer_ which now contains requested data
 */
DataBuffer DBInterface::readFromDataBase(DataBuffer& dataBuffer_) {
    if (readStatusOK()) {
        DataBuffer result = dataBuffer_;

        stringstream httpRequestUrl;
        httpRequestUrl << URL_OF_DATABASE << "/query?pretty=true&db=" << NAME_OF_DATBASE << "&q=SELECT+"; // << "&precision=s";
        bool printComma = false;
        typedef std::map<string, double>::iterator it_type;
        for(it_type iterator = dataBuffer_.data.begin(); iterator != dataBuffer_.data.end(); iterator++) {
            if (printComma) {
                httpRequestUrl << ",";
            } else {
                printComma = true;
            }
            string name = cleanString(iterator->first);
            httpRequestUrl << name << "+";
        }
        if (!dataBuffer_.useDataSource) {
            log << SLevel(ERROR) << "Aborted reading from database because there was either no DataSource specified";
            log << " or the useDataSource-flag was not set to true." << endl;
            //todo return empty dataBuffer
        } else {
            string dataSource = cleanString(dataBuffer_.dataSource);
            httpRequestUrl << "FROM+point+where+DataSource+=+'" << dataSource << "'";
            if (dataBuffer_.useDateTimes) {
                string startDateTime = cTimeToString(dataBuffer_.startDateTime,false);
                string   endDateTime = cTimeToString(  dataBuffer_.endDateTime,false);
                httpRequestUrl << "+and+time+>=+'" << startDateTime << "'";
                httpRequestUrl << "+and+time+<=+'" <<   endDateTime << "'";
            }
            cout << "request : " << httpRequestUrl.str() << endl;
            HTTPRequest req;
            string answer = req.get(httpRequestUrl.str());
            cout << answer;

            return dataBuffer_;
        }
    } else {
        log << SLevel(ERROR) << "Aborted reading from database because of status not OK" << endl;
        DataBuffer emptyDataBuffer;
        return emptyDataBuffer;
    }
}

/**
 * DBInterface::writeStatusOK
 * @brief writes the boolean value statusOK_ to database
 * @param statusOK_ boolean value which is wirtten to the database
 */
void DBInterface::writeStatusOK(bool statusOK_) {
    // --- TODO -- dummy code ---
    cout << "write status to database : " << statusOK_ << endl;
    // --- TODO -- dummy code ---
}

/**
 * DBInterface::readStatusOK
 * @brief reads the boolean value statusOK from database and returns it.
 * @return returns the value of the boolean value statusOK
 */
bool DBInterface::readStatusOK() {
    // --- TODO -- dummy code ---
    cout << "read statusOK" << endl;
    return 1;//rand() % 1;
    // --- TODO -- dummy code ---
}

/**
 * DBInterface::getDBFailure
 * @brief returns value of private member variable dbFailure
 * @return value of private member variable dbFailure
 */
bool DBInterface::getDBFailure() {
    return dbFailure;
}

/**
 * DBInterface::createIfNotCreatedDataBase
 * @brief creates database defined by NAME_OF_DATBASE in config.h if not already created
 */
void DBInterface::createIfNotCreatedDataBase() {
    HTTPRequest request;
    request.post(URL_OF_DATABASE + "/query?q=create+database+"+NAME_OF_DATBASE+"&db=_internal","");
}

/**
 * DBInterface::cleanString
 * @brief removes every char that is not an alphabetic character, a number or '_'
 * @param stringToClean_ the string to clean
 * @return returns stringToClean_ without anything but character, numbers and '_'
 */
string DBInterface::cleanString(const string &stringToClean_) {
    string result = stringToClean_;
    // remove everythin that not is not alphanum and that is not _
    result.erase(
                  remove_if( result.begin(), result.end(),
                             [](char c) { return !(isalnum(c) || (c == '_') ) ; }
                           ),
                  result.end()
                );

    return result;
}

string DBInterface::cTimeToString(tm datetime_, bool inUnixTime_) {
    stringstream dateTimeString;

    if (inUnixTime_) {
        // convert to number of seconds since 1979 (unix-time)
        // e.g. 1434055562
        datetime_.tm_hour += 2;    // hours (0 to 23)
        datetime_.tm_mon  -= 1;    // month (0 bis 11)
        datetime_.tm_year -= 1900; // Year (calender-year minus 1900)
        datetime_.tm_isdst = 1;    // converting us-summer-time

        time_t secondsSince1970 = mktime(&datetime_);
        dateTimeString << secondsSince1970;
    } else {
        // convert to formatted string
        // e.g. 2016-08-09T16:40:57Z
        dateTimeString << datetime_.tm_year << "-" ;
        dateTimeString << setfill('0') << setw(2);
        dateTimeString << datetime_.tm_mon  << "-" ;
        dateTimeString << setfill('0') << setw(2);
        dateTimeString << datetime_.tm_mday << "T" ;
        dateTimeString << setfill('0') << setw(2);
        dateTimeString << datetime_.tm_hour << ":" ;
        dateTimeString << setfill('0') << setw(2);
        dateTimeString << datetime_.tm_min  << ":" ;
        dateTimeString << setfill('0') << setw(2);
        dateTimeString << datetime_.tm_sec  << "Z" ;
    }
    return dateTimeString.str();
}




