#include "../include/HTTPRequest.h"

/* --- constructor --- */
/**
 * HTTPRequest::HTTPRequest
 * @brief constuctor of class HTTPRequest, initializes local LogWriter object.
 */
HTTPRequest::HTTPRequest() {
    // create LogWriter-object
    log = LogWriter("HTTPRequest", PATH_OF_LOGFILE);
}

/* --- http - requests --- */
/**
 * HTTPRequest::post
 * @brief executes a http-post-request for the given url
 * @param url_ the URL which is requested
 * @return returns true if request executed successfully, otherwise false
 */
bool HTTPRequest::post(const string &url_) {
    if (system(NULL)) {                                    // Checking if command - processor is available
        string command = "curl -i -XPOST '" + url_ + "'";  // build command-string
        int statusCode = system (command.c_str());         // execute command
        return true;
    } else {
        log << SLevel(ERROR) <<  "Unable to make http-post-request, command proccessor is not available" << endl;
        return false;
    }

}

bool HTTPRequest::get(const string &url_) {
    // curl -G 'http://localhost:8086/query?pretty=true' --data-urlencode "db=mydb" --data-urlencode "q=SELECT value FROM cpu_load_short WHERE region='us-west'"
    return true;
}
