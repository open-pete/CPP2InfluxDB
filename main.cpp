#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include <float.h>
#include "dbinterface.h"

TEST_CASE( "HTTPRequest.post works") {
    HTTPRequest req;
    string url;
    string postFields;

    SECTION("url_ valid, postFields_ empty") {
        url = "http://localhost:8086/query?q=create+database+WeatherData2&db=_internal";
        postFields = "";
        REQUIRE(req.post(url,postFields));
    }

    SECTION("url_ is not valid") {
        url = "http://localhost:86/write?db=test3";
        postFields = "forecast,datatype=temperature value=50";
        REQUIRE_FALSE(req.post(url,postFields));
    }

    SECTION("url_ is empty") {
        url = "";
        postFields = "forecast,datatype=temperature value=50";
        REQUIRE_FALSE(req.post(url,postFields));
    }

}

TEST_CASE( "HTTPRequest.get works") {
    HTTPRequest req;
    string url;

    SECTION("url_ valid") {
        url = "http://localhost:8086/query?pretty=true&db=WeatherData&q=SELECT+Lufttemperatur_2m+FROM+point";
        string result = req.get(url);
        string sub = result.substr(0,20);
        REQUIRE(sub == "{\n    \"results\": [\n ");
    }


    SECTION("url_ is not valid") {
        url = "http://localhost:8086/Lufttemperatur_2m+FROM+point";
        REQUIRE(req.get(url) == "");
    }

    SECTION("url_ is empty") {
        url = "";
        REQUIRE(req.get(url) == "");
    }

}


TEST_CASE("DBInterface, write/read to/from database, getDBFailure") {
    DataBuffer dataBuffer, dataBuffer2;

    DBInterface& dbi = DBInterface::getInstance();
    dbi.init();

    dbi.writeStatusOK(true);

    SECTION ("write / read valid databuffer") {
        //2015-06-11T20:46:02
        dataBuffer.startDateTime.seconds(2);    // seconds
        dataBuffer.startDateTime.minutes(46);   // minutes
        dataBuffer.startDateTime.hours(20);     // hours
        dataBuffer.startDateTime.days(11);      // day
        dataBuffer.startDateTime.months(6);     // month
        dataBuffer.startDateTime.years(2015);   // year

        dataBuffer.endDateTime = dataBuffer.startDateTime;
        dataBuffer.useDateTimes = true;

        dataBuffer.dataSource = "Forecast";
        dataBuffer.useDataSource = true;

        dataBuffer.data["Lufttemperatur_2m"] = 14.5;
        dataBuffer.data["RelativeLuftfeuchte_2m"] = 1200;
        dbi.writeToDataBase(dataBuffer);

        dataBuffer2 = dataBuffer;
        dataBuffer2.data["Lufttemperatur_2m"] = 0;
        dataBuffer2.data["RelativeLuftfeuchte_2m"] = 0;
        vector<DataBuffer> dataBufferVec = dbi.readFromDataBase(dataBuffer2);
        REQUIRE(dataBufferVec[0] == dataBuffer);
        REQUIRE(dbi.getDBFailure() == false);
    }

    SECTION ("write / read date = 01.01.1972") {
        dataBuffer.startDateTime.seconds(0);    // seconds
        dataBuffer.startDateTime.minutes(0);    // minutes
        dataBuffer.startDateTime.hours(0);      // hours
        dataBuffer.startDateTime.days(1);       // day
        dataBuffer.startDateTime.months(1);     // month
        dataBuffer.startDateTime.years(1972);    // year

        dataBuffer.endDateTime = dataBuffer.startDateTime;
        dataBuffer.useDateTimes = true;

        dataBuffer.dataSource = "Forecast";
        dataBuffer.useDataSource = true;

        dataBuffer.data["Lufttemperatur_2m"] = 14.5;
        dataBuffer.data["RelativeLuftfeuchte_2m"] = 1200;
        dbi.writeToDataBase(dataBuffer);

        dataBuffer2 = dataBuffer;
        dataBuffer2.data["Lufttemperatur_2m"] = 0;
        dataBuffer2.data["RelativeLuftfeuchte_2m"] = 0;
        vector<DataBuffer> dataBufferVec = dbi.readFromDataBase(dataBuffer2);
        REQUIRE(dataBufferVec[0] == dataBuffer);
        REQUIRE(dbi.getDBFailure() == false);
    }

    SECTION ("write / read date < 01.01.1972") {
        dataBuffer.startDateTime.seconds(0);    // seconds
        dataBuffer.startDateTime.minutes(0);    // minutes
        dataBuffer.startDateTime.hours(0);      // hours
        dataBuffer.startDateTime.days(31);      // day
        dataBuffer.startDateTime.months(12);    // month
        dataBuffer.startDateTime.years(1971);   // year

        dataBuffer.endDateTime = dataBuffer.startDateTime;
        dataBuffer.useDateTimes = true;

        dataBuffer.dataSource = "Forecast";
        dataBuffer.useDataSource = true;

        dataBuffer.data["Lufttemperatur_2m"] = 14.5;
        dataBuffer.data["RelativeLuftfeuchte_2m"] = 1200;
        dbi.writeToDataBase(dataBuffer);

        dataBuffer2 = dataBuffer;
        dataBuffer2.data["Lufttemperatur_2m"] = 0;
        dataBuffer2.data["RelativeLuftfeuchte_2m"] = 0;
        vector<DataBuffer> dataBufferVec = dbi.readFromDataBase(dataBuffer2);
        REQUIRE(dataBufferVec.size() == 0);
        REQUIRE(dbi.getDBFailure() == true);
    }



    SECTION ("write / read valid values") {
        dataBuffer.startDateTime.seconds(0);    // seconds
        dataBuffer.startDateTime.minutes(0);    // minutes
        dataBuffer.startDateTime.hours(0);      // hours
        dataBuffer.startDateTime.days(31);      // day
        dataBuffer.startDateTime.months(12);    // month
        dataBuffer.startDateTime.years(1972);   // year

        dataBuffer.endDateTime = dataBuffer.startDateTime;
        dataBuffer.useDateTimes = true;

        dataBuffer.dataSource = "Forecast";
        dataBuffer.useDataSource = true;

        dataBuffer.data["Lufttemperatur_2m"] = INFLUXDB_MAX;
        dataBuffer.data["RelativeLuftfeuchte_2m"] = INFLUXDB_MIN;
        dataBuffer.data["Windgeschwindigkeit_Stundenmittel"] = 0;

        dbi.writeToDataBase(dataBuffer);

        dataBuffer2 = dataBuffer;
        dataBuffer2.data["Lufttemperatur_2m"] = 0;
        dataBuffer2.data["RelativeLuftfeuchte_2m"] = 0;
        dataBuffer2.data["Windgeschwindigkeit_Stundenmittel"] = 0;
        vector<DataBuffer> dataBufferVec = dbi.readFromDataBase(dataBuffer2);
        REQUIRE(dataBufferVec[0] == dataBuffer);
        REQUIRE(dbi.getDBFailure() == false);
    }

    SECTION ("write / read with current local time") {
        dataBuffer.startDateTime.seconds(0);   // seconds
        dataBuffer.startDateTime.minutes(0);   // minutes
        dataBuffer.startDateTime.hours(0);     // hours
        dataBuffer.startDateTime.days(0);      // day
        dataBuffer.startDateTime.months(0);    // month
        dataBuffer.startDateTime.years(0);     // year
        dataBuffer.useDateTimes = false;

        dataBuffer.dataSource = "Forecast";
        dataBuffer.useDataSource = true;

        dataBuffer.data["Lufttemperatur_2m"] = -10.5;
        dataBuffer.data["RelativeLuftfeuchte_2m"] = 90.4;
        dataBuffer.data["Windgeschwindigkeit_Stundenmittel"] = 10.345;

        dbi.writeToDataBase(dataBuffer);

        dataBuffer2 = dataBuffer;
        dataBuffer2.data["Lufttemperatur_2m"] = 0;
        dataBuffer2.data["RelativeLuftfeuchte_2m"] = 0;
        dataBuffer2.data["Windgeschwindigkeit_Stundenmittel"] = 0;
        vector<DataBuffer> dataBufferVec = dbi.readFromDataBase(dataBuffer2);
        REQUIRE(dataBufferVec[0] == dataBuffer);
        REQUIRE(dbi.getDBFailure() == false);
    }

    SECTION ("write / read invalid values and strings") {
        // invalid values get cut to range
        // invalid extra signs get removed
        // (alphabetical chars, numbers and '_' are allowed)
        dataBuffer.startDateTime.seconds(59);   // seconds
        dataBuffer.startDateTime.minutes(59);   // minutes
        dataBuffer.startDateTime.hours(1);      // hours
        dataBuffer.startDateTime.days(10);      // day
        dataBuffer.startDateTime.months(8);     // month
        dataBuffer.startDateTime.years(2016);   // year

        dataBuffer.endDateTime = dataBuffer.startDateTime;
        dataBuffer.useDateTimes = true;

        dataBuffer.dataSource = "Foreca%st";
        dataBuffer.useDataSource = true;

        dataBuffer.data["Luft%&te2mperatur_2m"] = INFLUXDB_MAX+1;
        dataBuffer.data["RelativeL34uf'tfeuchte_2m"] = INFLUXDB_MIN-1;
        dataBuffer.data["Windgeschwindi()gk?eit_Stundenmittel"] = 0;

        dbi.writeToDataBase(dataBuffer);

        dataBuffer2 = dataBuffer;
        dataBuffer2.data["Luft%&te2mperatur_2m"] = 0;
        dataBuffer2.data["RelativeL34uf'tfeuchte_2m"] = 0;
        dataBuffer2.data["Windgeschwindi()gk?eit_Stundenmittel"] = 0;
        vector<DataBuffer> dataBufferVec = dbi.readFromDataBase(dataBuffer2);

        DataBuffer dataBufferWithoutExtraSigns;

        dataBufferWithoutExtraSigns.startDateTime = dataBuffer.startDateTime;
        dataBufferWithoutExtraSigns.endDateTime   = dataBuffer.endDateTime;
        dataBufferWithoutExtraSigns.useDateTimes = true;

        dataBufferWithoutExtraSigns.dataSource = "Forecast";
        dataBufferWithoutExtraSigns.useDataSource = true;

        dataBufferWithoutExtraSigns.data["Luftte2mperatur_2m"] = INFLUXDB_MAX+1;
        dataBufferWithoutExtraSigns.data["RelativeL34uftfeuchte_2m"] = INFLUXDB_MIN-1;
        dataBufferWithoutExtraSigns.data["Windgeschwindigkeit_Stundenmittel"] = 0;

        REQUIRE(dataBufferVec[0] == dataBufferWithoutExtraSigns);
        REQUIRE(dbi.getDBFailure() == false);
    }

}

TEST_CASE ("Write / Read Status") {
    DBInterface& dbi = DBInterface::getInstance();
    dbi.init();

    SECTION("Write/Read of true works") {
        dbi.writeStatusOK(true);
        REQUIRE(dbi.readStatusOK());
    }

    SECTION("Write/Read of false works") {
        dbi.writeStatusOK(false);
        REQUIRE_FALSE(dbi.readStatusOK());
    }
}
