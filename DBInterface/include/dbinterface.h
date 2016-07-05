/**
 * DBInterface.h
 * Purpose: defines class DBInterface
 *
 * @author Wall.Of.Death
 * @version 1.0 20160704
 */

#ifndef DBINTERFACE_H
#define DBINTERFACE_H

#include "DataBuffer.h"
#include "config.h"
#include "logwriter.h"
#include "HTTPRequest.h"

/**
 * DBInterface class
 * @brief DBInterface provides access to the database
 * The DBInterface class provides acces to the database by having public functions for
 * initializing, reading and writing data to the database.
 * It is designed by the design pattern singleton.
 */
class DBInterface {
    public:
        /* --- needed to create a singleton --- */
        static DBInterface& getInstance() {
            static DBInterface _instance;
            return _instance;
        }
        ~DBInterface() {}

        /* --- interfacing the database --- */
        void       init             ();
        void       writeToDataBase  (const DataBuffer& dataBuffer_);
        DataBuffer readFromDataBase (const DataBuffer& dataBuffer_);
        void       writeStatusOK    (      bool        statusOK_  );
        bool       readStatusOK     ();
        bool       getDBFailure     ();


    private:
        /* --- needed to create a singleton --- */
        DBInterface() {};                  // must be private to avoid the creation of DBInterface from the outside by the constructor
                                           // use 'protected' if you want to inherit from this class
        DBInterface            (const DBInterface& dbInterface_); // must be private to avoid creation of another DBInterface-instance by copy-constructor
        DBInterface& operator= (const DBInterface& dbInterface_); // must be private to avoid creating an new DBInterface-instance by copying

        /* --- interfacing the database --- */
        void createIfNotCreatedDataBase();
        bool dbFailure = false;
        LogWriter log;
};

#endif // DBINTERFACE_H
