#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "dbinterface.h"



TEST_CASE( "HTTPRequest.post works") {
    HTTPRequest req;
    string url;
    string postFields;

    SECTION("both parameters valid") {
        url = "http://localhost:8086/write?db=test3";
        postFields = "forecast,datatype=temperature value=50";
        REQUIRE(req.post(url,postFields));
    }

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
