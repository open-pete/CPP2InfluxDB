/**
 * CPP2InfluxDB.h
 * Purpose: defines class CPP2InfluxDB
 *
 * @author Wall.Of.Death
 * @version 1.0 20160704
 */

#ifndef CPP2InfluxDB_H
#define CPP2InfluxDB_H

// todo
#include <QStringList>
// --
#include <QString>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
// ---
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <vector>
// ---
#include "DataBuffer.h"
#include "config.h"
#include "open-pete/Log-Writer/include/LogWriter.h"
#include "HTTPRequest.h"


using namespace std;

/**
 * CPP2InfluxDB class
 * @brief CPP2InfluxDB provides access to the database
 * The CPP2InfluxDB class provides acces to the database by having public functions for
 * initializing, reading and writing data to the database.
 * It is designed by the design pattern singleton.
 */
class CPP2InfluxDB {
    public:
        /* --- needed to create a singleton --- */
        static CPP2InfluxDB& getInstance() {
            static CPP2InfluxDB _instance;
            return _instance;
        }
        ~CPP2InfluxDB() {}

        /* --- interfacing the database --- */
        void               init             ();
        void               writeToDataBase  (DataBuffer &dataBuffer_);
        vector<DataBuffer> readFromDataBase (DataBuffer &dataBuffer_);
        void               writeStatusOK    (      bool  statusOK_  );
        bool               readStatusOK     ();
        bool               getDBFailure     ();


    private:
        /* --- needed to create a singleton --- */
        CPP2InfluxDB() {};                  // must be private to avoid the creation of CPP2InfluxDB from the outside by the constructor
                                           // use 'protected' if you want to inherit from this class
        CPP2InfluxDB            (const CPP2InfluxDB& CPP2InfluxDB_); // must be private to avoid creation of another CPP2InfluxDB-instance by copy-constructor
        CPP2InfluxDB& operator= (const CPP2InfluxDB& CPP2InfluxDB_); // must be private to avoid creating an new CPP2InfluxDB-instance by copying

        /* --- interfacing the database --- */
        void createIfNotCreatedDataBase();
        void setDBFailure(bool val_) {dbFailure = val_;} ;
        bool dbFailure = false;
        LogWriter log;

        /* --- miscellaneous --- */
        string cleanString(const string& stringToClean_);
        double cutValueToInfluxDBRange(double val_);
        vector<DataBuffer> jsonToDataBufferVector(const string& json_, const string &dataSource_);
};

#endif // CPP2InfluxDB_H
