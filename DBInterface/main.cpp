#include <iostream>
#include "include/DataBuffer.h"
#include "include/dbinterface.h"
#include "include/HTTPRequest.h"

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
    dbi.init();
    dbi.writeToDataBase(dataBuffer);
    dataBuffer = dbi.readFromDataBase(dataBuffer);
    cout << "dataBuffer content " << dataBuffer << endl;
    cout << "getDBFailure " << dbi.getDBFailure() << endl;
    dbi.writeStatusOK(true);
    cout << "statusOK " << dbi.readStatusOK() << endl;

    //try http-request
    HTTPRequest req;
    //req.post("http://localhost:8086/write?db=test3' --data-binary 'forecast,datatype=temperature value=50");
    req.post("http://localhost:8086/query?q=create+database+test400&db=_internal");
    //req.get("http://localhost:8086/query?pretty=true&db=test3&q=SELECT+*+FROM+forecast");
    string answer = req.get("http://localhost:8086/query?pretty=true&db=WeatherData&q=SELECT+Lufttemperatur_2m+FROM+point+where+DataSource+=+'Forecast'+and+time+=+'2015-08-18T23:00:00.00000000Z'+%2B+1000h");
    cout << answer;
    //req.get("http://api.openweathermap.org/data/2.5/weather?lat=52.9&lon=9.2&APPID=08854a5d6fe0754f2670f5fa5127a831");

    return 0 ;
}

