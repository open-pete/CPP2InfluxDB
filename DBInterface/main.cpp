#include <iostream>
#include "include/DataBuffer.h"
#include "include/dbinterface.h"

using namespace std;

int main() {
    DataBuffer dataBuffer;

    // try dataBuffer
    cout << dataBuffer << endl;
    dataBuffer.data["Temperature"] = 4.5;
    cout << dataBuffer << endl;
    dataBuffer.data["AirPressure"] = 1021;
    cout << dataBuffer << endl;

    DataBufferProperties DBP = possibleDataBufferValues.at("Temperature");
    if ((dataBuffer.data["Temperature"] <= DBP.maxValue) && (dataBuffer.data["Temperature"] >= DBP.minValue)) {
        cout << "Temperature is within its range." << endl;
        cout << "Temperature : " << dataBuffer.data["Temperature"] <<  " " << DBP.unitOfMeasure << endl;

    }

    //try dbinterface
    DBInterface& dbi = DBInterface::getInstance();
    dbi.init("hallo.com");
    dbi.writeToDataBase(dataBuffer);
    dataBuffer = dbi.readFromDataBase(dataBuffer);
    cout << "dataBuffer content " << dataBuffer << endl;
    cout << "getDBFailure " << dbi.getDBFailure() << endl;
    dbi.writeStatusOK(true);
    cout << "statusOK " << dbi.readStatusOK() << endl;
    return 0;
}
