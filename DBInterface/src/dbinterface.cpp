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
 * @brief sets the url of the database and creates a LogWriter-object
 * @param url_ url of the database
 */
void DBInterface::init(const string& url_) {
    // set url of database
    url = url_;

    // create LogWriter-object
    log = LogWriter("DBInterface", pathOfLogFile);

    log << SLevel(INFO) << "Initialized DBInterface with url :" << url << "." << endl;
}

/**
 * DBInterface::writeToDataBase
 * @brief writeToDataBase writes content of dataBuffer_ to database
 * @param dataBuffer_ data which is written to database
 */
void DBInterface::writeToDataBase(const DataBuffer& dataBuffer_) {
    if (readStatusOK()) {
        // --- TODO -- dummy code ---
        cout << "written to database : " << dataBuffer_ << endl;
        // --- TODO -- dummy code ---
    } else {
        log << SLevel(ERROR) << "Aborted writing to database because of status not OK";
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
    return rand() % 1;
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


