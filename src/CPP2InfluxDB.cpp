/**
 * CPP2InfluxDB.cpp
 * Purpose: implements class CPP2InfluxDB
 *
 * @author Wall.Of.Death
 * @version 1.0 20160704
 */


#include "../include/CPP2InfluxDB.h"

/**
 * CPP2InfluxDB::init
 * @brief creates a LogWriter-object
 */
void CPP2InfluxDB::init() {
    createIfNotCreatedDataBase();

    // create LogWriter-object
    log = LogWriter("CPP2InfluxDB", PATH_OF_LOGFILE);

    log << SLevel(INFO) << "Initialized CPP2InfluxDB with url : " << URL_OF_DATABASE << "." << endl;

}

/**
 * CPP2InfluxDB::writeToDataBase
 * @brief writeToDataBase writes content of dataBuffer_ to database
 * @param dataBuffer_ data which is written to database
 */
void CPP2InfluxDB::writeToDataBase(DataBuffer& dataBuffer_) {
    if (readStatusOK()) {

        stringstream httpRequestUrl;

        httpRequestUrl << URL_OF_DATABASE << "/write?db=" << NAME_OF_DATBASE << "&precision=s";
        stringstream httpRequestPostFields;
        if (!dataBuffer_.useDataSource) {
            log << SLevel(ERROR) << "Aborted writing to database because there was either no DataSource specified" <<
             " or the useDataSource-flag was not set to true." << endl;
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
                double value = cutValueToInfluxDBRange(iterator->second);
                httpRequestPostFields << name << "=" << value;
            }
            // create datetime-string
            if (dataBuffer_.useDateTimes) {
                if (dataBuffer_.startDateTime.years() < 1970) {
                    log << SLevel(ERROR) << "Aborted writing to database because of invalid datetime. " <<
                    "Please use only dates >= 01.01.1970." << endl;
                    setDBFailure(true);
                    return;
                } else {
                    string startDateTime = to_string(dataBuffer_.startDateTime.toUnixTime());
                    httpRequestPostFields << " " << startDateTime;
                }
            } else {
                // if no date-time is specified use current UTC time (cut down to current hour)
                DateTimePP dt;
                dt.now(true);
                int currentLocalDateTime = dt.toUnixTime();
                string startDateTime = to_string(currentLocalDateTime);
                httpRequestPostFields << " " << startDateTime;
            }
            HTTPRequest req;
            log << SLevel(INFO) << "curl : " << httpRequestUrl.str() << " -> " << httpRequestPostFields.str() << endl;
            bool noFailure = req.post(httpRequestUrl.str(),httpRequestPostFields.str());
            setDBFailure(!noFailure);
        }
    } else {
        log << SLevel(ERROR) << "Aborted writing to database because of status not OK" << endl;
    }
}

/**
 * CPP2InfluxDB::readFromDataBase
 * @brief readFromDataBase reads the data which is requested by dataBuffer_ from database
 * @param dataBuffer_ requested data (is only filled with requested strings)
 * @return returns the requested dataBuffer_ which now contains requested data
 */
vector<DataBuffer> CPP2InfluxDB::readFromDataBase(DataBuffer& dataBuffer_) {

    // create empty result
    vector<DataBuffer> result;

    if (readStatusOK()) {

        // create url-string for select ... from ...
        stringstream httpRequestUrl;
        httpRequestUrl << URL_OF_DATABASE << "/query?pretty=true&db=" << NAME_OF_DATBASE << "&q=SELECT+"; // << "&precision=s";

        // iterate all requested fields
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

        // add requested datasource
        if (!dataBuffer_.useDataSource) {
            log << SLevel(ERROR) << "Aborted reading from database because there was either no DataSource specified" <<
            " or the useDataSource-flag was not set to true." << endl;
        } else {
            string dataSource = cleanString(dataBuffer_.dataSource);
            httpRequestUrl << "FROM+point+where+DataSource+=+'" << dataSource << "'";

            // add requested datetime-range
            if (dataBuffer_.useDateTimes) {
                if ( (dataBuffer_.startDateTime.years() < 1970) ||
                     (dataBuffer_.endDateTime.years()   < 1970) ){
                    log << SLevel(ERROR) << "Aborted reading from database because of invalid datetime. " <<
                    "Please use only dates >= 01.01.1970 ." << endl;
                    setDBFailure(true);
                    return result;
                }
                DateTimePP dt = dataBuffer_.startDateTime;
                string startDateTime = dt.toString();
                dt = dataBuffer_.endDateTime;
                string   endDateTime = dt.toString();
                httpRequestUrl << "+and+time+>=+'" << startDateTime << "'";
                httpRequestUrl << "+and+time+<=+'" <<   endDateTime << "'";
            } else {
                // if no date-time is specified use local time (cut down to current hour)
                DateTimePP currentUTCDateTime;
                currentUTCDateTime.now(true);
                string startDateTime = currentUTCDateTime.toString();
                string   endDateTime = startDateTime;
                httpRequestUrl << "+and+time+>=+'" << startDateTime << "'";
                httpRequestUrl << "+and+time+<=+'" <<   endDateTime << "'";
            }

            // execute request
            HTTPRequest req;
            string answerJSON = req.get(httpRequestUrl.str());
            setDBFailure(answerJSON == "");

            // convert json to vector of DataBuffer
            result = jsonToDataBufferVector(answerJSON,dataBuffer_.dataSource);
            if (! dataBuffer_.useDateTimes) {
                for (unsigned int i=0; i < result.size();i++){
                    result[i].startDateTime.seconds(0);   // seconds
                    result[i].startDateTime.minutes(0);   // minutes
                    result[i].startDateTime.hours(0);     // hours
                    result[i].startDateTime.days(0);      // day
                    result[i].startDateTime.months(0);    // month
                    result[i].startDateTime.years(0);     // year

                    result[i].endDateTime = result[i].startDateTime;
                    result[i].useDateTimes = false;
                }
            }
        }
    } else {
        log << SLevel(ERROR) << "Aborted reading from database because of status not OK" << endl;
    }

    // return
    return result;
}

/**
 * CPP2InfluxDB::writeStatusOK
 * @brief writes the boolean value statusOK_ to database
 * @param statusOK_ boolean value which is wirtten to the database
 */
void CPP2InfluxDB::writeStatusOK(bool statusOK_) {
    stringstream httpRequestUrl;
    stringstream httpRequestPostFields;
    HTTPRequest req;

    // try to delete old value from influxDB
    // (post writes an error to log, if there is nothing to delete)
    httpRequestUrl << URL_OF_DATABASE << "/query?db=" << NAME_OF_DATBASE;
    httpRequestPostFields << "q=drop measurement statusOK";
    req.post(httpRequestUrl.str(),httpRequestPostFields.str());

    // write new value to influxDB
    stringstream httpRequestUrl2;
    stringstream httpRequestPostFields2;
    httpRequestUrl2 << URL_OF_DATABASE << "/write?db=" << NAME_OF_DATBASE << "&precision=s";

    httpRequestPostFields2 << "statusOK value=" << statusOK_;

    bool noFailure = req.post(httpRequestUrl2.str(),httpRequestPostFields2.str());
    setDBFailure(!noFailure);
    if (!noFailure) {
        log << SLevel(ERROR) << "Aborted writing statusOK to database because http-post was not possible." << endl;
    }
}

/**
 * CPP2InfluxDB::readStatusOK
 * @brief reads the boolean value statusOK from database and returns it.
 * @return returns the value of the boolean value statusOK
 */
bool CPP2InfluxDB::readStatusOK() {
    // create url-string for select ... from ...
    stringstream httpRequestUrl;
    HTTPRequest req;

    httpRequestUrl << URL_OF_DATABASE << "/query?pretty=true&db=" << NAME_OF_DATBASE << "&q=SELECT+";
    httpRequestUrl << "value+FROM+statusOK";

    string answerJSON = req.get(httpRequestUrl.str());
    setDBFailure(answerJSON == "");

    vector<DataBuffer> dataBufferVec = jsonToDataBufferVector(answerJSON,"");

    double result = dataBufferVec[0].data["value"];

    return (result != 0);
}

/**
 * CPP2InfluxDB::getDBFailure
 * @brief returns value of private member variable dbFailure
 * @return value of private member variable dbFailure
 */
bool CPP2InfluxDB::getDBFailure() {
    return dbFailure;
}

/**
 * CPP2InfluxDB::createIfNotCreatedDataBase
 * @brief creates database defined by NAME_OF_DATBASE in config.h if not already created
 */
void CPP2InfluxDB::createIfNotCreatedDataBase() {
    HTTPRequest request;
    request.post(URL_OF_DATABASE + "/query?q=create+database+"+NAME_OF_DATBASE+"&db=_internal","");
}

/**
 * CPP2InfluxDB::cleanString
 * @brief removes every char that is not an alphabetic character, a number or '_'
 * @param stringToClean_ the string to clean
 * @return returns stringToClean_ without anything but character, numbers and '_'
 */
string CPP2InfluxDB::cleanString(const string &stringToClean_) {
    string result = stringToClean_;
    // remove everything that not is not alphanum and that is not _
    result.erase(
                  remove_if( result.begin(), result.end(),
                             [](char c) { return !(isalnum(c) || (c == '_') ) ; }
                           ),
                  result.end()
                );

    return result;
}

/**
 * CPP2InfluxDB::cutValueToInfluxDBRange
 * @brief cuts val_ to the range INFLUXDB_MAX <= val_ >= INFLUXDB_MIN
 * @param val_ value to cut
 * @return returns INFLUXDB_MAX / INFLUXDB_MIN if value is bigger/smaller as INFLUXDB_MAX/INFLUXDB_MIN
 */
double CPP2InfluxDB::cutValueToInfluxDBRange(double val_) {
    if (val_ > INFLUXDB_MAX) {
        return INFLUXDB_MAX;
    } else if (val_ < INFLUXDB_MIN) {
        return INFLUXDB_MIN;
    } else {
        return val_;
    }
}


/**
 * CPP2InfluxDB::jsonToDataBufferVector
 * @brief iterate through JSON and return data inside json_ as vector of DataBuffer
 * @param json_ JSON string to convert
 * @return returns a vector of DataBuffer which contains the data inside json_
 *
 * This function can convert a json received from either InfluxDB or TODO
 * to a vector of DataBuffers.
 * If the JSONs origin was InfluxDB, the return values contains a DataBuffer for
 * every DateTime which was requested from InfluxDB.
 */
vector<DataBuffer> CPP2InfluxDB::jsonToDataBufferVector(const string &json_, const string& dataSource_) {
    vector<DataBuffer> result;
    QString jsonQString(json_.c_str());
    QJsonDocument jsonDocument = QJsonDocument::fromJson(jsonQString.toUtf8());
    QJsonObject jsonObject = jsonDocument.object();

    // parse json from influxdb
    if (jsonObject.contains(QString("results"))) {
        QJsonArray tempArray = jsonObject["results"].toArray();
        QJsonObject tempObject = tempArray.first().toObject();
        if (tempObject.contains(QString("series"))) {
            tempArray = tempObject["series"].toArray();
            tempObject = tempArray.first().toObject();
            if (tempObject.contains(QString("columns")) &&
                tempObject.contains(QString("values" )) ){
                QJsonArray names  = tempObject["columns"].toArray();
                QJsonArray values = tempObject["values" ].toArray();

                // iterate through all datasets
                typedef QJsonArray::iterator it_type;
                for(it_type iterator = values.begin(); iterator != values.end(); iterator++) {
                    QJsonArray dataSet = values.at(iterator.i).toArray();
                    DataBuffer tempDataBuffer;
                    // iterate to all names/values in a dataset
                    for(it_type iterator2 = dataSet.begin(); iterator2 != dataSet.end(); iterator2++) {

                        // get name
                        string name = names.at(iterator2.i).toString().toStdString();
                        // get value
                        QJsonValue valueJSON = dataSet.at(iterator2.i);

                        // set time
                        if (name == "time") {
                            DateTimePP dt;
                            dt.fromString(valueJSON.toString().toStdString());
                            tempDataBuffer.useDateTimes = true;
                            tempDataBuffer.startDateTime = dt;
                            tempDataBuffer.endDateTime   = dt;
                        } else {
                            // set values
                            double valueDouble = valueJSON.toDouble();
                            tempDataBuffer.data[name] = cutValueToInfluxDBRange(valueDouble);
                        }
                    }
                    // add DataSource;
                    tempDataBuffer.useDataSource = true;
                    tempDataBuffer.dataSource = cleanString(dataSource_);

                    // add data buffer to vector
                    result.push_back(tempDataBuffer);

                }
            } else {
                log << SLevel(ERROR) << "Aborted parsing InfluxDB-Json to databuffer. Unable to find 'columns and/or 'values' in JSON" << endl;
            }
        } else {
            log << SLevel(ERROR) << "Aborted parsing InfluxDB-Json to databuffer. Unable to find 'series' in JSON" << endl;
        }
    }


    return result;
}
