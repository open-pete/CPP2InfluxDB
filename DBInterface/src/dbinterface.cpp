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
        //http://localhost:8086/write?db=WeatherData2

        httpRequestUrl << URL_OF_DATABASE << "/write?db=" << NAME_OF_DATBASE;
        stringstream httpRequestPostFields;
        if (!dataBuffer_.useDataSource) {
            log << SLevel(ERROR) << "Aborted writing to database because there was either no DataSource specified";
            log << " or the useDataSource-flag was not set to true." << endl;
        } else {
            httpRequestPostFields << "point,DataSource=" << dataBuffer_.dataSource << " ";

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
DataBuffer DBInterface::readFromDataBase(const DataBuffer& dataBuffer_) {
    if (readStatusOK()) {
        // --- TODO -- dummy code ---
        cout << "read from database : " << dataBuffer_ << endl;
        DataBuffer temp = dataBuffer_;
        for (auto& x : temp.data) {
            x.second = rand() % 100;
        }
        return dataBuffer_;
        // --- TODO -- dummy code ---
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


